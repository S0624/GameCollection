using UnityEngine;
// 1-1-2のゲームシーンのマネージャースクリプト.
public class Gimick1_1_2_Manager : MonoBehaviour
{
    // 回転させるオブジェクトの取得.
    private GearRotation _gear;
    // サウンドの取得.
    private SoundManager _sound;
    // クリアしたときにclearの画像を表示させる.
    [SerializeField] private GenerateImg _img;
    // 一回転したら時間を計測するためのタイマー.
    private int _maxTime;
    private float _countTime;
    // タイマーが指定した時間に達したかのフラグ.
    private bool _isTimeFlag;
    // 一回転したかどうかのフラグ.
    private bool _isRotaFlag;

    public TipsDrawer _tipsDrawer;
    [SerializeField] private PauseController _pauseController;
    private void Start()
    {
        _gear = GameObject.Find("GearHandle").GetComponent<GearRotation>();
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        // 計測する時間の最大値.
        _maxTime = 60 * 2;
        // 実際にカウントする時間.
        _countTime = 0;

        _tipsDrawer.IsDownSlider();
    }

    // 60フレームに一回の更新処理.
    private void FixedUpdate()
    {
        // ギアを回転させる.
        _gear.GearRotate();
        // 一回転していたら時間を計測する.
        TimeCount();
    }
    // 更新処理.
    private void Update()
    {
        _gear.PlayerColRange();
        _isRotaFlag = _gear.IsGearRotated();
    }
    // クリアしていたら少し時間をおいてから処理をするための関数.
    private void TimeCount()
    {
        // 一回転していたら.
        if (_isRotaFlag)
        {
            // タイマーをカウントさせる.
            _countTime++;

            if (_countTime > _maxTime)
            {
                _isTimeFlag = true;
            }
        }
    }
    // シーン移行するための関数.
    public bool GetResult()
    {
        // 一回転していたら
        if (_isRotaFlag)
        {
            // 画像の表示.
            _img.GenerateCompleteImage();
        }
        // 指定した時間がたっていたらフェード処理をさせる.
        _pauseController._getResult = _isTimeFlag;
        return _isTimeFlag;
    }
}
