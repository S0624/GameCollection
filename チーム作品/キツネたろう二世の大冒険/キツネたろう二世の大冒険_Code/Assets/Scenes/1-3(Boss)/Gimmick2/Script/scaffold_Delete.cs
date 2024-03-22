using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class scaffold_Delete : MonoBehaviour
{

    //足場がプレイヤーに接触したとき.
    private void OnCollisionEnter(Collision collision)
    {
        //足場を削除する.
        Destroy(this.gameObject);
    }
}
