using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick1_3_3Manager : MonoBehaviour
{
    // サウンド用.
    private SoundManager _sound;
    // クリアしたときにclearの画像を表示させる.
    [SerializeField] private GenerateImg _img;
    [SerializeField] private GameObject Pause;
    // オブジェクトの取得
    private CameraChange _cameraChange;
    private StageCamera _stageCamera;
    private ContainerDirector _containerDirector;
    private Reset_Button _resetButton;
    [SerializeField] private GameObject _wallEffect;
    private GameObject _effectClone;
    //バリケードを取得.
    GameObject _barricade;
    // バリケードを消したかどうかのフラグ.
    private bool _isDestory;
    private Vector3 _effectPos;
    // サウンドを鳴らしたかのフラグ.
    private bool _isSound = false;
    // 待つフレーム.
    private int _frameWaitTime = 60;
    public TipsDrawer _tipsDrawer;
    [SerializeField] private PauseController _pauseController;
    // Start is called before the first frame update
    void Start()
    {
        //_barricade = GameObject.Find("Barricade");
        _cameraChange = GetComponent<CameraChange>();
        _stageCamera = GameObject.Find("MinmapCamera").GetComponent<StageCamera>();
        _containerDirector = GameObject.Find("Container Director").GetComponent<ContainerDirector>();
        _resetButton = GameObject.Find("Reset_Button").GetComponent<Reset_Button>();
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        // バリケード初期位置を取得.
        //_effectPos = _barricade.transform.position;
        //_effectPos.x -= -1.0f;
        //_effectPos.y -= (_barricade.transform.localScale.y * 0.5f);
        _resetButton.SoundDataSet(_sound);
        _containerDirector.GetSoundData(_sound);

        _tipsDrawer.IsDownSlider();

    }

    // Update is called once per frame
    private void Update()
    {
        if (!Pause.GetComponent<UpdatePause>()._isPause)
        {
            _cameraChange.ChengeCameraUpdate();
            _stageCamera.CameraUpdate();
        }
        // リセットの処理.
        _resetButton.ResetPush(_containerDirector.IsStage1Clear());
        _containerDirector.ResetBoxPos(_resetButton.IsReset());
        _containerDirector.GimickClearCheck();
        //if (_containerDirector.IsStage1Clear() && !_isDestory)
        //{
        //    if (!_isSound)
        //    {
        //        _isSound = true;
        //        _sound.PlaySE("1_3_3_WallDown");
        //    }
        //    // 壁に関する処理.
        //    WallUpdate();
        //}
    }
    //// 壁に関する処理.
    //private void WallUpdate()
    //{
    //    _cameraChange.WallCameraChenge();
    //    _barricade.gameObject.transform.position += new Vector3(0, -0.02f, 0);
    //    // エフェクトの生成
    //    WallEffectPlay();
    //    // HACK ちょっと実装お試しです
    //    // 壁が下りたら壁とカメラを破壊する
    //    if (_barricade.transform.position.y < -6.5)
    //    {
    //        _cameraChange.WallCameraOff();
    //        _isDestory = true;
    //        EfeectStop();
    //        Destroy(_barricade);
    //    }
    //}
    //// 壁のエフェクト生成.
    //private void WallEffectPlay()
    //{
    //    if (_effectClone == null)
    //    {
    //        _effectClone = Instantiate(_wallEffect,
    //                         _effectPos,
    //                         _barricade.transform.rotation);
    //    }
    //}
    private void EfeectStop()
    {
        if(_effectClone != null)
        {
            Destroy(_effectClone);
        }
    }
    public bool GetResult()
    {
        if (_containerDirector.GetClearFlag())
        {
            _frameWaitTime--;
            // 画像の生成.
            _img.GenerateCompleteImage();
            if (_frameWaitTime <= 0)
            {
                _pauseController._getResult = true;
                return true;
            }
        }
        return false;
    }
}
