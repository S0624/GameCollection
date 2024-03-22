using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class MonitorCamera131 : MonoBehaviour
{
    // ボタンを押したかの状態.
    private bool _isPushFlag;
    // ゲームオブジェクトを取得する
    public GameObject _playerObject;
    public CinemachineVirtualCamera _monitorCameraObject;
    public GameObject _handObject;
    public GameObject _changeImage;
    public GameObject Canvas;

    // Start is called before the first frame update
    void Start()
    {
        _isPushFlag = true;
    }

    private void Update()
    {
        // ボタンの状態によって分岐させる.
        if (_isPushFlag)
        {
            // 通常状態での動作関係をActiveに
            _playerObject.gameObject.SetActive(true);
            // 絵合わせ状態での動作関係をNonActiveに
            _handObject.gameObject.SetActive(false);
            _changeImage.SetActive(false);
            Canvas.SetActive(false);
            // カメラを動かす
            _monitorCameraObject.Priority = 3;
        }
        else
        {
            // 通常状態での動作関係をNonActiveに
            _playerObject.gameObject.SetActive(false);
            // 絵合わせ状態での動作関係をActiveに
            _handObject.gameObject.SetActive(true);
            _changeImage.SetActive(true);
            Canvas.SetActive(true);
            // カメラを動かす
            _monitorCameraObject.Priority = 15;
        }
    }

    public void SetPushFlag()
    {
        _isPushFlag = !_isPushFlag;
    }
}
