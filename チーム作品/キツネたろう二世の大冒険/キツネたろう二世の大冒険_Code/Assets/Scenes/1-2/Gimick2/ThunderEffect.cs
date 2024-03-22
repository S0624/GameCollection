using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThunderEffect : MonoBehaviour
{
    Material _mat;
    Material _tMat;
    public float _duration = 1.0f;
    public float intensity = 2.5f;

    private float _n = 0.0f;//何かわかんない
    private float _xTemp = 0.0f;
    private float _sumTime = 0.0f;

    public float duration2 = 1.0f;
    public float length = 1.0f;

    ParticleSystem _particleSystem;
    ParticleSystemRenderer _particleRenderer;
    // Start is called before the first frame update
    void Start()
    {
        _particleSystem = GetComponent<ParticleSystem>();
        _particleRenderer = GetComponent<ParticleSystemRenderer>();
        _mat = _particleRenderer.material;
        _tMat = _particleRenderer.trailMaterial;
    }

    // Update is called once per frame
    void Update()
    {
        float phi = Time.time / _duration * 2 * Mathf.PI;
        float amplitude = Mathf.Cos(phi) * 0.5f + 0.5f;
        _mat.EnableKeyword("_EMISSION");
        float factor = Mathf.Pow(2, intensity);
        _sumTime += Time.deltaTime;
        _n = _xTemp + Mathf.PingPong(_sumTime * length / duration2 * 2, length);//1秒間に0からlengthまで1往復する時間 

        _mat.SetColor("_EmissionColor", _particleRenderer.material.color * factor * _n);
        _particleSystem.startColor = _particleRenderer.material.color * factor * _n;

        _tMat.SetColor("_EmissionColor", _particleRenderer.material.color * factor * _n);



    }
}
