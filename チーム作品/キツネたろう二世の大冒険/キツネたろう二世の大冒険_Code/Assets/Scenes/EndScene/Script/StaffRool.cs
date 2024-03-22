using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StaffRool : MonoBehaviour
{
    // エンドが真ん中あたりにいるフレーム(どっちか分からないから一時的に保持)
    private const int kRoolFrame = 3750;
    //private const int kRoolFrame = 2800;
    // タイトルに移行するフレーム
    private const int kTitleFrame = kRoolFrame + 50 * 5;

    public GameObject _credits;
    Vector3 _vec;

    int _frame = 0;

    bool _isEnd;
    private Color _color;
    private GameObject _fade;

    private void Start()
    {
        _vec = new Vector3(0, 1f, 0);
        _isEnd = false;

        _fade = GameObject.Find("Fade");
        _color = _credits.GetComponent<Text>().color;
    }

    public void RoolUpdate()
    {
        _frame++;
        
        if (_frame < kRoolFrame)
        {
            _credits.GetComponent<RectTransform>().localPosition += _vec;
        }
        if (_frame > kTitleFrame)
        {
            _isEnd = true;

            _color.a = 1.0f - _fade.GetComponent<FadeScene>().GetAlphColor();
            _credits.GetComponent<Text>().color = _color;
        }
    }

    public bool GetIsEnd()
    {
        return _isEnd;
    }
}
