using UnityEngine;
using UnityEngine.UI;

public class ResetButton : MonoBehaviour
{
    //それぞれのオブジェクト.
    [SerializeField] private GameObject[] _resetPos;
    private Vector3[] _respawnPos;
    //それぞれのオブジェクトの位置.
    [SerializeField] private GameObject _player;
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
        Debug.Log($"{name}");
        _respawnPos = new Vector3[_resetPos.Length];
        //それぞれのオブジェクトの初期位置を保存.
        for (int i = 0; i < _resetPos.Length; i++)
        {
            _respawnPos[i] = _resetPos[i].transform.position;
        }
    }
    public void SoundDataSet(SoundManager sound)
    {
        _sound = sound;
    }
    // リセットボタンを押したときの処理.
    public void ResetPush()
    {
        if (Input.GetKey(KeyCode.F) || Input.GetKey("joystick button 2"))
        {
            if (!_isResetCheck)
            {
                ResetGauge();
            }
        }
        else
        {
            Gauge.transform.GetChild(0).GetComponent<Image>().fillAmount = 0;
            _resetCount = 0;
            _isResetCheck = false;
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
            ResetPosition();
        }
    }
    private void ResetPosition()
    {
        for (int i = _count; i < _resetPos.Length; i++)
        {
            //_player.transform.position = _respawnPos[i];

        }
    }
    // リセットボタンを押したかのフラグを返す.
    public bool IsReset()
    {
        return _isResetCheck;
    }

}
