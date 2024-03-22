using UnityEngine;
// 画像の生成.
public class GenerateImg : MonoBehaviour
{
    // clearテキストをいれる.
    [SerializeField, Header("クリア画像")] private GameObject ClearImg;
    [SerializeField] private GameObject _clearText;
    [SerializeField] private GameObject _resetText;
    // Canvasを入れるよう.
    [SerializeField] private GameObject Canvas;
    // テキストの生成.
    private GameObject _img = null;
    // 画像を生成する.
    public void GenerateCompleteImage()
    {
        // 一回だけ画像を生成する.
        if (_img == null)
        {
            _img = Instantiate(ClearImg);
            _img.transform.SetParent(Canvas.transform, false);
        }
    }
    public void GenerateClearText()
    {
        // 一回だけ画像を生成する.
        if (_img == null)
        {
            _img = Instantiate(_clearText);
            _img.transform.SetParent(Canvas.transform, false);
        }
    }
    public void GenerateResetText()
    {
        // 一回だけ画像を生成する.
        if (_img == null)
        {
            _img = Instantiate(_resetText);
            _img.transform.SetParent(Canvas.transform, false);
        }
    }
}
