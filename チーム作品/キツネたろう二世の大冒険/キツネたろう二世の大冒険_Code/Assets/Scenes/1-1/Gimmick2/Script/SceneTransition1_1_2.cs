/*1-1-2から表世界へのシーン遷移*/

using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransition1_1_2 : MonoBehaviour
{
    // ギミックをクリアしたかの取得.
    private Gimick1_1_2_Manager _Gimmick1_1_2;
    // フェード.
    private Fade _fade;
    // フェード管理.
    private FadeAnimDirector _fadeDirector;
    private Player3DMove _Player3D;

    // 解いたかどうか.
    private bool _active = false;

    // Start is called before the first frame update
    void Start()
    {
        _Gimmick1_1_2 = GetComponent<Gimick1_1_2_Manager>();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
        _fadeDirector = GameObject.Find("Manager").GetComponent<FadeAnimDirector>();
        _Player3D = GameObject.FindWithTag("Player").GetComponent<Player3DMove>();

    }

    // Update is called once per frame
    void Update()
    {
        if (_Gimmick1_1_2.GetResult())
        {
            _fadeDirector._isFade = true;
        }

        if (_fade.cutoutRange == 1.0f && _fadeDirector._isFade)
        {
            _active = _Gimmick1_1_2.GetResult();
            SceneManager.sceneLoaded += GameSceneLoaded;
            SceneManager.LoadScene("MainScene1-1");
        }
    }

    // シーン切り替え時に呼ぶ.
    private void GameSceneLoaded(Scene next, LoadSceneMode mode)
    {
        // 切り替え後のスクリプト取得.
        SolveGimmickManager solveGimmickManager = 
            GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        Player2DMove player2D = GameObject.FindWithTag("Player").GetComponent<Player2DMove>();
        CameraUpdate camera = GameObject.Find("Camera").GetComponent<CameraUpdate>();

        // ギミックを解いたかのデータを渡す.
        //gimmickManager1_1._operationGimmick[1] = _active;
        solveGimmickManager._solve[1] = _active;
        player2D.transform.position = new Vector3(94.0f, 0.0f, 0.0f);
        player2D._hp = _Player3D._hp + 1;
        camera.transform.position = new Vector3(player2D.transform.position.x, player2D.transform.position.y,
            -20.0f);

        // 削除
        SceneManager.sceneLoaded -= GameSceneLoaded;
    }
}
