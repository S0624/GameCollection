using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ContainerDirector : MonoBehaviour
{
    // ギミックの管理に使用.
    [SerializeField] private List< bool> _gimickClears = new List<bool>();
    // HACK めっちゃよくない書き方してる自覚はあります.
    // ギミックをクリアしたとき一回だけならしたい.
    [SerializeField] private List< bool> _gimickPrevFlag = new List<bool>();

    //[SerializeField] private Dictionary<int, bool> _gimickClears = new Dictionary<int, bool>();
    //[SerializeField] private Dictionary<int, Dictionary<string,bool>> _gimickClear = new Dictionary<int, Dictionary<string, bool>>();
    // ギミックの名前を取得する用の配列.
    [SerializeField] private GameObject[] _gimickName = new GameObject[0];
    //クリア数カウント.
    public static string _getName;
    public static bool _isColl;
    //クリアに必要なカウント数.
    //private int _Maxcount = 8;
    // 何個目から始めるか
    private int _countBox = 0;
    //Stage2に行くためのカウント.
    private int _stage2_Count = 4;
    // 一回クリア判定.
    private bool _isStage1Flag = false;
    // 全てクリアしているかのフラグ.
    private bool _isAllClear;
    private SoundManager _sound = null;

    // Start is called before the first frame update
    void Start()
    {
        //_getName = 0;
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        _isAllClear= false;
        GetGimickName();
    }
    public void GetSoundData(SoundManager sound)
    {
        _sound = sound;
    }
    // ギミックの名前を取得.
    // ギミックの正誤を初期化.
    private void GetGimickName()
    {
        for (int i = 0; i < _gimickName.Length; i++)
        {
            _gimickClears.Add(false);
            _gimickPrevFlag.Add(false);
            //_gimickClears.Add(i, false);
        }
    }

    // ギミックのクリア判定のチェック
    public void GimickClearCheck()
    {
        for (int i = 0; i < _gimickClears.Count; i++)
        {
            if (_gimickName[i].name == _getName)
            {
                _gimickClears[i] = _isColl;
                // サウンドが鳴らせるかどうか.
                BoxInSoundPlay(_gimickClears[i], _gimickPrevFlag[i]);
                _gimickPrevFlag[i] = _gimickClears[i];
            }
        }
        // クリア判定.
        _isAllClear = IsGimickAllClear();
    }
    // 一回だけサウンドを鳴らす処理.
    private void BoxInSoundPlay(bool nowFlag,bool prevFlag)
    {
        if(nowFlag != prevFlag && nowFlag)
        {
            _sound.PlaySE("1_3_3_InBox");
        }
    }
    // 箱の位置をリセットする処理.
    public void ResetBoxPos(bool isReset)
    {
        if(isReset)
        {
            // ステージ1をクリアしていたらリセットしない.
            if(_isStage1Flag)
            {
                _countBox = _stage2_Count;
            }
            else
            {
                _countBox = 0;
            }
            for (int i = _countBox; i < _gimickClears.Count; i++)
            {
                _gimickClears[i] = false;
            }
        }
    }


    // ギミックをクリアしたかどうか.
    private bool IsGimickAllClear()
    {
        for (int i = 0; i < _gimickClears.Count; i++)
        {
            if (_gimickClears[i] == false)
            {
                return false;
            }
            //// ステージ1をクリアした(0の分をカウントするために1つたす).
            //if (i + 1 >= _stage2_Count)
            //{
            //    _isStage1Flag = true;
            //}
        }
        return true;
    }
    public bool IsStage1Clear()
    {
        return _isStage1Flag;
    }
    // クリア判定.
    public bool GetClearFlag()
    {
        return _isAllClear;
    }
}
