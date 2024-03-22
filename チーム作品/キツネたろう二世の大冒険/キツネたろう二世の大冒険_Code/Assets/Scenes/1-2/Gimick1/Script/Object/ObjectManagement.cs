using UnityEngine;
using Cinemachine;
using System;
// カメラのオンオフの切り替え&手の生成.
public class ObjectManagement : MonoBehaviour
{
    // プレイヤーの手の生成に使用.
    [SerializeField] private GameObject PlayerHand = default;
    // ボタンを押したかの状態.
    private bool _isPushFlag;
    // ゲームオブジェクトを取得する
    public GameObject _monitorCameraObject;
    public GameObject _playerObject;
    private GameObject _handObject;
    public CinemachineVirtualCamera _vcamera;

    public TipsDrawer _tipsDrawer;


    // ターゲットのリストの管理.
    [Serializable] public struct TargetInfo
    {
        // モニターの名前.
        public Transform name;
        // 手の生成位置.
        public Transform hand;
    }

    // 追従対象リスト
    [SerializeField] private TargetInfo[] _targetList;
    // カメラをチェンジさせる.
    private void Start()
    {
        _tipsDrawer.IsDownSlider();
    }
    public void CameraChenge()
    {
        // ボタンの状態によって分岐させる.
        if (_isPushFlag)
        {
            // モニター前のカメラをオンにする(値が大きいほうがメインカメラになるので大きい値を代入).
            _vcamera.Priority = 15;
            // プレイヤーを非表示にする
            _playerObject.gameObject.SetActive(false);
        }
        else
        {
            // モニター前のカメラをオフにする(値が小さいほうがメインカメラにならないので小さい値を代入).
            _vcamera.Priority = 5;
            _playerObject.gameObject.SetActive(true);
        }
    }
    // プレイヤーの手の生成.
    public void PlayerHandGenerate(string name)
    {
        if (_handObject == null)
        {
            for (int i = 0; i < _targetList.Length; i++)
            {
                // リストの中身と名前が一致していたら手を生成する.
                if (_targetList[i].name.name == name)
                {
                    var info = _targetList[i];
                    _handObject = Instantiate(PlayerHand,
                        info.hand.transform.position,
                        info.hand.transform.rotation * PlayerHand.transform.rotation);
                }
            }
        }
    }
    // プレイヤーの手を削除する.
    public void PlayerHandDestory()
    {
        if (_handObject != null)
        {
            Destroy(_handObject);
        }
    }
    // ボタンが押されたかのフラグを取得する.
    public void SetPushFlag(bool ispush)
    {
        _isPushFlag = ispush;  
    }
}
