using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class piston : MonoBehaviour
{
    // 秒数を数えるカウント.
    private int _count;
    //Transformを取得.
    private Transform _myTransform;
    // 座標を取得.
    private Vector3 _pos;
    // 5秒の時間.
    private int _time;
    // ギミックの移動量
    private float _moveX;

    private bool _isMove;
    void Start()
    {
        _count = 0;
        _myTransform = this.transform;
        _pos = _myTransform.position;
        _time = 60;
        _moveX = 0.08f;
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // 5秒経ったら.
        if (!_isMove)
        {
            // z座標へ0.08減算.
            _pos.x -= _moveX;
            // 座標を設定.
            _myTransform.position = _pos;
        }
        else
        {
            // z座標へ0.08加算.
            _pos.x += _moveX;
            // 座標を設定.
            _myTransform.position = _pos;
        }
        if(_myTransform.position.x >= 15.0)
        {
            _isMove = false;
        }
        if (_myTransform.position.x <= 10.0)
        {
            _isMove = true;
        }
    }
}
