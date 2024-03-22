using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Fade1_2 : MonoBehaviour
{
    // 色.
    private Color _color;
    // ゲートのボタンを押したかどうか.
    private bool _isPush;

    // Start is called before the first frame update
    void Start()
    {
        // 初期化.
        _isPush = false;
        _color = gameObject.GetComponent<Image>().color;
        _color.r = 0.0f;
        _color.g = 0.0f;
        _color.b = 0.0f;
        _color.a = 1.0f;
        gameObject.GetComponent<Image>().color = _color;
    }

    // Update is called once per frame
    void Update()
    {
        // フェード処理.
        FadeUpdate();
        // シーン遷移関数.
        SceneTransition();
    }

    // ゲートの前にいるかの状態.
    private bool SetGateFlag()
    {
        return GimmickSceneTransition1_2._instance.GetGateGimmick1() || 
            GimmickSceneTransition1_2._instance.GetGateGimmick2() ||
            GimmickSceneTransition1_2._instance.GetGateGimmick3() ||
            GimmickSceneTransition1_2._instance.GetGateGimmick4();
    }

    // フェード処理.
    private void FadeUpdate()
    {
        // フェードインフラグ.
        if (_color.a >= 1.0f)
        {
            _isPush = false;
        }

        // 透明度を固定化.
        if (_color.a <= 0.0f)
        {
            _color.a = 0.0f;
        }

        // フェードイン.
        if (!_isPush)
        {
            _color.a -= 0.01f;
            gameObject.GetComponent<Image>().color = _color;
        }
        else// フェードアウト.
        {
            _color.a += 0.01f;
            gameObject.GetComponent<Image>().color = _color;
        }
    }

    // シーン遷移
    private void SceneTransition()
    {
        // ボタン押したら(ボタン配置は仮).
        if (Input.GetKeyDown("joystick button 3"))
        {
            // ゲートの前にいないときはスキップ.
            if (!SetGateFlag()) return;
            _isPush = true;
        }

        // シーン遷移.
        if (GimmickSceneTransition1_2._instance.GetGateGimmick1() && _color.a >= 0.9f)
        {
            SceneManager.LoadScene("Gimmick1_2_1");
        }
        else if (GimmickSceneTransition1_2._instance.GetGateGimmick2() && _color.a >= 0.9f)
        {
            SceneManager.LoadScene("Gimmick1_2_2");
        }
        else if (GimmickSceneTransition1_2._instance.GetGateGimmick3() && _color.a >= 0.9f)
        {
            SceneManager.LoadScene("Gimmick1_2_3");
        }
        else if (GimmickSceneTransition1_2._instance.GetGateGimmick4() && _color.a >= 0.9f)
        {
            SceneManager.LoadScene("Gimmick1_2_4");
        }

    }
}
