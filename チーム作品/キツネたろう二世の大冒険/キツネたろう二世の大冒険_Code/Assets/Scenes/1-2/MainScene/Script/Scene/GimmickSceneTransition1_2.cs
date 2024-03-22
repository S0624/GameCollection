using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GimmickSceneTransition1_2 : MonoBehaviour
{
    // インスタンス.
    public static GimmickSceneTransition1_2 _instance;
    // シーン遷移を行ったかどうか.
    public bool _isScene;
    // シーン遷移の真偽.
    public bool _isGateGimmick1;
    public bool _isGateGimmick2;
    public bool _isGateGimmick3;
    public bool _isGateGimmick4;

    private void Awake()
    {
        // シングルトン.
        if (_instance == null)
        {
            // 自身をインスタンスとする.
            _instance = this;
        }
        else
        {
            // インスタンスが複数存在しないように、既に存在していたら自身を消去する.
            Destroy(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        // 初期化.
        _isScene = false;
        _isGateGimmick1 = false;
        _isGateGimmick2 = false;
        _isGateGimmick3 = false;
        _isGateGimmick4 = false;
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void OnTriggerEnter(Collider other)
    {
        // 扉の当たり判定に入ったらture.
        if (other.tag == "Gimmick1")
        {
            _isGateGimmick1 = true;
        }
        else if (other.tag == "Gimmick2")
        {
            _isGateGimmick2 = true;
        }
        else if(other.tag == "Gimmick3")
        {
            _isGateGimmick3 = true;
        }
        else if( other.tag == "Gimmick4")
        {
            _isGateGimmick4 = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        // 扉の当たり判定を出たらfalse.
        if (other.tag == "Gimmick1")
        {
            _isGateGimmick1 = false;
        }
        else if (other.tag == "Gimmick2")
        {
            _isGateGimmick2 = false;
        }
        else if (other.tag == "Gimmick3")
        {
            _isGateGimmick3 = false;
        }
        else if (other.tag == "Gimmick4")
        {
            _isGateGimmick4 = false;
        }
    }

    public bool GetGateGimmick1()
    {
        return _isGateGimmick1;
    }

    public bool GetGateGimmick2()
    {
        return _isGateGimmick2;
    }

    public bool GetGateGimmick3()
    {
        return _isGateGimmick3;
    }

    public bool GetGateGimmick4()
    {
        return _isGateGimmick4;
    }
}
