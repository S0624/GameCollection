using UnityEngine;
// モニターの更新スクリプト.
public class MonitorCollider : MonoBehaviour
{
    public GameObject Pause;
    // プレイヤーが範囲内にいるかどうか.
    private bool _isPlayerCollider;
    // ボタンを押されたかどうか.
    private bool _isPushButton;
    // ボタンの状態を渡すためにオブジェクトを取得.
    private ObjectManagement _gameManager;
    // モニターのカメラオブジェクトの取得.
    private MonitorCamera _monitorObject;
    // どこのモニターを見ているかを保存する変数.
    private string _name;
    // ボタンの取得(UI).
    public GameObject _aButton;
    public GameObject _bButton;

    private void Start()
    {
        // 初期化処理.
        _isPlayerCollider = false;
        _isPushButton = false;

        // オブジェクトを取得.
        _gameManager = GameObject.Find("GameManager").GetComponent<ObjectManagement>();
        _monitorObject = GameObject.Find("MonitorCamera").GetComponent<MonitorCamera>();
    }

    private void Update()
    {
        if (Pause.GetComponent<UpdatePause>()._isPause) return;
        CameraFlag();
    }
    // カメラを切り替える処理
    public void CameraFlag()
    {
        // プレイヤーが判定内にいるとき.
        if (_isPlayerCollider)
        {
            // ボタンが押されたかどうかの処理をする.
            BottonPush();
            // プレイヤーが範囲内にいたらカメラの名前をセットする.
            _monitorObject.SetCameraName(_name);
            // ボタンが押されたかの状態を渡す.
            _gameManager.SetPushFlag(_isPushButton);
        }
    }
    // ボタンが押されたかどうかの処理.
    private void BottonPush()
    {
        // Aボタンを押したら.
        if (Input.GetKeyDown("joystick button 1"))
        {
            // ボタンのフラグをオンにする(カメラON).
            _isPushButton = true;
            _name = this.transform.name;
            // プレイヤーの手を生成する.
            _gameManager.PlayerHandGenerate(_name);
        }
        // Xボタンを押したら.
        else if (Input.GetKeyDown("joystick button 0"))
        {
            // ボタンのフラグをオフにする(カメラOFF).
            _isPushButton = false;
            _name = null;
            // プレイヤーの手を破壊する.
            _gameManager.PlayerHandDestory();
        }
        // ボタン(UI)の変更処理.
        ButtonUIActive();
    }
    // どちらのUIをアクティブにするか.
    private void ButtonUIActive()
    {
        if(_isPushButton)
        {
            _aButton.SetActive(true);
            _bButton.SetActive(false);
        }
        else
        {
            _aButton.SetActive(false);
            _bButton.SetActive(true);
        }
    }
    // 当たり判定の処理
    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            // プレイヤーがコライダーに入ったとき.
            _isPlayerCollider = true;

        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            // プレイヤーがコライダーから出たとき.
            _isPlayerCollider = false;
            // おされた場所のモニターがどこかを保存する.
            _name = null;
        }
    }
}
