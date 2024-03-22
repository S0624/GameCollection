// ベルトコンベアギミック
// MEMO:ベルトコンベアのSEを流すときに_sound.PlaySE("1_2_0_BeltConbeyor")を入れる

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BeltConveyorGimmick : MonoBehaviour
{
    private SolveGimmickManager _manager;

    private SoundManager _sound;

    // アニメーション.
    private Animator _animator;
    // アニメーション再生速度
    private float _animSpeed = 0;
    [Header("アニメーションの再生速度の加速")]
    public float _animSpeedAddForce = 0;
    // アニメーション最大再生速度
    private float _animMaxSpeed = 1;

    // マテリアルの取得.
    public Material _material;
    // テクスチャのスピード
    public Vector2 _textureSpeed = Vector2.zero;
    // テクスチャのx方向のスピード
    private float _textureSpeedX = 0;
    // テクスチャのx方向の加速
    public float _textureSpeedXAddForce = 0;

    // ベルトコンベアが物体を動かす向き.
    [SerializeField] private Vector3 _moveDirection = Vector3.forward;
    // ベルトコンベアの速度.
    [SerializeField] private float _ConveyorSpeed;
    // コンベアに載っている物体の加速度.
    [SerializeField] private float _forcePower;


    private List<Rigidbody> _rigidbodies = new List<Rigidbody>();

    // 作動時間.
    private int _operatingTime = 0;

    void Start()
    {
        _manager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();

        // 方向を正規化する.
        _moveDirection = _moveDirection.normalized;

        _animator = GetComponent<Animator>();
    }

    private void FixedUpdate()
    {
        _material.SetTextureScale("_MainTex", _textureSpeed);
        _animator.SetFloat("AnimSpeed", _animSpeed);

        _textureSpeed = new Vector2(_textureSpeedX, 0.0f);

        //Debug.Log(_textureSpeed.x);

        if (_manager._solve[1])
        {
            UpdateBeltConveyor();
            _operatingTime++;
            _animSpeed += _animSpeedAddForce;
            //_textureSpeed = new Vector2(5.0f, 0.0f);
            if(_operatingTime == 1)
            {
                _sound.PlaySE("1_2_0_BeltConbeyor");
            }
            _textureSpeedX += _textureSpeedXAddForce;

            if (_animSpeed >= _animMaxSpeed)
            {
                _animSpeed = _animMaxSpeed;
            }
            if(_textureSpeedX >= 5)
            {
                _textureSpeedX = 5;
            }
        }
        else
        {
            //_textureSpeed = new Vector2(0.0f, 0.0f);
            _textureSpeedX -= _textureSpeedXAddForce;
            _animSpeed -= _animSpeedAddForce;
            if(_animSpeed <= 0)
            {
                _animSpeed = 0;
            }

            if(_textureSpeedX <= 0)
            {
                _textureSpeedX = 0;
            }
        }

        if(_operatingTime >= 180)
        {
            _manager._solve[1] = false;
            _sound.StopSe();
            _operatingTime = 0;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        var rigidBody = collision.gameObject.GetComponent<Rigidbody>();
        _rigidbodies.Add(rigidBody);
    }

    private void OnCollisionExit(Collision collision)
    {
        var rigidBody = collision.gameObject.GetComponent<Rigidbody>();
        _rigidbodies.Remove(rigidBody);
    }

    /// <summary>
    /// ベルトコンベアの更新処理.
    /// </summary>
    public void UpdateBeltConveyor()
    {
        // 消滅したオブジェクトは除去する.
        _rigidbodies.RemoveAll(r => r == null);

        foreach (var r in _rigidbodies)
        {
            // 物体の移動速度のベルトコンベア方向の成分だけを取り出す.
            var objectSpeed = Vector3.Dot(r.velocity, _moveDirection);

            // 目標値以下なら加速する.
            if (objectSpeed < Mathf.Abs(_ConveyorSpeed))
            {
                r.AddForce(_moveDirection * _forcePower, ForceMode.Acceleration);
            }
        }
    }
}
