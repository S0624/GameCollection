using UnityEngine;
using Cinemachine;
using System;
// とりあえずコピペ
public class StageCamera : MonoBehaviour
{
    // カメラの位置情報.
    [Serializable]
    public struct TargetInfo
    {
        // カメラのがとらえる対象.
        public Transform follow;
        // カメラの角度.
        public float rota;
    }
    // カメラ関係.
    private CinemachineVirtualCamera _vCamera;
    private CinemachineComponentBase _vBase;
    private CinemachinePOV _vPOV;
    // 追従対象リスト.
    [SerializeField] private TargetInfo[] _targetList;
    // カメラの名前.
    private string _cameraName;
    // 初期化処理.
    void Start()
    {
        _vCamera = this.GetComponent<CinemachineVirtualCamera>();
        _vBase = _vCamera.GetCinemachineComponent(CinemachineCore.Stage.Aim);
        _vPOV = _vBase.GetComponent<CinemachinePOV>();
        var info = _targetList[0];
        _vCamera.Follow = info.follow;

        _cameraName = null;
    }
    
    // カメラの更新処理.
    public void CameraUpdate()
    {
        for (int count = 0; count < _targetList.Length; count++)
        {
            // リストの中身で一致する情報を入れる.
            if (_targetList[count].follow.name == _cameraName)
            {
                var info = _targetList[count];
                _vCamera.Follow = info.follow;
                _vPOV.m_HorizontalAxis.Value = info.rota;
            }
        }
    }
    // カメラの名前をもらってくる.
    public void SetCameraName(string name)
    {
        _cameraName = name;
    }
    // カメラの名前を返す.
    public string GetCameraName()
    {
        return _cameraName;
    }
}
