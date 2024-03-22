using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveScaffold : MonoBehaviour
{
    
    private Rigidbody _rigidBody;

    [SerializeField] private Vector3 _speed = new Vector3(1.0f, 0.0f, 1.0f);

    List<Rigidbody> _rigidBodies = new();

    // 折り返すときの最大フレーム数
    [SerializeField] private int _TurningMaxFrame = 0;

    // 移動しているフレーム数
    private int _DirectionChangeFrame = 0;

    // Start is called before the first frame update
    void Start()
    {
        _rigidBody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
    }


    private void FixedUpdate()
    {
        _DirectionChangeFrame++;
        MoveObject();
        AddVelocity();
        //Debug.Log(_DirectionChangeFrame);
    }

    private void OnCollisionEnter(Collision collision)
    {
        _rigidBodies.Add(collision.gameObject.GetComponent<Rigidbody>());
    }

    private void OnCollisionExit(Collision collision)
    {
        _rigidBodies.Remove(collision.gameObject.GetComponent<Rigidbody>());

    }

    // 地面の移動
    private void MoveObject()
    {
        _rigidBody.MovePosition(transform.position + Time.fixedDeltaTime * _speed);

        if(_DirectionChangeFrame >= _TurningMaxFrame)
        {
            _speed = new Vector3(_speed.x * -1, _speed.y * -1, _speed.z * -1);
            _DirectionChangeFrame = 0;
        }
    }

    // 上に載ったオブジェクトの移動
    private void AddVelocity()
    {
        if(_rigidBody.velocity.sqrMagnitude <=0.01f)
        {
            return;
        }

        //Debug.Log(_rigidBodies.Count);

        for (int i = 0; i < _rigidBodies.Count; i++)
        {
            _rigidBodies[i].AddForce(_rigidBody.velocity, ForceMode.VelocityChange);
        }
    }

}
