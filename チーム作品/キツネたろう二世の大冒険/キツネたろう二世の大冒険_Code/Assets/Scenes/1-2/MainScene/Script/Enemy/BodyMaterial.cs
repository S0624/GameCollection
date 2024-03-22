using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BodyMaterial : MonoBehaviour
{
    private Material _material;

    private float _a;

    // Start is called before the first frame update
    void Start()
    {
        _material = GetComponent<Material>();
        _a = _material.color.a;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        
    }
}
