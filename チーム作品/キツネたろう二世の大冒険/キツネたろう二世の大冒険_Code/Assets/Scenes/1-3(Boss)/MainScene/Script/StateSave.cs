using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StateSave : MonoBehaviour
{
    // インスタンスが存在するか.
    static bool _inctanceExit = false;
    // コア.
    public GameObject[] _cora;

    private void Awake()
    {
        if(_inctanceExit)
        {
            Destroy(gameObject);
            for(int coraNum = 0; coraNum < _cora.Length; coraNum++)
            {
                Destroy(_cora[coraNum]);
            }

            return;
        }

        _inctanceExit = true;

        DontDestroyOnLoad(gameObject);
        for (int coraNum = 0; coraNum < _cora.Length; coraNum++)
        {
            DontDestroyOnLoad(_cora[coraNum]);
        }
    }
}
