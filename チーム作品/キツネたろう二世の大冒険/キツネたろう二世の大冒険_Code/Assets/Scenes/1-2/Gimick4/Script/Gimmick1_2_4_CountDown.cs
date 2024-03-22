using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class Gimmick1_2_4_CountDown : MonoBehaviour
{
    // 制限時間.
    private float _repeatSpan = 0;
    // 残り時間.
    public float _countTime;

    // 最大カウント数を記録
    private int _countTimeRecord;

    // 文字列に変換.
    private string _count;

    // カウントダウンの桁.
    private string _column;

    // テキスト.
    private Text _countDownText;

    // 文字のサイズを変更する.
    private bool _stringSizeChange = false;

    // カウントが0かそうではないか.
    private bool _isCount = false;

    // カウントダウンするかどうか
    private bool _isCountDown = false;

    void Start()
    {
        // 繰り返し処理を呼び出す.
        StartCoroutine(RepeatFunction());

        _countTimeRecord = (int)_countTime;

        // テキスト関連.
        {
            // テキストを取得用.
            _countDownText = this.GetComponent<Text>();
            // サイズを変更.
            _countDownText.fontSize = 56;
        }

        _stringSizeChange = true;

        // カウントの桁数.
        _column = "00";
    }

    private void Update()
    {
        // カウントが10より小さくなったら0を減らす.
        if (_countTime < 10)
        {
            _column = "0";
        }

        // 数値を桁数指定で文字列に変換.
        _count = _countTime.ToString(_column);

        // 画面上のテキストを更新.
        _countDownText.text = _count;
    }

    private void FixedUpdate()
    {
        // 制限時間が10になった場合.
        if (_countTime < 10)
        {
            FontSizeFloat();
        }
        // 制限時間が0になった場合.
        if(_countTime <= 0)
        {
            FontSizeUp();
            _isCount = true;
        }
    }

    //繰り返し処理
    private IEnumerator RepeatFunction()
    {        
        while (true)
        {
            if (_isCountDown)
            {
                // 時間をカウントダウンする.
                _countTime -= Time.deltaTime;
            }

            // 経過時間が繰り返す間隔を経過したら.
            if (_countTime <= _repeatSpan)
            {
                //ここで処理をする.
                _countTime = 0.0f;
            }
            //次のフレームへ.
            yield return null;  
        }
    }

    // フォントのサイズを変更する.
    private void FontSizeFloat()
    {
        if (_stringSizeChange)
        {
            _countDownText.fontSize += 2;
            if (_countDownText.fontSize >= 56.0f * 2)
            {
                _stringSizeChange = false;
            }      
        }
        else
        {
            _countDownText.fontSize -= 2;
            if (_countDownText.fontSize <= 56.0f)
            {
                _stringSizeChange = true;
            }
        }
    }

    // カウント文字をでかくする.
    private void FontSizeUp()
    {
        _countDownText.fontSize += 3;
    }

    // カウントが0かどうか
    public bool IsCount()
    {
        return _isCount;
    }

    public void SstResetCount()
    {
        _countTime = _countTimeRecord;
        _isCount = false;
        _countDownText.fontSize = 56;
        _column = "00";
        _stringSizeChange = true;
    }

    public int GetCountTime()
    {
        return (int)_countTime;
    }

    // カウントダウンをするかどうか
    public void SetTimeCount(bool isCount)
    {
        _isCountDown = isCount;
    }
}
