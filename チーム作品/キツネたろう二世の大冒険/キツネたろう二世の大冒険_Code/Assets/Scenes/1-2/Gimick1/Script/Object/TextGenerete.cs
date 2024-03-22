using UnityEngine;
using UnityEngine.UI;
// テキスト生成クラス.
public class TextGenerete : MonoBehaviour
{
    // 足していくアルファ値の値.
    private readonly float kAlpha = 0.05f;

    // 色を入れるよう.
    private Color _color;
    // 数フレーム表示させる
    [SerializeField] private int _waitTime = 60;
    // 画像の透明度の初期化をする.
    private void Start()
    {
        _color = gameObject.GetComponent<Text>().color;
        // アルファ値を1にする.
        _color.a = 0.98f;
    }

    private void FixedUpdate()
    {
        _waitTime--;
        if (_waitTime < 0)
        {
            _waitTime = 0;
            TextFade();
        }
    }
    private void TextFade()
    {
        // 現在のアルファ値からたしていく.
        _color.a -= kAlpha;
        gameObject.GetComponent<Text>().color = _color;
        // アルファ値が1.0(普通に表示)されたら1.0で固定させる.
        if (_color.a < 0.0f)
        {
            _color.a = 0.0f;
            Destroy(this.gameObject);
        }
    }
}
