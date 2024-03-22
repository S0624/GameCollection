using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

// カメラを揺らすスクリプト(テスト用)
public class CameraShake : MonoBehaviour
{
    // 揺らすカメラを持ってくる.
    [SerializeField] private GameObject _shakeScreen;
    private CinemachineVirtualCamera _cinemachineCamera;
    // 最初の位置
    private Vector3 _firstPos = Vector3.zero;
    // ランダムで生成した位置
    private Vector3 _randPos = Vector3.zero;
    private bool IsUndo = false;
    // Start is called before the first frame update
    void Start()
    {
        //_vCamera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_HorizontalAxis.Value = info.rota;
        _cinemachineCamera = _shakeScreen.GetComponent<CinemachineVirtualCamera>();

        _firstPos.x = _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenX;
        _firstPos.y = _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenY;
    }

    // カメラを動かす.
    public void ShekeUpdate(bool sheke)
    {
        if (sheke && !IsUndo)
        {
            //// テスト実装(あとできれいにする)
            _randPos.x = Random.Range(-0.1f, 0.1f);
            _randPos.y = Random.Range(-0.2f, 0.2f);
            // あとでまとめまｓ
            _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenX = _randPos.x + _firstPos.x;
            _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenY = _randPos.y + _firstPos.y;
        }
    }
    // カメラをもとに戻す.
    public void CameraUndo(bool undo)
    {
        if (undo)
        {
            _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenX = _firstPos.x;
            _cinemachineCamera.GetCinemachineComponent(CinemachineCore.Stage.Body).GetComponent<CinemachineFramingTransposer>().m_ScreenY = _firstPos.y;
        }
    }
}
