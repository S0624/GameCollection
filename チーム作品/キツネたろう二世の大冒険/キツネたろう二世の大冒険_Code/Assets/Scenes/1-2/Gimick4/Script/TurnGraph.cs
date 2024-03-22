using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class TurnGraph : MonoBehaviour
{
    // 回転命令.
    private bool _connected = false;
    // 回転量.
    private int _rota = 0;
    // 回転量保存.
    private float _tempRota = 0.0f;
    // 正解の角度.
    public int _ansRota;
    // 正解が無い偽物の場合.
    public bool _isFake;

    // 回転した回数をカウントする
    private int _isRotaCount = 0;

    void Update()
    {
        // ボタンが押されたら.
        if (_connected)
        {
            if(_isRotaCount == 4)
            {
                _isRotaCount = 0;
            }

            // 90度回転したら止める.
            if (_rota >= _tempRota + 90.0f)
            {
                _connected = false;
                _tempRota = _rota;
                _isRotaCount++;
            }
            else
            {
                // 回転させる.
                _rota += 5;
                this.transform.rotation = Quaternion.Euler(0.0f, _rota, 0.0f);
            }
        }

        // 360度回転したら0度に戻す.
        if (_tempRota >= 360.0f)
        {
            _rota = 0;
            _tempRota = 0.0f;
        }
    }

    // 回転を有効にする.
    public void Rota()
    {
        _connected = true;
    }

    // 回転結果が正解だったらtrue.
    public bool IsGetAns()
    {
        if (_isFake) return true;

        if (_ansRota == _isRotaCount)
        {
            return true;
        }

        return false;
    }

    public float tempAngle()
    {
        return _tempRota;
    }

    public void ResetRota()
    {
        _isRotaCount = 0;
        _rota = 0;
        _tempRota = 0.0f;
        _connected = false;
        this.transform.rotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
    }
}
