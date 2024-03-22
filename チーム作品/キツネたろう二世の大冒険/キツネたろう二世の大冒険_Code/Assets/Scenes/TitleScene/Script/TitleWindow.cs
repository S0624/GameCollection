using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleWindow : MonoBehaviour
{
    // 回転速度.
    private float _rotateSpeed = 0.5f;

    private void Start()
    {
        _rotateSpeed = 0.5f;
    }

    public void WindowUpdate()
    {
        transform.Rotate(_rotateSpeed, 0.0f, 0.0f);
    }
}
