using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
//using UnityEditor.U2D.Common;

public class Switch_1_2_2 : MonoBehaviour
{
    // 説明画面描画.
    public TipsDrawer _tipsDrawer;

    // プレイヤーがオブジェクトに当たったかどうか.
    private bool _isHit = false;

    // レバーを倒すかどうか.
    private bool _isLever = false;

    // レーバー取得用.
    private GameObject _leverRota;

    // レーバーの角度記録.
    private bool _isMinusRota = false;

    // 画像のクラスを取得.
    public Image _meter;

    // クリアしたときにclearの画像を表示させる.
    [SerializeField] private GenerateImg _img;

    // メーターの速度.
    public float _meterSpeed;

    //効果音
    public Sound_1_2_2 _sound;

    //フェードの時間稼ぎ
    int _fadeCount = 0;

    //フェードが始まる時間
    int _fadeTime;
    // ギミックをクリアしたかどうか.
    private bool _isResult = false;

    void Start()
    {
        _fadeTime = 60 * 2;
        //_sound
        // オブジェクト取得. 
        _leverRota = GameObject.Find("stage03_lever_02/locator1");

        _tipsDrawer.IsDownSlider();
    }

    private void Update()
    {
        // ボタンを押したら.
        if (Input.GetKeyDown("joystick button 1") && _isHit)
        {
            _isLever = true;
            _sound._isLeverFlag = true;
        }
        Debug.Log($"{name}");
    }

    private void FixedUpdate()
    {
        if (_isLever)
        {
            // レーバーの角度を調整.
            if (_leverRota.transform.localEulerAngles.x >= 310.0f)
            {
                _leverRota.transform.Rotate(1.0f, 0.0f, 0.0f);
            }
            else
            {
                // 角度が0.0fになったら.
                _isMinusRota = true;
            }

            // レーバーの角度を調整.
            if (_isMinusRota)
            {
                if (_leverRota.transform.localEulerAngles.x < 50.0f)
                {
                    _leverRota.transform.Rotate(1.0f, 0.0f, 0.0f);
                }
                else
                {
                    // 画像の表示.
                    _img.GenerateCompleteImage();
                    // 角度が50.0fになったら.
                    _fadeCount++;
                    //COMPLETEが表示されてから2秒たったらクリア判定を入れる
                    if (_fadeTime < _fadeCount)
                    {
                        _isResult = true;
                    }
                }
            }
            // メーターを動かす.
            _meter.fillAmount += _meterSpeed;
        }
    }

    private void OnTriggerStay(Collider other)
    {
        // プレイヤーだったら.
        if (other.gameObject.tag == "Player")
        {
            _isHit = true;
            return;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        // プレイヤーだったら.
        if (other.gameObject.tag == "Player")
        {
            _isHit = false;
            return;
        }
    }

    // ギミックをクリアしたかどうか.
    public bool GetResult()
    {
        return _isResult;
    }
}
