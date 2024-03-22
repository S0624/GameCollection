using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveBackGround : MonoBehaviour
{
    public GameObject Bg;

    private GameObject _instance1;
    private GameObject _instance2;

    private Vector3 _pos;
    private Vector3 _move;

    void Start()
    {
        _instance1 = Instantiate(Bg);
        _instance2 = Instantiate(Bg);

        _pos = Bg.transform.position;
        _pos.x = 184f;

        _instance2.transform.position = _pos;

        _move = new Vector3(0.04f, 0, 0);
    }

    public void BgMove()
    {
        _instance1.transform.position -= _move;
        _instance2.transform.position -= _move;

        if (_instance1.transform.position.x < -184.0f)
        {
            _instance1.transform.position = _pos;
        }
        if (_instance2.transform.position.x < -184.0f)
        {
            _instance2.transform.position = _pos;
        }
    }
}
