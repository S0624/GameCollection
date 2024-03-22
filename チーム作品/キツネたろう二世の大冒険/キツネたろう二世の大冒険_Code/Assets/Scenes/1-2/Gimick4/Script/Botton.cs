using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Botton : MonoBehaviour
{
    // 押してるかどうかを渡す.
    // トリガー判定用.
    private bool _isTrigger { get; set; }
    // 現在ボタンを押しているかどうか
    private bool _isTriggerActive = false;

    // Start is called before the first frame update.
    void Start()
    {
        // 押していない.
        _isTrigger = false;
    }

    // Update is called once per frame.
    void Update()
    {
        // 押していない.
        _isTrigger = false;
        // Bを押す
        if (Input.GetKey(KeyCode.JoystickButton1)) // B.
        {
            // 押していない場合は.
            if (!_isTriggerActive)
            {
                // 押した判定.
                _isTriggerActive = true;
                _isTrigger = true;
            }
        }
        else
        {
            // ボタンを押していなかったら.
            _isTriggerActive = false;
        }
    }
    // 押した瞬間の判定を渡す.
    public bool GetButtonB()
    {
        return _isTrigger;
    }
}
