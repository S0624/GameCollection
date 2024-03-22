using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransition1_3_4 : MonoBehaviour
{
    private Gimick1_3_4Manager _manager;

    private Fade _fade;
    private FadeAnimDirector _fadeDirector;

    private Player3DMove _player;

    // クリアしたときにclearの画像を表示させる.
    [SerializeField] private GenerateImg _img;

    // 解いたかどうか.
    private bool _active = false;

    //フェードインするまでのカウント
    private int _fadeCount = 0;

    // Start is called before the first frame update
    void Start()
    {
        _manager = gameObject.GetComponent<Gimick1_3_4Manager>();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
        _fadeDirector = GameObject.Find("Manager").GetComponent<FadeAnimDirector>();
        _player = GameObject.Find("3DPlayer").GetComponent<Player3DMove>();
    }

    // Update is called once per frame
    void Update()
    {
        if (_manager.GetResult() || _player.GetHp() == 0)
        {
            //Debug.Log("a");
            // 画像の表示.
            if(_player.GetHp() != 0)
            {
                _img.GenerateCompleteImage();
            }
            _fadeCount++;
            if (_fadeCount > 50)
            {
                _fadeDirector._isFade = true;
                _fadeCount = 0;
            }
        }

        if (_fade.cutoutRange == 1.0f && _fadeDirector._isFade)
        {
            _active = _manager.GetResult();
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
        solveGimmickManager._solve[3] = _active;

        // 削除
        SceneManager.sceneLoaded -= GameSceneLoaded;
    }
}
