/*クリアした時の狐のアニメーション*/
// HACK.マジックナンバー消せよ.

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClearFox : MonoBehaviour
{
    // クリアシーンマネージャー.
    private ClearSceneManager _manager;

    // プレイヤーアニメーション.
    private PlayerAnim _anim;

    // 狐の初期位置.
    [Header("始点")]
    public GameObject _startPos;
    // 狐の着地する位置.
    [Header("終点")]
    public GameObject _endPos;
    [Header("移動時間")]
    [SerializeField] private float _moveTime = 1;
    [Header("始点と終点の中心")]
    [SerializeField] private GameObject _sphereCenter;

    // 狐が最初にいる場所の座標.
    private Vector3 _start;
    // 最終的にたどり着く座標.
    private Vector3 _end;
    // 狐の円運動の中心座標.
    private Vector3 _center;
    // 中心点だけずらした位置を戻す.
    private Vector3 _slerpPos;

    // 補間位置の計算の値.
    private float _interpolationPosition;

    // 現在の移動時間.
    private float _currentMoveTime;

    void Start()
    {
        _anim = GetComponent<PlayerAnim>();
        _manager = GameObject.Find("GameManager").GetComponent<ClearSceneManager>();
    }

    private void FixedUpdate()
    {

        if(_manager._currentTime < 200)
        {
            
            transform.position = _startPos.transform.position;
        }
        else if(_manager._currentTime > 200 && _manager._currentTime < 250)
        {
            _anim._jump = true;
            SlerpMove();
        }
        else if(_manager._currentTime > 250 && _manager._currentTime < 380)
        {
            _anim._jump = false;
            _anim._waveHands = true;
            WaveHand();
        }
        else if(_manager._currentTime > 380)
        {

            _anim._waveHands = false;
            _anim._run = true;

            Chase();
        }

    }

    private void SlerpMove()
    {
        _currentMoveTime += 0.01f;

        _start = _startPos.transform.position; ;
        _end = _endPos.transform.position;

        // 補間位置計算.
        _interpolationPosition = _currentMoveTime / _moveTime;

        // 円運動の中心点取得.
        _center = _sphereCenter.transform.position;
        // 円運動させる前に中心点が元徳に来るように始点・終点を移動.
        _start -= _center;
        _end -= _center;

        // 原点中心で円運動.
        _slerpPos = Vector3.Slerp( _start, _end, _interpolationPosition );

        // 中心点だけずらした位置を戻す.
        _slerpPos += _center;

        // 補間位置を反映.
        transform.position = _slerpPos;
    }

    // 手を振る処理.
    private void WaveHand()
    {
        // 正面に回転させる.
        Quaternion rotation = Quaternion.LookRotation(new Vector3(0.0f, 0.0f, -180.0f), Vector3.up);

        transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * 5);
    }

    // 追いかける処理.
    private void Chase()
    {
        // 進行方向に回転させる.
        Quaternion rotation = Quaternion.LookRotation(new Vector3(-1.0f, 0.0f, -1.0f), Vector3.up);

        transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * 20);

        transform.position += new Vector3(-0.5f, 0.0f, 0.0f);
    }
}
