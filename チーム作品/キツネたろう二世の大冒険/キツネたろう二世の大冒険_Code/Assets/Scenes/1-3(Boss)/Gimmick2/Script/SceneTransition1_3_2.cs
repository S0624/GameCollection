using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransition1_3_2 : MonoBehaviour
{
    private Stage_Clear_Switch _slideGimmickDirector;
    // フェード処理.
    private Fade _fade;
    // フェード管理.
    private FadeAnimDirector _fadeAnimDirector;
    // プレイヤー.
    private Player3DMove _player;

    // 解いたかどうか.
    private bool _active = false;

    // Start is called before the first frame update
    void Start()
    {
        _slideGimmickDirector = GetComponent<Stage_Clear_Switch>();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
        _fadeAnimDirector = GameObject.Find("Manager").GetComponent <FadeAnimDirector>();
        _player = GameObject.Find("3DPlayer").GetComponent<Player3DMove>();
    }

    // Update is called once per frame
    void Update()
    {
        if (_slideGimmickDirector.GetResult() || _player.GetHp() == 0)
        {
            //Debug.Log("a");
            _fadeAnimDirector._isFade = true;
        }

        if (_fade.cutoutRange == 1.0f && _fadeAnimDirector._isFade)
        {
            _active = _slideGimmickDirector.GetResult();
            SceneManager.sceneLoaded += GameSceneLoaded;
            SceneManager.LoadScene("MainScene1-3");
        }
    }

    // シーン切り替え時に呼ぶ.
    private void GameSceneLoaded(Scene next, LoadSceneMode mode)
    {
        // 切り替え後のスクリプト取得.
        SolveGimmickManager solveGimmickManager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();

        // ギミックを解いたかのデータを渡す.
        solveGimmickManager._solve[1] = _active;

        // 削除
        SceneManager.sceneLoaded -= GameSceneLoaded;
    }
}
