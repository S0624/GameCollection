using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallingGimmick : MonoBehaviour
{
    // 落ちるスピード.
    [SerializeField] private Vector3 _FallingSpeed = new Vector3(0.0f,-1.0f,0.0f);
    // 落ちているかどうか
    private bool _isFalling = false;

    private Vector3 _initialPosition;

    // 床の上昇する上限の座標.
    private float _upperPosition = 0;


    // Start is called before the first frame update
    void Start()
    {
        _initialPosition = transform.position;
        _upperPosition = transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        if(_isFalling)
        {
            transform.position += _FallingSpeed;
        }
        else if(!_isFalling && transform.position.y < _upperPosition)
        {
            transform.position -= _FallingSpeed * 3;
        }

        if(transform.position.y <= -6.0f)
        {
            PositionReset();
            _isFalling = false;
        }
    }

    private void OnCollisionStay(Collision collision)
    {
        if(collision.gameObject.tag == "Player")
        {
            _isFalling = true;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            _isFalling = false;
        }
    }

    // 一番下まで落ち切った時に初期位置にリセット.
    private void PositionReset()
    {
        transform.position = _initialPosition;
    }
}
