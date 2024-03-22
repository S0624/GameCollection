using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stage1_Blue_Container : MonoBehaviour
{
    [SerializeField] private ParticleSystem _particleRed;
    [SerializeField] private ParticleSystem _particleGreen;
    [SerializeField] private ParticleSystem _particlePurple;
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "stage1_kontena_blue")
        {
            ContainerDirector._getName = collision.gameObject.name;
            ContainerDirector._isColl = true;
            EffectPlay();
        }
    }
    private void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.name == "stage1_kontena_blue")
        {
            ContainerDirector._getName = collision.gameObject.name;
            ContainerDirector._isColl = false;
        }
    }
    private void EffectPlay()
    {
        _particleRed.Play();
        _particleGreen.Play();
        _particlePurple.Play();
    }
}
