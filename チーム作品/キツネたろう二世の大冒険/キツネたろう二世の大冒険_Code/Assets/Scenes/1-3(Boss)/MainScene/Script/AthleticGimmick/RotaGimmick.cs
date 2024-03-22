using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotaGimmick : MonoBehaviour
{
    // プレイヤー.
    private GameObject _player;
    // プレイヤーに入れる移動ベクトル.
    private Vector3 _vec;
    // プレイヤーが当たっているか.
    private bool _isHit;

    // 回転スピード.
    [SerializeField] private Vector3 _rotateSpeed = Vector3.zero;

    void Start()
    {
        _player = GameObject.Find("3DPlayer");

        // 回転スピードz軸の0.0.5倍分をx軸にいれ、移動ベクトルとする.
        _vec = transform.right * _rotateSpeed.z * -0.05f;

        _isHit = false;
    }

    private void FixedUpdate()
    {
        transform.Rotate(_rotateSpeed);

        // プレイヤーが当たっている時、移動ベクトル分動かす.
        if (_isHit)
        {
            _player.transform.position += _vec;
            // 動かしたら一度当たっていない状態に戻す.
            _isHit = false;
        }
    }

    private void OnCollisionStay(Collision collision)
    {
        // 触れている間はあたっていることにする.
        _isHit = true;
    }
}
