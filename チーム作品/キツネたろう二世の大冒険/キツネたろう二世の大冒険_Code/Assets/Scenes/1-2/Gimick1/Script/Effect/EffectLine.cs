using System.Collections.Generic;
using UnityEngine;

// 線のエフェクトを管理するスクリプト.
public class EffectLine : MonoBehaviour
{
    // オブジェクトの取得.
    [SerializeField] private GameObject Line = default;
    [SerializeField] private GameObject[] _lineName;
    // エフェクト.
    private GameObject[] _effectLine = new GameObject[3];
    // LineRendererの取得.
    private LineRenderer[] _lineRenderer = new LineRenderer[3];
    // ポジションを覚えておく配列.
    private List<Vector3>_pointList = new List<Vector3>();
    // ゲームクリアのフラグ.
    private bool _isGameClear = false;
    // 線の最大値.
    private int _lineMax = 5;
    private float _time = 0;
    [SerializeField] private PauseController _pauseController;
    // エフェクトの初期化.
    public void LineInit()
    {
        for (int i = 0; i < _lineName.Length; i++)
        {
            // 初期化処理
            _effectLine[i] = Instantiate(Line, this.transform.position,
                                        Quaternion.identity); // 初期化処理
                                                              // LineRenderer取得
            _lineRenderer[i] = _effectLine[i].GetComponent<LineRenderer>();
        }
    }
    // エフェクトを再生成する処理.
    private void Regeneration(string name)
    {
        for (int i = 0; i < _lineName.Length; i++)
        {
            if (_lineName[i].name == name)
                // 初期化処理
                _effectLine[i] = Instantiate(Line, this.transform.position,
                                            Quaternion.identity);
            // LineRenderer取得
            _lineRenderer[i] = _effectLine[i].GetComponent<LineRenderer>();
        }
    }
    // 線のポジションを加えていく処理.
    private void LinePosAdd(Vector3 pos,int linenum)
    {
        _pointList.Add(pos);
        _lineRenderer[linenum].positionCount = _pointList.Count;

        // 各頂点の座標設定
        for (int iCnt = 0; iCnt < _pointList.Count; iCnt++)
        {
            _lineRenderer[linenum].SetPosition(iCnt, _pointList[iCnt]);
        }
    }
    // ラインエフェクトの生成.
    public void LineGenerate(Vector3 pos,string name)
    {
        for (int i = 0; i < _lineName.Length; i++)
        {
            if (name == _lineName[i].name)
            {
                LinePosAdd(pos,i);
            }
        }
    }
    // クリアしたときに出す六番目の線の生成.
    public void LineClearGenerete(string name)
    {
        for (int i = 0; i < _lineName.Length; i++)
        {
            if (name == _lineName[i].name)
            {
                if (_lineRenderer[i].positionCount <= _lineMax)
                {
                    LinePosAdd(_pointList[0], i);
                    _pointList.Clear();

                }
            }
        }
    }
    // 線をすべて壊す.
    public void LineDestroy(string name)
    {
        for (int i = 0; i < _lineName.Length; i++)
        {
            if (name == _lineName[i].name)
            {
                // 完成していたら消さない
                if (_lineRenderer[i].positionCount <= _lineMax)
                {
                    _pointList.Clear();
                    Destroy(_effectLine[i]);
                    Destroy(_lineRenderer[i]);
                    // 再生成する.
                    Regeneration(name);
                }
            }
        }
    }
    // 記憶しているポジションをすべて消す.
    public void PosAllErase(string name)
    {
        LineDestroy(name);
    }
    // ラインを最後まで引いたかどうか.
    public void LineEndDraw()
    {
        int endCount = 0;
        for (int i = 0; i < _lineName.Length; i++)
        {
            if (_lineRenderer[i].positionCount == 6)
            {
                endCount++;
            }
        }
        if(endCount == _lineRenderer.Length)
        {
            _isGameClear  = true;
        }
    }
    // ゲームをクリアしたかのフラグ.
    public bool GetResult()
    {
        _pauseController._getResult = IsTimeCount();
        return IsTimeCount();
    }
    public bool GetClearFlag()
    {
        return _isGameClear;
    }
    private bool IsTimeCount()
    {
        if (_isGameClear)
        {
            _time++;
        }
        if(_time > 60*1.5)
        {
            return true;
        }
        return false;
    }
}
