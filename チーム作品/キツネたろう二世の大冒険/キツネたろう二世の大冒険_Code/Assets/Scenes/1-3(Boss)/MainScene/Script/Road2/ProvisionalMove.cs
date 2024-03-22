using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class ProvisionalMove : MonoBehaviour
{
    private Rigidbody _rb;

    private float _speed = 50f;
    public float _jump = 500f;
    private Vector3 _moveDirection;

    void Start()
    {
        _rb = GetComponent<Rigidbody>();

        _moveDirection = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {
        // 垂直方向.
        float vertical = Input.GetAxis("Vertical") * _speed;
        // 水平方向.
        float horizontal = Input.GetAxis("Horizontal") * _speed;

        _moveDirection = new Vector3(horizontal, 0.0f, vertical);

        if (_rb.velocity.magnitude <= 5)
        {
            _rb.AddForce(_moveDirection);
        }

        if (Input.GetKeyDown("joystick button 0"))
        {
            Debug.Log("jump");
            _rb.AddForce(Vector3.up * _jump);
        }
    }
}
