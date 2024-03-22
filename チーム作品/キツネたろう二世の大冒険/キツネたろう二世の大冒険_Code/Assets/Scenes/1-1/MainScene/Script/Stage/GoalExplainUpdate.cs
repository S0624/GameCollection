/*ゴールするときの説明の挙動処理*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GoalExplainUpdate : MonoBehaviour
{
    // ボタンUIの色.
    private Color _colorUI;
    // テキストの色.
    private Color _colorText;

    // 色のα値.
    [Range(0f, 1f)]
    public float _alpha;

    // α値の変動開始
    public bool _isAlphaChange;

    // α値の上昇速度.
    private float _alphaUpSpeed = 0.1f;

    // Start is called before the first frame update
    void Start()
    {
        Init();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        ColorApply();
        AlphaUpCount();
    }

    private void Init()
    {
        _colorUI = GetComponentInChildren<SpriteRenderer>().color;
        _colorText = GetComponentInChildren<Text>().color;
        _colorUI.a = 0.0f;
        _colorText.a = 0.0f;
        GetComponentInChildren<SpriteRenderer>().color = _colorUI;
        GetComponentInChildren<Text>().color = _colorText;
    }

    // 色を当てはめる.
    private void ColorApply()
    {
        _colorUI.a = _alpha;
        _colorText.a = _alpha;
        GetComponentInChildren<SpriteRenderer>().color = _colorUI;
        GetComponentInChildren<Text>().color = _colorText;
    }

    // α値を大きくする
    private void AlphaUpCount()
    {
        if (!_isAlphaChange) return;

        _alpha += _alphaUpSpeed;

        if( _alpha > 1.0f )
        {
            _alpha = 1.0f;
            _isAlphaChange = false;
        }
    }
}
