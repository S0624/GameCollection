using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransition1_3_1 : MonoBehaviour
{
    private SlideGimmickDirector _slideGimmickDirector;

    // フェード.
    private Fade _fade;
    // フェード管理.
    private FadeAnimDirector _fadeDirector;

    // 解いたかどうか.
    private bool _active = false;

    // Start is called before the first frame update
    void Start()
    {
        _slideGimmickDirector = GetComponent<SlideGimmickDirector>();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
        _fadeDirector = GameObject.Find("Manager").GetComponent<FadeAnimDirector>();
    }

    // Update is called once per frame
    void Update()
    {
        if (_slideGimmickDirector.GetResult())
        {
            //Debug.Log("a");
            _fadeDirector._isFade = true;
        }

        if (_fade.cutoutRange == 1.0f && _fadeDirector._isFade)
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
        solveGimmickManager._solve[0] = _active;

        // 削除
        SceneManager.sceneLoaded -= GameSceneLoaded;
    }
}
