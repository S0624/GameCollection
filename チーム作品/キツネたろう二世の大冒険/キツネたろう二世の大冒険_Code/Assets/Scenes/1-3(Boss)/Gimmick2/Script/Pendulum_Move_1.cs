using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pendulum_Move_1 : MonoBehaviour
{
    //回転の軸を取得.
    GameObject _Cube;
    //X座標の回転速度.
    private float _rotateX = 0;
    //Y座標の回転速度.
    private float _rotateY = 0;
    //Z座標の回転速度.
    private float _rotateZ = 30;
    Quaternion _rotation;
        
    bool _isMoving;

    private void Start()
    {
        //回転の軸を名前指定で取得する.
         _Cube = GameObject.Find("CubeRotate1");
        _rotation = _Cube.transform.rotation;
        _isMoving = false;
    }

    void FixedUpdate()
    {
        //カウントに対して処理を変える.
        if (!_isMoving)
        {
            // X,Y,Z軸に対してそれぞれ、指定した角度ずつ回転させている。
            // deltaTimeをかけることで、フレームごとではなく、1秒ごとに回転するようにしている。
            _Cube.transform.Rotate(new Vector3(_rotateX, _rotateY, _rotateZ) * -Mathf.Deg2Rad * 2);
        }
        else
        {
            // X,Y,Z軸に対してそれぞれ、指定した角度ずつ回転させている。
            // deltaTimeをかけることで、フレームごとではなく、1秒ごとに回転するようにしている。
            _Cube.transform.Rotate(new Vector3(_rotateX, _rotateY, _rotateZ) * Mathf.Deg2Rad * 2);
        }
        if (_rotation.z <= -0.5)
        {
            _isMoving = true;
        }
        if (_rotation.z >= 0.5)
        {
            _isMoving = false;
        }
        //角度の更新
        _rotation = _Cube.transform.rotation;
    }
}
