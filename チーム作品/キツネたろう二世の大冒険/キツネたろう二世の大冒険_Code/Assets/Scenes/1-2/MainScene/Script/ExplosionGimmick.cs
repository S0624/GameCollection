// 爆発ギミックの処理

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplosionGimmick : MonoBehaviour
{
    private SolveGimmickManager _manager;

    [Header("着火のパーティクルオブジェクト")]
    [SerializeField] ParticleSystem _ignitionParticle;
    [Header("火花のパーティクルオブジェクト")]
    [SerializeField] ParticleSystem _sparkParticle;
    [Header("爆風のパーティクルオブジェクト")]
    [SerializeField] ParticleSystem _blastParticle;

    [Header("銅線オブジェクト")]
    [SerializeField] GameObject _CopperWireObject;

    [Header("爆発オブジェクト")]
    [SerializeField] GameObject _bombObject;

    [Header("爆発する力")]
    [SerializeField] private float _force;

    [Header("爆発範囲の半径")]
    [SerializeField] private float _radius;

    [Header("上に飛ばされる力")]
    [SerializeField] private float _upwardsPower;

    [Header("パーティクルの最大再生時間")]
    [SerializeField] private float _particleMaxCount;

    [Header("爆発するまでの時間")]
    [SerializeField] private int _blastTime;

    // サウンドマネージャー.
    private SoundManager _soundManager;

    // パーティクル再生時間
    private float _particleCount;

    // 爆発する座標
    Vector3 _ExplosionPosition;

    // 作動時間.
    private int _operatingTime = 0;
    // 作動終了時間
    private int _operatingFinish = 240;

    // ボムの存在の有無
    private bool _isBombExist = true;

    Vector3 velocity = Vector3.zero;


    private void Start()
    {
        _manager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        //_particleSystem.Stop();
        _ignitionParticle.Stop();
        _sparkParticle.Stop();
        _blastParticle.Stop();
    }

    private void FixedUpdate()
    {
        if (_manager._solve[2])
        {
            IgnitionUpdate();

            

            _operatingTime++;
            //_sparkParticle.Play();
            _blastParticle.Play();
            if(_operatingTime == 1)
            {
                _ignitionParticle.Play();
            }
        }

        if(_operatingTime > _blastTime)
        {
            UpdateExplosion();
            
        }

        if(_operatingTime > 70)
        {
            _sparkParticle.Play();
            _CopperWireObject.transform.position += new Vector3(0.0f, -0.01f, 0.0f);
            _sparkParticle.transform.position += new Vector3(0.0f, -0.01f, 0.0f);
        }

        if(_operatingTime >= _operatingFinish)
        {
            _manager._solve[2] = false;
            _operatingTime = 0;
        }
    }

    /// <summary>
    /// 着火パーティクルの処理
    /// </summary>
    private void IgnitionUpdate()
    {
        _ignitionParticle.transform.position = Vector3.SmoothDamp(_ignitionParticle.transform.position, _sparkParticle.transform.position, ref velocity, 0.5f);
    }


    /// <summary>
    /// 爆発処理
    /// </summary>
    public void UpdateExplosion()
    {
        // パーティクル再生.
        //_sparkParticle.Play();
        if(_isBombExist)
        {
            Instantiate(_blastParticle, _bombObject.transform.position, Quaternion.identity);
            _soundManager.PlaySE("1_2_0_Bomb");
        }

        // ボム座標を代入.
        _ExplosionPosition = _bombObject.transform.position;

        // 範囲内のRigidbodyにAddExplosionForce.
        // 後でコメント変更.
        Collider[] hitColliders = Physics.OverlapSphere(_ExplosionPosition, _radius);
        for(int i = 0; i < hitColliders.Length; i++)
        {
            Rigidbody rigidbody = hitColliders[i].GetComponent<Rigidbody>();

            // 範囲内にいるRigidbodyを持つオブジェクトを吹き飛ばす.
            if(rigidbody)
            {
                rigidbody.AddExplosionForce(_force, _ExplosionPosition, _radius, _upwardsPower, ForceMode.Impulse);
                rigidbody.constraints = RigidbodyConstraints.None;
                rigidbody.useGravity = true;
                rigidbody.tag = "Untagged";
            }
        }

        // 再生している時間.
        //if(_particleCount < _particleMaxCount)
        //{
        //    _particleCount++;
        //}
        //// 時間がたつとパーティクル再生終了.
        //if(_particleCount == _particleMaxCount )
        //{
        //    // パーティクル再生終了.
        //    _sparkParticle.Stop();
        //}

        _isBombExist = false;


        _bombObject.SetActive(_isBombExist);
        //Destroy(gameObject);
    }
}
