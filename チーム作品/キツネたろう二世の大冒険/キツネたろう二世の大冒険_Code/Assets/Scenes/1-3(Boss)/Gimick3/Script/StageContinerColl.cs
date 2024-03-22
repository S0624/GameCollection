using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageContinerColl : MonoBehaviour
{
    // オブジェクトの取得.
    [SerializeField] private GameObject _contena;
    [SerializeField] private GameObject _contenaGreen;
    private GameObject _contenaEffect;
    //[SerializeField] private ParticleSystem _contenaEffect;
    // Start is called before the first frame update
    private void Start()
    {
        _contenaEffect = Instantiate(_contenaGreen, transform.position, _contena.transform.rotation);

    }
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == _contena.name)
        {
            ContainerDirector._getName = collision.gameObject.name;
            ContainerDirector._isColl = true;
            EffectPlay();
        }
    }
    private void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.name == _contena.name)
        {
            ContainerDirector._getName = collision.gameObject.name;
            ContainerDirector._isColl = true;
            //EffectPlay();
        }
    }
    // 範囲外に出た処理.
    private void OnCollisionExit(Collision collision)
    {
        ContainerDirector._getName = _contena.name;
        ContainerDirector._isColl = false;
        EffectStop();
    }
    // エフェクト再生
    private void EffectPlay()
    {
        foreach (ParticleSystem _effect in _contenaEffect.GetComponentsInChildren<ParticleSystem>())
        {
            _effect.Play();
        }
    }
    // エフェクトストップ.
    private void EffectStop()
    {
        foreach (ParticleSystem _effect in _contenaEffect.GetComponentsInChildren<ParticleSystem>())
        {
            _effect.Stop();
        }
    }
}
