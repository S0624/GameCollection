// クリアシーンマネージャー.

using UnityEngine;
using UnityEngine.SceneManagement;

public class ClearSceneManager : MonoBehaviour
{
    // 現在の経過時間.
    public int _currentTime;
    // フェード.
    private FadeScene _fade;

    private SoundManager _soundManager;

    private void Start()
    {
        _fade = GameObject.Find("Fade").GetComponent<FadeScene>();
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        _soundManager.PlaySE("1_3_MainSceneClear");
    }

    private void FixedUpdate()
    {
        _currentTime++;

        if(_currentTime >= 400)
        {
            _fade._isFadeOut = true;
        }

        if(_fade._color.a >= 0.9f && _currentTime >= 400)
        {
            SceneManager.LoadScene("EndScene");
        }
    }
}
