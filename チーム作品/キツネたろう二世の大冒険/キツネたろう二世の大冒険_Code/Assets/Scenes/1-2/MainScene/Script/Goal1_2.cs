using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal1_2 : MonoBehaviour
{
    // イベント発生.
    private bool _isEvent = false;
    private SoundManager _soundManager;
    private bool _isPlaySe = false;

    // Start is called before the first frame update
    void Start()
    {
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        if(_isEvent)
        {
            transform.position += new Vector3(-0.5f, 0.5f, 0.0f);
            transform.Rotate(0.0f, 0.0f, 50.0f);

            if(!_isPlaySe)
            {
                _soundManager.PlaySE("GoalAttack");
                _isPlaySe = true;
            }

        }
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "BossEat")
        {
            _isEvent = true;
        }
    }
}
