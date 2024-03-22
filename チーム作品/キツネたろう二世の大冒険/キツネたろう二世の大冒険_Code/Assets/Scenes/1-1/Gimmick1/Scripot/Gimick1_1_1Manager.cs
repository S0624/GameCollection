using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick1_1_1Manager : MonoBehaviour
{
    // ハンドルの位置を変更.
    [SerializeField] private GameObject[] _handlePos;
    // ハンドルの判定.
    [SerializeField] private GameObject[] _handleColl;

    // ハンドルの近くでボタンをおしたかどうか.
    private bool[] _isButtonHandle = {false,false};
    // 壁の近くでボタンをおしたかどうか.
    private bool[] _isButtonWall = { false, false };
    // 回転を始める.
    private bool[] _isRota = { false, false };
    // 最後まで回転を行った.
    private bool[] _isEndRota = { false, false };
    // 1フレーム隙を与える.
    private bool[] _isOneFrameStop = { false, false };
    // 壁の名前.
    private string[] _handleWallName = {"HandleWall0","HandleWall1"};
    // fot文に使用する最大数.
    private int _maxNum;
    // ステージをクリアしたかどうか
    private bool _clear = false;

    // 説明を描画する
    private TipsDrawer _tips;

    private SoundManager _sound;

    public GenerateImg _image;

    private int _clearFrameCount = 0;
    [SerializeField] private PauseController _pauseController;
    void Start()
    {
        string objName = "3DPlayer";
        _handleColl[0].GetComponent<CollsionHandle>().SetNameColl(objName);
        _handleColl[1].GetComponent<CollsionHandle>().SetNameColl(objName);
        _maxNum = 2;

        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();

        _tips = GameObject.Find("Tips0").GetComponent<TipsDrawer>();
        _tips.IsDownSlider();

    }

    private void Update()
    {
        for (int i = 0; i < _maxNum; i++)
        {
            // ハンドルを入手していない場合.
            if (!_isButtonHandle[i])
            {
                // ハンドルに当たっていたら.
                if (_handleColl[i].GetComponent<CollsionHandle>().IsGetHit())
                {
                    // ボタンを押したら.
                    if (Input.GetKeyDown(KeyCode.JoystickButton1))
                    {
                        _sound.PlaySE("1_2_4_Light");
                        _isButtonHandle[i] = true;
                        _handleColl[i].GetComponent<CollsionHandle>().SetNameColl(_handleWallName[i]);
                        _handleColl[i].GetComponent<CollsionHandle>().SetHit(false);
                    }
                }
            }
            // ハンドルを入手した場合.
            if (_isButtonHandle[i] && !_isEndRota[i])
            {
                _handlePos[i].GetComponent<HandlePos>().HandlePosIsPlayer();
                if (_handleColl[i].GetComponent<CollsionHandle>().IsGetHit())
                {
                    // ボタンを押したら.
                    if (Input.GetKeyDown(KeyCode.JoystickButton1))
                    {
                        _sound.PlaySE("1_2_3_MetalRota");
                        _isButtonWall[i] = true;
                    }
                }
            }
            // ハンドルを差し込んだ場合.
            if (_isButtonWall[i] && !_isEndRota[i])
            {
                _handlePos[i].GetComponent<HandlePos>().HandlePosIsHandleWall(i);
                // 回転を始める.
                if (Input.GetKeyDown(KeyCode.JoystickButton1) && _isOneFrameStop[i])
                {
                    // 回転指示
                    _isRota[i] = true;
                }
                // 回転開始.
                if (_isRota[i])
                {
                    // 回転速度.
                    _handlePos[i].GetComponent<HandlePos>().Rota(1.0f);
                    // 回転時間.
                    if (_handlePos[i].GetComponent<HandlePos>().IsGetRotaTimeOver(300))
                    {
                        // 回転終了.
                        _isEndRota[i] = true;
                    }
                }
                // ボタンを一度とめる.
                _isOneFrameStop[i] = true;
            }
        }
    }

    private void FixedUpdate()
    {
        // 謎解きが終わったかどうか.
        if (_isEndRota[0] && _isEndRota[1])
        {
            _clearFrameCount++;            
            _image.GenerateCompleteImage();
        }

        if(_clearFrameCount > 60)
        {
//            _sound.StopBgm();
            _clear = true;
            _pauseController._getResult = _clear;
        }
    }
    // クリアしたかどうか
    public bool GetResult()
    {        
        return _clear;
    }
}

