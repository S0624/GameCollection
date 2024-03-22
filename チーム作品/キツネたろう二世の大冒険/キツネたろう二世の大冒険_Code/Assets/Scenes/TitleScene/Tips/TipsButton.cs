using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TipsButton : MonoBehaviour
{
    // 画像を描画.
    Image _image;

    // 画像データ.
    public Sprite _sprite;

    // 画像サイズ
    private float _imageSize = 0.2f;
    
    // トランスフォームクラスの初期化.
    private RectTransform rectTransform = null;

    // 判定用.
    public TipsButtonColl coll;

    // 色変更用.
    private Color _color;

    // フェイド用.
    private bool _isImageDraw;

    void Start()
    {
        // パネルにImageコンポーネントを追加.
        _image = gameObject.AddComponent<Image>();
        // 画像をアタッチ.
        _image.sprite = _sprite;

        // RectTransformを取得して設定.
        rectTransform = _image.rectTransform;

        rectTransform.sizeDelta = new Vector2(1080, 1080); // 16:9アスペクト比を維持した高さ.
        // 画面外の上に配置.
        rectTransform.anchorMin        = new Vector2(0.5f, 0.5f);
        rectTransform.anchorMax        = new Vector2(0.5f, 0.5f);
        rectTransform.pivot            = new Vector2(0.5f, 0.5f);
        rectTransform.anchoredPosition = new Vector2(0.0f, 350.0f);
        rectTransform.localScale       = new Vector3(_imageSize, _imageSize, _imageSize);

        // 画像のアルファ値を指定する.
        _color = this.GetComponent<Image>().color;
        _color.a = 0.0f;
        gameObject.GetComponent<Image>().color = _color;
    }

    void Update()
    {
        // 当たっているかどうか.
        if(coll._isHit)
        {                     
            _isImageDraw = true;
        }
        else
        {
            _isImageDraw = false;
        }

        // アルファ値の変更
        if(_isImageDraw)
        {
            if(_color.a < 1.0f)
            {
                _color.a += 0.01f;
            }
            else
            {
                _color.a = 1.0f;
            }
        }
        else
        {
            if (_color.a > 0.0f)
            {
                _color.a -= 0.01f;
            }
            else
            {
                _color.a = 0.0f;
            }
        }

        // 色の代入
        gameObject.GetComponent<Image>().color = _color;
    }
}
