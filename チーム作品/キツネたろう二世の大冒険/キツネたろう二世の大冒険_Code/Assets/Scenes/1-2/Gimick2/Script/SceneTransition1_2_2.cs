using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransition1_2_2 : MonoBehaviour
{
    // ギミックをクリアしたかどうかの情報を取得.
    private Switch_1_2_2 _switch;
    // フェード処理.
    private Fade _fade;
    // フェード管理.
    private FadeAnimDirector _fadeDirector;

    // プレイヤー.
    private Player3DMove _Player3D;

    // 解いたかどうか.
    private bool _active = false;

    void Start()
    {
        _switch = GameObject.Find("stage03_lever_02").GetComponent<Switch_1_2_2>();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
        _fadeDirector = GameObject.Find("Manager").GetComponent<FadeAnimDirector>();
        _Player3D = GameObject.FindWithTag("Player").GetComponent<Player3DMove>();
    }

    void Update()
    {
        if (_switch.GetResult())
        {
            _fadeDirector._isFade = true;
        }
        if (_fade.cutoutRange == 1.0f && _fadeDirector._isFade)
        {
            _active = true;
            SceneManager.sceneLoaded += GameSceneLoaded;
            SceneManager.LoadScene("MainScene1-2");
        }

        // シーン切り替え時に呼ぶ.
        void GameSceneLoaded(Scene next, LoadSceneMode mode)
        {
            // 切り替え後のスクリプト取得.
            SolveGimmickManager solveGimmickManager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
            Player2DMove player2D = GameObject.FindWithTag("Player").GetComponent<Player2DMove>();
            CameraUpdate camera = GameObject.Find("Camera").GetComponent<CameraUpdate>();

            // ギミックを解いたかのデータを渡す.
            solveGimmickManager._solve[1] = _active;
            player2D.transform.position = new Vector3(145.0f, 0.0f, 0.0f);
            player2D._hp = _Player3D._hp + 1;
            camera.transform.position = new Vector3(player2D.transform.position.x, player2D.transform.position.y,
                -20.0f);

            // 削除
            SceneManager.sceneLoaded -= GameSceneLoaded;
        }
    }
}
