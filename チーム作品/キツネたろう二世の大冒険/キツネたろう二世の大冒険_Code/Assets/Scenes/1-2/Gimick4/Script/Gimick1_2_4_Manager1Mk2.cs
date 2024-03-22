using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick1_2_4_Manager1Mk2 : MonoBehaviour
{
    // クリア後のフレームカウントの最大数
    static readonly int ClearCountMaxFrame = 60 * 3;
    // ゲームのリセット用カウント
    static readonly int GameOverCountMaxFrame = 60;

    // ワープするための変数
    private Gimick1_2_4_PlayerWarp _warp;
    private Gimick1_2_4_PlayerWarp _warpFirst;

    // 回転用.
    [SerializeField] GameObject[] _rota;

    // 回転用のクラスのメモリを確保
    private TurnGraph[] _rotaGraph = new TurnGraph[19];

    // 判定用.
    [SerializeField] GameObject[] _coll;

    // クリア後のライトを調整
    private GameObject _light;

    // 回転するオブジェクトの最大数.
    public int _objRotaMaxNum;

    // 謎解きがとけたかどうか.
    private bool _isClear = false;

    // 回路が正しい場合のカウント.
    private int _ansFrameCount = 0;

    // クリア後のカウント
    private int _clearFrameCount = 0;

    // クリア後カメラの位置を移動させる.
    private CinemachineVirtualCamera _camera;

    // クリア後カメラの位置をターゲット位置
    private GameObject _cameraData;
    private Transform _cameraPos;

    // クリア後のカメラ角度
    public float _clearCameraRotaY;
    public float _clearCameraRotaX;

    // サウンド
    private SoundManager _sound;
    private bool _isSoundStop = false;
    //[SerializeField] private PauseController _pauseController;

    // ライトが光るかどうか
    private bool _isLight = false;

    // カウントダウンを確認
    public GameObject _count;
    private Gimmick1_2_4_CountDown2 _countDown;

    // 時間制限内にクリアできなかった場合
    private int _gameOverFrameCount = 0;

    // ステージ全体をうつすかどうか
    private bool _isMap = false;

    // カウントダウンを止めるかどうか
    private bool _isCountDown = false;

    public GenerateImg _image;

    // 説明を描画
    public TipsDrawer _tipsDrawer;

    // Bボタンを押したかどうか.
    private bool _isBottomB = false;
    private int _collArry = 0;

    void Start()
    {
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();

        // 回転する回路のクラス
        for (int i = 0; i < _objRotaMaxNum; i++)
        {
            _rotaGraph[i] = _rota[i].GetComponent<TurnGraph>();
        }

        // 現在のステージのワープ先
        _warpFirst = GameObject.Find("Warp1").GetComponent<Gimick1_2_4_PlayerWarp>();

        // カメラ関連
        {
            // カメラオブジェクトを取得
            _camera = GameObject.Find("3DPlayerCamer").GetComponent<CinemachineVirtualCamera>();

            // カメラ用の位置データを取得
            _cameraData = GameObject.Find("AnsPos1");
            _cameraPos = _cameraData.transform;
        }

        // カウントダウンをするクラスを取得
        _countDown = _count.GetComponent<Gimmick1_2_4_CountDown2>();
        _countDown.SetTimeCount(true);        
    }

    void Update()
    {
        // サウンドを鳴らす(テスト).
        if (!_isSoundStop)
        {
            _sound.PlayBGM("1_1_2_BGM");
        }
        if (!_isLight)
        {
            _camera.Follow = GameObject.Find("3DPlayer").transform;
        }
        else
        {
            // カメラのターゲット位置と角度を変更
            _camera.Follow = _cameraPos;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_VerticalAxis.Value   = _clearCameraRotaY;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_HorizontalAxis.Value = _clearCameraRotaX;
        }

        // 回路が正しく接続されている数を確認.
        for (int i = 0; i < _objRotaMaxNum; i++)
        {
            if (!_rotaGraph[i].IsGetAns())
            {
                _ansFrameCount = 0;
                break;
            }
            else
            {
                // 最大値まで到達するとカウントを行わない.
                if (_ansFrameCount < _objRotaMaxNum)
                {
                    _ansFrameCount++;
                }
            }
        }


        if (!_isCountDown)
        {
            for (int i = 0; i < _objRotaMaxNum; i++)
            {
                if (_coll[i].GetComponent<MyCollsion3D>().IsGetHit())
                {
                    if (Input.GetKeyDown(KeyCode.JoystickButton1))
                    {
                        _isBottomB = true;
                        // サウンドを再生.
                        _sound.PlaySE("1_2_3_MetalRota");
                        _collArry = i;
                    }
                }
            }
        }

        // マップ全体を見る.
        MapDrawer();
        //_pauseController._getResult = _isClear;
        if (_isClear)
        {
            _sound.StopBgm();
            _isSoundStop = true;
        }
    }

    private void FixedUpdate()
    {
        _countDown.SetTimeCount(true);
        if (_countDown.IsCount())
        {
            // ゲームオーバーになるとカウントする
            _gameOverFrameCount++;
            // 
            if (_gameOverFrameCount > GameOverCountMaxFrame)
            {
                // ゲームオーバー用カウントを初期化する
                _gameOverFrameCount = 0;

                // カウントダウンを初期化する
                _countDown.SstResetCount();

                // 次のギミックの場所にワープする.
                _warpFirst.GetComponent<Gimick1_2_4_PlayerWarp>().NextStagePos();

                // 角度を初期化
                for (int i = 0; i < _objRotaMaxNum; i++)
                {
                    _rota[i].GetComponent<TurnGraph>().ResetRota();
                }
            }
        }

        // 全ての回路が正しく接続されている場合.
        if (_ansFrameCount == _objRotaMaxNum)
        {
            if(_clearFrameCount == 0)
            {
               _sound.PlaySE("1_2_4_Light");
            }

            _isCountDown = true;

            // クリア後少し間を開ける為のカウント.
            _clearFrameCount++;

            // 光った演出用のライトを表示させる.
            _isLight = true;

            // コンプリートを描画
            _image.GenerateCompleteImage();

            // カメラのターゲット位置と角度を変更.
            _camera.Follow = _cameraPos;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_VerticalAxis.Value = _clearCameraRotaY;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_HorizontalAxis.Value = _clearCameraRotaX;

            // 一定数カウントが値を御超えると.
            if (_isLight  && _clearFrameCount > ClearCountMaxFrame)
            {
                // クリアした場合のフラグを立てる
                _isClear = true;
            }
        }
    }

    // マップ全体を見る
    private void MapDrawer()
    {
        if (_isBottomB)
        {
            // 回転したら.
            _rota[_collArry].GetComponent<TurnGraph>().Rota();
            _isBottomB = false;
        }

        // Yを押した場合.
        if (Input.GetKeyDown(KeyCode.JoystickButton3))
        {
            _isMap = !_isMap;
        }

        // ステージ全体を見ているかどうか.
        if (_isMap)
        {
            // カメラのターゲット位置と角度を変更.
            _camera.Follow = _cameraPos;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_VerticalAxis.Value = _clearCameraRotaY;
            _camera.GetCinemachineComponent(CinemachineCore.Stage.Aim).GetComponent<CinemachinePOV>().m_HorizontalAxis.Value = _clearCameraRotaX;
        }
        else
        {
            if (!IsCountDown())
            {
                // カメラのターゲット位置と角度を変更.
                _camera.Follow = GameObject.Find("3DPlayer").transform;
            }
        }
    }

    // クリアしたかどうか.
    public bool GetResult()
    {
        return _isClear;
    }

    // ライトを光らせるかどうか
    public bool IsLight()
    {
        return _isLight;
    }

    // カウントダウンを止めるかどうか
    public bool IsCountDown()
    {
        return _isCountDown;
    }
}
