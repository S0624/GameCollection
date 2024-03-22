using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TipsDrawer : MonoBehaviour
{
    // 画像データ.
    public Sprite _sprite; 
    // 下にスライドさせる場合の速度.
    public float _slideDownSpeed;
    // 上にスライドさせる場合の速度.
    public float _slideUpSpeed;
    // 画像サイズ
    public float _imageSize;

    // 2Dプレイヤーの場合
    public bool _is2DPlayer;

    // 画像クラスの初期化.
    private Image _image = null;
    // トランスフォームクラスの初期化.
    private RectTransform rectTransform = null;

    // スライド用の速度.
    private float _slideSpeed = 0.0f;

    // スライドの方向.
    private bool _isDownSlider = false;
    private bool _isUpSlider = false;

    // スライドの位置を確かめる.
    public bool _isSlideStart { get; private set; }
    public bool _isSlideEnd   { get; private set; }

    // プレイヤーの操作を受け付けなくする用.
    private Player3DMove _player;

    // 始めに描画する説明かどうか.
    public bool _isFirstTips;

    // プレイヤーの行動の制限.
    public bool _isPlayerJump;
    public bool _isPlayerMove;

    // 動きを有効にするかどうか.
    private bool _isMove = false;

    void Start()
    {
        // パネルにImageコンポーネントを追加.
        _image = gameObject.AddComponent<Image>();
        // 画像をアタッチ.
        _image.sprite = _sprite;
        // RectTransformを取得して設定.
        rectTransform = _image.rectTransform;

        // 16:9アスペクト比に設定.
        float targetAspectRatio = 16.0f / 9.0f;
        rectTransform.sizeDelta = new Vector2(1080, 1080 / targetAspectRatio); // 16:9アスペクト比を維持した高さ.
        // 画面外の上に配置.
        rectTransform.anchorMin        = new Vector2(0.5f, 0.5f);
        rectTransform.anchorMax        = new Vector2(0.5f, 0.5f);
        rectTransform.pivot            = new Vector2(0.5f, 0.5f);
        rectTransform.anchoredPosition = new Vector2(0.0f, 1080.0f);
        rectTransform.localScale       = new Vector3(_imageSize, _imageSize, _imageSize);

        _isSlideStart = true;
        _isSlideEnd = false;

        if(!_is2DPlayer)
        {
            _player = GameObject.Find("3DPlayer").GetComponent<Player3DMove>();
        }

        if(_isFirstTips)
        {
            if (_isPlayerMove)  _player._isController     = false;
            if (_isPlayerJump)  _player._isJumpController = false;
        }
    }


    private void Update()
    {
        // 始めの説明描画用.
        if(_isFirstTips)
        {
            if(Input.GetKeyDown(KeyCode.JoystickButton0))
            {
                IsUpSlider(true, false);
                _isFirstTips = false;
                _isMove = true;
            }
        }
        else
        {
            // 動けるようにする.
            if(_isMove)
            {
                _isMove = false;
                if (!_is2DPlayer)
                {
                    
                    if (_isPlayerMove) _player._isController     = true;
                    if (_isPlayerJump) _player._isJumpController = true;
                }
            }
        }

        // if 下にスライドの場合.
        // else if 上にスライド.
        if(_isDownSlider)
        {
            // Y軸で下にスライドさせるのでマイナス.
            _slideSpeed = (-_slideDownSpeed);
            // 画面の中心まで移動するとスライドを止める.
            if(rectTransform.anchoredPosition.y <= 1.0f)
            {
                _isSlideStart = false;
                _isSlideEnd   = true;

                _isDownSlider = false;
                _slideSpeed = 0.0f;
                rectTransform.anchoredPosition = new Vector2(rectTransform.anchoredPosition.x, 1.0f);
            }
        }
        else if(_isUpSlider)
        {
            _slideSpeed = _slideUpSpeed;
            if (rectTransform.anchoredPosition.y >= 1080.0f)
            {
                _isSlideStart = true;
                _isSlideEnd = false;

                _isUpSlider = false;
                _slideSpeed = 0.0f;
                rectTransform.anchoredPosition = new Vector2(rectTransform.anchoredPosition.x, 1080.0f);

            }
        }

        // 画像をスライドさせる.
        rectTransform.anchoredPosition += new Vector2(0.0f, _slideSpeed);
    }



    // 下にスライドさせる場合.
    // 引数には基本的にfalseを入れてください.
    public void IsDownSlider(bool isMove = false, bool isJump = false)
    {
        _isDownSlider = true;
        _isUpSlider = false;
        if (!_is2DPlayer)
        {
            if (_isPlayerMove) _player._isController     = isMove;
            if (_isPlayerJump) _player._isJumpController = isJump;
        }
    }
    // 上にスライドさせる場合.
    // 引数には基本的にtrueを入れてください.
    public void IsUpSlider(bool isMove = true, bool isJump = true)
    {
        _isUpSlider = true;
        _isDownSlider = false;
        if (!_is2DPlayer)
        {
            if (_isPlayerMove) _player._isController     = isMove;
            if (_isPlayerJump) _player._isJumpController = isJump;
        }
    }
    // スライドの位置が上だったら.
    public bool IsUpSliderResult()
    {
        return _isUpSlider;
    }
    // スライドの位置が下だったら.
    public bool IsDownSliderResult()
    {
        return _isDownSlider;
    }
}
