using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Reset_Button : MonoBehaviour
{
    //それぞれのオブジェクト.
    [SerializeField] private GameObject[] _stageContainer;
    //それぞれのオブジェクトの位置.
    [SerializeField] private Vector3[] _containeInitialPositionr;
    private int _count = 0;

    // ゲージ入れるよう
    [SerializeField] private GameObject Gauge;

    // リセットするカウント.
    private int _resetCount = 0;
    // リセットする最大秒数
    private readonly static int _resetMaxCount = 45;
    // リセットしたフラグ
    private bool _isResetCheck = false;
    private SoundManager _sound;

    void Start()
    {
        //それぞれのオブジェクトの初期位置を保存.
        for (int i = 0; i < _stageContainer.Length; i++)
        {
            _containeInitialPositionr[i] = _stageContainer[i].transform.position;
        }

        //_sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
    }
    public void SoundDataSet(SoundManager sound)
    {
        _sound = sound;
    }
    // リセットボタンを押したときの処理.
    public void ResetPush(bool isClear)
    {
        if (Input.GetKey(KeyCode.F) || Input.GetKey("joystick button 1"))
        {
            if (isClear)
            {
                _count = 4;
            }
            else
            {
                _count = 0;
            }
            if (!_isResetCheck)
            {
                ResetGauge();
            }
        }
        else
        {
            Gauge.transform.GetChild(0).GetComponent<Image>().fillAmount = 0;
            _resetCount = 0;
            _isResetCheck  = false;
        }
    }
    private void ResetGauge()
    {
        _resetCount++;
        Gauge.transform.GetChild(0).GetComponent<Image>().fillAmount = (float)_resetCount / (float)_resetMaxCount;
        if (_resetCount > _resetMaxCount)
        {
            _isResetCheck = true;
            // サウンドを鳴らす.
            _sound.PlaySE("1_3_1_Reset");
            ResetBox();
        }
    }
    private void ResetBox()
    {
        for (int i = _count; i < _stageContainer.Length; i++)
        {
            _stageContainer[i].transform.position = _containeInitialPositionr[i];

        }
    }
    // リセットボタンを押したかのフラグを返す.
    public bool IsReset()
    {
        return _isResetCheck;
    }

    private void Move()
    {
        //this.gameObject.transform.position += ;
    }
}
