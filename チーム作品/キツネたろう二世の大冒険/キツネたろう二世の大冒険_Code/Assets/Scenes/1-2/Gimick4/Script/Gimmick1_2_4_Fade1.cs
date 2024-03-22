using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Gimmick1_2_4_Fade1 : MonoBehaviour
{
    // オブジェクトを取得.
    public GameObject _timeCountDown;
    // タイムクラスを取得.
    private Gimmick1_2_4_CountDown2 _time;
    // 画像クラス
    private Image _image;
    // カラー用構造体を宣言.
    private Color _color;
    void Start()
    {
        // クラスを取得.
        _time = _timeCountDown.GetComponent<Gimmick1_2_4_CountDown2>();
        // 画像クラスを取得.
        _image = GetComponent<Image>();

        // カラー指定.
        _color.r = 0.0f;
        _color.g = 0.0f;
        _color.b = 0.0f;
        _color.a = 1.0f;
    }
    void Update()
    {
        
    }
    private void FixedUpdate()
    {
        // カウントが0ではなかったら.
        if(!_time.IsCount())
        {
            _color.a -= 0.1f;
        }

        // タイマーが0だった場合.
        if(_time.GetCountTime() == 0)
        {
            _color.a += 0.1f;
        }

        // 最大、最小を指定.
        if(_color.a > 1)
        {
            _color.a = 1;
        }
        if(_color.a < 0)
        {
            _color.a = 0;
        }
        // カラーを代入.
        _image.color = _color;
    }
}
