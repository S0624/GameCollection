using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GateCol : MonoBehaviour
{
    private bool[] _GimmickRoad = new bool[4];

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "")
        {

        }
    }

    private void OnTriggerExit(Collider other)
    {
        
    }
}
