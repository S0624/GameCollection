using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class TitleSelect : MonoBehaviour
{
    // GameStartとOption
    private const int kSelectNum = 2;
    // 上下の幅(Main)
    private const float kMainRangeY = -192.0f;
    // 上下の幅(Option)
    private const float KOptionRangeY = 160f;

    public SoundManager SndManager;

    public bool IsMain;

    private int _index;
    private bool _isUpPush;
    private bool _isDownPush;

    Vector3 _move;

    RectTransform _rect;
    
    void Start()
    {
        _index = 0;
        _isUpPush = false;

        _move = new Vector3();

        _rect = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    public void SelectUpdate()
    {
        if (Input.GetAxisRaw("Vertical") == 1)
        {
            if (!_isUpPush)
            {
                _isUpPush = true;
                _index = (kSelectNum + _index - 1) % kSelectNum;

                MoveFrame();
            }
        }
        else
        {
            _isUpPush = false;
        }

        if (Input.GetAxisRaw("Vertical") == -1)
        {
            if (!_isDownPush)
            {
                _isDownPush = true;
                _index = (_index + 1) % kSelectNum;

                MoveFrame();
            }
        }
        else
        {
            _isDownPush = false;
        }
    }

    private void MoveFrame()
    {
        SndManager.GetComponent<SoundManager>().PlaySE("1_3_1_Reset");

        if (_index == 0)
        {
            if (IsMain)
            {
                _move.y = kMainRangeY;
            }
            else
            {
                _move.y = KOptionRangeY;
            }
        }
        else
        {
            if (IsMain)
            {
                _move.y = -kMainRangeY;
            }
            else
            {
                _move.y = -KOptionRangeY;
            }
        }

        _rect.localPosition += _move;
    }

    public int GetIndex() 
    {
        return _index; 
    }
}
