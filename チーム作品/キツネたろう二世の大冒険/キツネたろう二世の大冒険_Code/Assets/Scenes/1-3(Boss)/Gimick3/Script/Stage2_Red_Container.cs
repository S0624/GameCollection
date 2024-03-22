using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stage2_Red_Container : MonoBehaviour
{
    [SerializeField] private ParticleSystem _particleRed;
    [SerializeField] private ParticleSystem _particleGreen;
    [SerializeField] private ParticleSystem _particlePurple;
    void OnTriggerEnter(Collider collision)
    {
        if (collision.gameObject.name == "stage2_kontena_red")
        {
            ContainerDirector._getName = collision.gameObject.name;
            ContainerDirector._isColl = true;
            EffectPlay();
        }
    }
    private void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.name == "stage2_kontena_red")
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
