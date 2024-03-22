using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class scaffold_Move : MonoBehaviour
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
    private float _moveZ;

    public GameObject _player;

    private bool _isMove;

    // それぞれの最大値.
    private Vector3 _rightPosition;
    private Vector3 _leftPosition;

    // 一番上か一番下に行った時の処理.
    private int _waitTimer = 0;
    // 待つ最大フレーム
    [SerializeField] private int _waitTimeMax = 75;
    private Vector3 _playerScale = Vector3.zero;

    void Start()
    {
        _count = 0;
        _myTransform = this.transform;
        _pos = _myTransform.position;
        _time = 300;
        _moveZ = 0.08f;
        _isMove = false;
        _rightPosition = new Vector3(this._myTransform.position.x, this._myTransform.position.y, 15.0f);
        _leftPosition = new Vector3(this._myTransform.position.x, this._myTransform.position.y, -7.0f);
        _playerScale = new Vector3(_player.transform.lossyScale.x, _player.transform.lossyScale.y, _player.transform.lossyScale.z);
    }
    
    // Update is called once per frame
    void FixedUpdate()
    {
        //5秒経ったら.
        if (!_isMove)
        {
            // z座標へ0.08減算.
            _pos.z += _moveZ;
            // 座標を設定.
            _myTransform.position = _pos;  
        }
        //10秒経ったら.
        else
        {
            // z座標へ0.08加算.
            _pos.z -= _moveZ;
            // 座標を設定.
            _myTransform.position = _pos;  
        }
        MoveOverControl();
    }
    private void MoveOverControl()
    {
        // 最大値より上に行かないようにする処理.
        if (_myTransform.position.z <= _leftPosition.z)
        {
            _myTransform.position = _leftPosition;
            if (TimerWait())
            {
                _isMove = false;
            }
        }
        // 最大値より下に行かないようにする処理.
        if (_myTransform.position.z >= _rightPosition.z)
        {
            _myTransform.position = _rightPosition;
            if (TimerWait())
            {
                _isMove = true;
            }
        }
    }
    // 一番下か一番上に行ったとき数秒待つ処理.
    private bool TimerWait()
    {
        _waitTimer++;
        if (_waitTimer > _waitTimeMax)
        {
            _waitTimer = 0;
            return true;
        }
        return false;

    }
    void OnCollisionStay(Collision collision)
    {
        Debug.Log("HitOutSidee");
        if (collision.gameObject.tag == _player.tag)
        {
            Debug.Log("Hit");
            _player.transform.SetParent(gameObject.transform);
            _player.transform.localScale = _playerScale;

            _player.transform.localScale = new Vector3(
                transform.localScale.x / transform.lossyScale.x * _playerScale.x,
                transform.localScale.y / transform.lossyScale.y * _playerScale.y,
                transform.localScale.z / transform.lossyScale.z * _playerScale.z);
        }
    }

    void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.tag == _player.tag)
        {            
            _player.transform.parent = null;
        }
    }
}
