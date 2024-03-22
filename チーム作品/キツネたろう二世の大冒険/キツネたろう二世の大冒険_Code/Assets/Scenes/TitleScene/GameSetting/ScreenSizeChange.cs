using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenSizeChange : MonoBehaviour
{
    private readonly int ScreenSizeX = 1920;
    private readonly int ScreenSizeY = 1080;

    // ウィンドウモードかどうか.
    private bool _isWindowMode;
    // ボタンを押しているかどうか.
    private bool _isPressKey;
    void Start()
    {
        // 指定したオブジェクトを削除しない.
        DontDestroyOnLoad(gameObject);

        _isWindowMode = false;
        _isPressKey = false;
    }

    void Update()
    {
        // ALT,ENTERでウィンドウモードを変更.
        if (Input.GetKey(KeyCode.LeftAlt) && !_isPressKey)
        {
            if (Input.GetKeyDown(KeyCode.Return))
            {
                _isPressKey = true;
                _isWindowMode = !_isWindowMode;
            }
        }
        else
        {
            _isPressKey = false;
        }

        Screen.SetResolution(ScreenSizeX, ScreenSizeY, _isWindowMode);
    }
}
