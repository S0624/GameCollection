using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TipsButtonColl : MonoBehaviour
{
    public bool _isHit { get; set; }
    private void OnTriggerStay(Collider coll)
    {
        // プレイヤーに触れたら
        if (coll.gameObject.tag == "Player")
        {
            _isHit = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        // プレイヤーに触れたら
        if (other.gameObject.tag == "Player")
        {
            _isHit = false;
        }
    }

}
