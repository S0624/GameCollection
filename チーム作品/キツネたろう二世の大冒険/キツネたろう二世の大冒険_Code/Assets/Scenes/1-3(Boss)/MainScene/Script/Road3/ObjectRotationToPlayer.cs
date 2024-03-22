using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectRotationToPlayer : MonoBehaviour
{
    // プレイヤーオブジェクト.
    public GameObject _player;
    // 子オブジェクトにするかどうか.
    public bool _isHitPrent;

    private void OnCollisionStay(Collision collision)
    {
        // プレイヤーだったら.
        if (collision.gameObject.tag == "Player")
        {
            // 子オブジェクトにするなら.
            if(_isHitPrent)
            {
                _player.transform.SetParent(gameObject.transform);
            }
            else
            {
                _player.transform.parent = null;
            }
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        // プレイヤーだったら.
        if (collision.gameObject.tag == "Player")
        {
            _player.transform.parent = null;
        }
    }
}
