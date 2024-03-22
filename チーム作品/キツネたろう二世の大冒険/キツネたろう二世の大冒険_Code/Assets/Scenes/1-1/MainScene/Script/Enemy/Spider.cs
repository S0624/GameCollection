using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spider : MonoBehaviour
{
    private RotateWindmill _windmill;

    // アニメーション.
    Animator _animator;
    BoxCollider col;

    // Start is called before the first frame update
    void Start()
    {
        _windmill = GameObject.Find("windmill:windmill:polySurface132").GetComponent<RotateWindmill>();
        // アニメーションの取得.
        _animator = GetComponent<Animator>();
        col = GetComponent<BoxCollider>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        // 落下したらオブジェクトを消す.
        if (transform.position.y < -20.0f || transform.position.z < -30.0f)
        {
            Destroy(gameObject);
        }

        if(_windmill.GetWindActive())
        {
            _animator.enabled = false;
        }
        else
        {
            //_animator.enabled = true;
        }
    }

    private void OnTriggerStay(Collider other)
    {
        Debug.Log("通ってる");

        // 風に当たるとアニメーションを終了.
        _animator.enabled = false;
    }

    private void OnTriggerExit(Collider other)
    {
        //_animator.enabled = true;
    }
}
