using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndRabbit : MonoBehaviour
{
    private const int kMoveFrame = 50 * 12;
    private const int kWaitFrame = kMoveFrame * 3;
    private const int kLapsNo = 2;

    private Vector3 _startPos;
    private Vector3 _move;
    int _frame;

    int _lapsNum;

    private void Start()
    {
        _startPos = transform.position;
        _move = new Vector3(-0.1f, 0, 0);
        _frame = kMoveFrame * 2;
        _lapsNum = 0;
    }

    public void RabbitUpdate()
    {
        // 周回数超えたら処理しない
        if (_lapsNum > kLapsNo) return;

        _frame++;

        if (_frame < kMoveFrame)
        {
            transform.position += _move;
        }
        else if (_frame < kWaitFrame)
        {
            // 何もしない    
        }
        else
        {
            _lapsNum++;
            _frame = 0;
            transform.position = _startPos;
        }
    }
}
