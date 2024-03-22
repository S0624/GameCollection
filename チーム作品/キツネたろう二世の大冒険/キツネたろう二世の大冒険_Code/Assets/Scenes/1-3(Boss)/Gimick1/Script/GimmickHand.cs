using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class GimmickHand : MonoBehaviour
{
    // 手の動く速度
    private const float kSpeed = 0.09375f;
    // 上下左右の上限
    private const float kRightLimit = 8.0f;
    private const float kLeftLimit = -6.4f;
    private const float kUpLimit = 12.0f;
    private const float kDownLimit = 2.0f;

    private int _hitNo;
    private GameObject _directer;
    // スティック情報
    private float _horizontal;
    private float _vertical;

    private Vector3 _limitPos;

    public int HitNo { get { return _hitNo; } }

    void Start()
    {
        _hitNo = 15;
        _directer = GameObject.Find("GameManager");

        _limitPos = transform.position;
    }

    bool _isStay = false;

    private void OnTriggerStay(Collider other)
    {
        if (!_isStay)
        {
            _hitNo = int.Parse(other.name);

            _directer.GetComponent<SlideGimmickDirector>().OnLight(_hitNo);

            _isStay = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        _isStay = false;
        _directer.GetComponent<SlideGimmickDirector>().OffLight(_hitNo);
    }

    public void HandUpdate()
    {
        // 垂直方向.
        _horizontal = Input.GetAxis("Horizontal");
        // 水平方向.
        _vertical = Input.GetAxis("Vertical");

        // プレイヤーの手の移動処理.
        if (_horizontal != 0.0f)
        {
            transform.position += Vector3.right * kSpeed * _horizontal;
            if (transform.position.x > kRightLimit)
            {
                _limitPos.x = kRightLimit;
                _limitPos.y = transform.position.y;

                transform.position = _limitPos;
            }
            if (transform.position.x < kLeftLimit)
            {
                _limitPos.x = kLeftLimit;
                _limitPos.y = transform.position.y;

                transform.position = _limitPos;
            }
        }

        if (_vertical != 0.0f)
        {
            transform.position += Vector3.up * kSpeed * _vertical;
            if (transform.position.y > kUpLimit)
            {
                _limitPos.x = transform.position.x;
                _limitPos.y = kUpLimit;

                transform.position = _limitPos;
            }
            if (transform.position.y < kDownLimit)
            {
                _limitPos.x = transform.position.x;
                _limitPos.y = kDownLimit;

                transform.position = _limitPos;
            }
        }
    }
}
