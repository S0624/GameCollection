using UnityEngine;
using UnityEngine.UI;
// ステージ番号(画像)を出すスクリプト

public class StageNoImage : MonoBehaviour
{
    // 処理をするまで待つフレーム数.
    private readonly static int kStayFrame = 50;
    // 引いていくアルファ値.
    private readonly static float kAlpha = 0.0625f;
    // フレーム数.
    private int _stayFrame;
    // 画像のカラー.
    private Color _color;
    // 画像のカラー取得.
    private Image _image;

    // 初期化処理.
    private void Start()
    {
        _image = GetComponent<Image>();
        _color = _image.color;
        _stayFrame = kStayFrame;
    }

    private void FixedUpdate()
    {
        // 50フレームから減算していく.
        _stayFrame--;
        // 引いて行って0より小さくなったら画像をフェードさせていく処理.
        if (_stayFrame < 0)
        {
            _color.a -= kAlpha;
            _image.color = _color;
            if (_color.a < 0.0f)
            {
                Destroy(gameObject);
            }
        }
    }
}
