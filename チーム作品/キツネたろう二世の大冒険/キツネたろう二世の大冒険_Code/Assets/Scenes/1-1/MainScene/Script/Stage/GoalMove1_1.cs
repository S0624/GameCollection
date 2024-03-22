
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalMove1_1 : MonoBehaviour
{
    // 球面線形補間
    [Header("始点")]
    [SerializeField] private GameObject _StartPos;

    [Header("終点")]
    [SerializeField] private GameObject _EndPos;

    [Header("移動時間")]
    [SerializeField] private float _moveTime = 1;

    [Header("円運動の中心点")]
    [SerializeField] private GameObject _sphereCenter;

    // サウンドマネージャー.
    private SoundManager _soundManager;

    // ゴールのチュートリアル.
    private GoalExplainUpdate _goalExplain;

    // ゴールが最初にいる場所の座標.
    private Vector3 _start;
    // 最終的にたどり着く座標.
    private Vector3 _end;
    // ゴールの円運動の中心座標.
    private Vector3 _center;
    // 中心点だけずらした位置を戻す.
    private Vector3 _slerpPos;

    // ゴールを動かすときの真偽.
    public bool _eventFlag = false;

    // 補間位置の計算の値.
    float _interpolationPosition;
    // 現在の移動時間.
    private float _currentMoveTime;

    // 接地された時のパーティクル.
    [SerializeField] private ParticleSystem _particle;

    // パーティクル再生時間.
    private int _playParticleTime;

    // Seが鳴ったらtrueにする.
    private bool _isPlaySe;

    void Start()
    {
        _particle.Stop();
        _goalExplain = GameObject.Find("GoalExplain").GetComponent<GoalExplainUpdate>();
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void FixedUpdate()
    {
        if (_playParticleTime > 20)
        {
            _particle.Stop();
            return;
        }
            
            

        if(transform.position.x == 160)
        {
            _particle.Play();
            _playParticleTime++;

            if(!_isPlaySe)
            {
                _soundManager.PlaySE("GoalLanding");
                _isPlaySe = true;
            }
            _goalExplain._isAlphaChange = true;
        }


        if (!_eventFlag) return;

        _currentMoveTime += 0.01f;

        SlerpMove();
    }

    private void SlerpMove()
    {
        _start = _StartPos.transform.position;
        _end = _EndPos.transform.position;

        // 補間位置計算.
        _interpolationPosition = _currentMoveTime / _moveTime;

        // 円運動の中心点取得.
        _center = _sphereCenter.transform.position;

        // 円運動させる前に中心点が原点に来るように始点・終点を移動.
        _start -= _center;
        _end -= _center;

        // 原点中心で円運動.
        _slerpPos = Vector3.Slerp(_start, _end, _interpolationPosition);

        // 中心点だけずらした位置を戻す.
        _slerpPos += _center;

        // 補間位置を反映.
        transform.position = _slerpPos;
    }
}
