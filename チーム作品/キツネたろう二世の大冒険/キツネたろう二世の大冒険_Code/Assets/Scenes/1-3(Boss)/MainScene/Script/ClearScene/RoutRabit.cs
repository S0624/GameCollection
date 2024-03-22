/*敗走するウサギ*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoutRabit : MonoBehaviour
{
    // クリアシーンマネージャー.
    private ClearSceneManager _manager;

    // 初期位置.
    public GameObject _initialPosition = null;
    // アニメーション.
    private Animator _animator;
    // ジャンプモーション.
    private bool _jumpMotion = false;

    // 現在のインターバル
    private int _currentInterval = 0;
    // 動ける時間.
    private int _moveTime = 12;
    // 動けない時間.
    private int _dontMoveTime = 2;
    // 一連の動きの最大時間.
    private int _moveMaxtime = 15;

    // ジャンプするスピード.
    private float _jumpSpeed = 5;

    void Start()
    {
        _animator = GetComponent<Animator>();
        _manager = GameObject.Find("GameManager").GetComponent<ClearSceneManager>();
    }


    private void FixedUpdate()
    {
        Anim();
        if(_manager._currentTime <= 120)
        {
            InitialPosition();
        }
        else if(_manager._currentTime >= 121)
        {
            _jumpMotion = true;
            AnimMove();
        }
    }

    // ウサギの初期位置
    private void InitialPosition()
    {
        transform.position = _initialPosition.transform.position;
    }

    // アニメーション移動.
    private void AnimMove()
    {
        _currentInterval++;

        if(_currentInterval < _moveTime && _currentInterval > _dontMoveTime)
        {
            transform.position -= new Vector3(0.5f,0.2f,0.0f);
        }
        else if(_currentInterval > _moveMaxtime)
        {
            _currentInterval = 0;
        }

        if(transform.position.y < 0.0f)
        {
            transform.position = new Vector3(transform.position.x, 0.0f, transform.position.z);
        }
    }

    // アニメーション.
    private void Anim()
    {
        _animator.SetBool("Jump", _jumpMotion);
        _animator.SetFloat("JumpSpeed", _jumpSpeed);
    }
}
