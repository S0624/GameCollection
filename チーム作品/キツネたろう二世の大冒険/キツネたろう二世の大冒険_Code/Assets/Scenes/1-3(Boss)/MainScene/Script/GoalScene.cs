using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalScene : MonoBehaviour
{
    private SolveGimmickManager _manager;
    private GateFlag _flag;
    private FadeAnimDirector _fadeDirector;
    private Player3DMove _player;

    // 次のシーンへ行くタイミング.
    private int _nextSceneTime;

    // Start is called before the first frame update
    void Start()
    {
        _manager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        _flag = GameObject.Find("3DPlayer").GetComponent<GateFlag>();
        _fadeDirector = GameObject.Find("Manager").GetComponent<FadeAnimDirector>();
        _player = GameObject.FindWithTag("Player").GetComponent<Player3DMove>();
        _nextSceneTime = 0;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        // 全てのギミックをクリアしたら. 
        if(_manager.GetAllClear())
        {
            _nextSceneTime++;
            _fadeDirector._isFade = true;
            //_flag._isGoal1_3 = true;
            _player._isController = false;

            if(_nextSceneTime > 120)
            {
                _flag._isGoal1_3 = true;
            }
        }
    }
}
