using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimmick1_2_4_Light : MonoBehaviour
{
    // ライトのオブジェクトを取得.
    [SerializeField] GameObject[] _lightData;
    Light[] _light = new Light[2];
    void Start()
    {
        for (int i = 0; i < 1; i++)
        {
            _light[i] = _lightData[i].GetComponent<Light>();
            _light[i].range = 0;
        }
    }

    void Update()
    {
        for (int i = 0; i < 1; i++)
        {
            _light[i].range += 0.1f;
        }
    }
}
