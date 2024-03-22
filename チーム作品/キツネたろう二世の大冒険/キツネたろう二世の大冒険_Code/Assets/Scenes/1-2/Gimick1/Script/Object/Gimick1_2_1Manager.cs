using UnityEngine;
// 1-2-1のゲームマネージャースクリプト.
public class Gimick1_2_1Manager : MonoBehaviour
{
    // プレイヤーの手.
    private GameObject _handObject;
    private PlayerHand _playerHand;
    // モニター前カメラ.
    private MonitorCamera _monitorCamera;
    // オブジェクトの管理しているマネージャー.
    private ObjectManagement _objectManagement;
    // ギミックのパネル（モニター）の取得.
    [SerializeField] private GameObject[] _panelObject;
    // ボタンの状態を管理するスクリプトクラス.
    private ButtonState[] _buttonState;
    // エフェクトの取得.
    private EffectPlay _effectPlay;
    // サウンドの取得.
    private SoundManager _sound;
    // 前フレームにいたモニターの場所の取得.
    private string _prevFrameName = null;
    // 今のフレームにいるモニターの場所の取得.
    private string _nowFrameName = null;

    // 初期化処理.
    private void Start()
    {
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        // カメラの取得.
        _monitorCamera = GameObject.Find("MonitorCamera").GetComponent<MonitorCamera>();
        // オブジェクトのマネージャー取得.
        _objectManagement = GetComponent<ObjectManagement>();
        // ボタンの状態を取得.
        _buttonState = new ButtonState[_panelObject.Length];
        for (int i = 0; i < _buttonState.Length; i++)
        {
            _buttonState[i] = _panelObject[i].GetComponent<ButtonState>();
        }
        // エフェクトの取得.
        _effectPlay = GameObject.Find("EffectCreate").GetComponent<EffectPlay>();
        // エフェクトの初期化処理.
        _effectPlay.EffectInit();
    }

    // 更新処理.
    private void Update()
    {
        // BGMの再生.
        _sound.PlayBGM("1_2_1_BGM");
        // プレイヤーの手の情報を取得する.
        _handObject = GameObject.Find("FoxHand(Clone)");
        // モニターを変えるかどうかをチェックしている
        _objectManagement.CameraChenge();
        // カメラのUpdate
        _monitorCamera.CameraUpdate();
        if (_handObject != null)
        {
            // プレイヤーの取得
            _playerHand = _handObject.GetComponent<PlayerHand>();
            // プレイヤーの手が存在していたら.
            if (_handObject.activeInHierarchy)
            {
                // プレイヤーの手がボタンを押したかどうか
                _playerHand.ButtonPush();
            }
            // 現在いる場所の取得.
            _nowFrameName = _monitorCamera.GetCameraName();
            // ボタン情報などの更新処理.
            ButtonUpdate();
            // 前のフレームにいた位置として保存.
            _prevFrameName = _nowFrameName;
        }
        // 画像を生成する.
        _effectPlay.GenaretaImg();
    }
    private void FixedUpdate()
    {
        if (_handObject != null)
        {
            // プレイヤーの手の移動処理
            _playerHand.MovePlayerHand();
        }
    }
    // ボタン情報などの更新処理
    private void ButtonUpdate()
    {
        foreach (ButtonState button in _buttonState)
        {
            if (button.name == _monitorCamera.GetCameraName())
            {
                // プレイヤーの手の情報を渡す.
                button.GetPlayerObject(_handObject);
                // ボタンの状態
                button.ButtonAcquisition();
                // エフェクトの更新.
                EffectUpdate(button);
            }
            // 現在いる位置と前フレームにいたモニターの場所が違ったら
            if (_prevFrameName != _nowFrameName)
            {
                // ボタンの情報をリセット.
                button.ButtnReset();
                // エフェクトをリセット.
                _effectPlay.EffectPosReset();
            }
        }
    }
    // エフェクト関連の処理.
    private void EffectUpdate(ButtonState button)
    {
        // パネルの名前を取得する.
        _effectPlay.GetPanelName(button.transform.name);
        // サウンドのデータを取得する.
        _effectPlay.GetSoundData(_sound);
        // 手の情報を取得する.
        _effectPlay.GetPlayerObject(_handObject);
        // ボタンを押されていたらエフェクトを生成する.
        _effectPlay.CheckTap(button.isCheckButton());
        // クリアしたときに五本目の線を表示させる.
        _effectPlay.EffectClearGenerete(button.IsGimckClear());
        // エフェクトをリセットする.
        _effectPlay.EffectDestory(button.IsResetFlag());
    }
    // プレイヤーの手の情報を返す.
    public GameObject SetHandObject()
    {
        return _handObject;
    }
}