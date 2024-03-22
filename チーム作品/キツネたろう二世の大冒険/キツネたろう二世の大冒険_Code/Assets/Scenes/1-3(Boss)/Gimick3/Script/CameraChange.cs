using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class CameraChange : MonoBehaviour
{
    // ボタンを押したかの状態.
    private bool _isPushFlag;
    [SerializeField] private CinemachineVirtualCamera _minMapCameraObject;
    [SerializeField] private CinemachineVirtualCamera _wallCameraObject;


    // Start is called before the first frame update
    void Start()
    {
        _isPushFlag = true;
    }

    public void ChengeCameraUpdate()
    {
        // ボタンの状態によって分岐させる.
        if (_isPushFlag)
        {
            // カメラを動かす.
            _minMapCameraObject.Priority = 3;
        }
        else
        {
            // カメラを動かす.
            _minMapCameraObject.Priority = 15;
        }
        if (Input.GetKeyDown("joystick button 3"))
        {
            _isPushFlag = !_isPushFlag;
        }
    }
    // 壁を見せるカメラ起動.
    public void WallCameraChenge()
    {
        _wallCameraObject.Priority = 50;
    }
    // 壁を見せるカメラoff.
    public void WallCameraOff()
    {
        _wallCameraObject.Priority = 0;
    }
    public void SetPushFlag(bool ispush)
    {
        _isPushFlag = ispush;
    }
}
