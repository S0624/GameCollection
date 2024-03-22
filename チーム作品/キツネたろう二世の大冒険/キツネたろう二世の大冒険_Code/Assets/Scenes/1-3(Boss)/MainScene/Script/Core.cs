using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Core : MonoBehaviour
{
    // コア.
    public GameObject[] _cora;
    // コアの膜.
    public GameObject[] _coraFilm;
    // ギミックマネージャー.
    private SolveGimmickManager _gimmickManager;

    void Start()
    {
        _gimmickManager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
    }

    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        // ギミックを解いたら膜を消し、コアを少し下げる
        //if(_gimmickManager._solve[0])
        //{
        //    Destroy(_coraFilm[0]);
        //}
        //if (_gimmickManager._solve[1])
        //{
        //    Destroy(_coraFilm[1]);
        //}
        //if (_gimmickManager._solve[2])
        //{
        //    Destroy(_coraFilm[2]);
        //}
        //if (_gimmickManager._solve[3])
        //{
        //    Destroy(_coraFilm[3]);
        //}

        for (int coraNum = 0; coraNum < _cora.Length; coraNum++)
        {
            CoraGoDown(coraNum);
        }
    }

    // クリアした時のコアの挙動
    private void CoraGoDown(int coraNum)
    {
        if (!_gimmickManager._solve[coraNum] ) return;

        //Destroy(_coraFilm[coraNum]);

        _coraFilm[coraNum].gameObject.SetActive(false);


        if (_cora[coraNum].transform.position.y > 0)
        {
            _cora[coraNum].transform.position += new Vector3(0.0f, -0.05f, 0.0f);
        }
        
    }
}
