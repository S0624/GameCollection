using UnityEngine;
using UnityEngine.UI;

// 画像のフェードをさせるスクリプト.
public class ImageManager : MonoBehaviour
{
    // 足していくアルファ値の値.
    private readonly float kAlpha = 0.01f;

    // 色を入れるよう.
    private Color _color;
    // 画像の透明度の初期化をする.
    private void Start()
    {
        _color = gameObject.GetComponent<Image>().color;
        // アルファ値を0(透明)にする.
        _color.a = 0.0f;
    }

    private void FixedUpdate()
    {
        // 現在のアルファ値からたしていく.
        _color.a += kAlpha;
        gameObject.GetComponent<Image>().color = _color;
        // アルファ値が1.0(普通に表示)されたら1.0で固定させる.
        if (_color.a > 1.0f)
        {
            _color.a = 1.0f;
        }
    }
}
