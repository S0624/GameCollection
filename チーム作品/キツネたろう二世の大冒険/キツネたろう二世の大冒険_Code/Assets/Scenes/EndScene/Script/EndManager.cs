using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EndManager : MonoBehaviour
{
    public TitleWindow Window;
    public GameObject Rabbit;
    public GameObject Player;
    public GameObject Boss;
    private SoundManager SndManager;
    private MoveBackGround _bg;
    private StaffRool _rool;
    private FadeScene _fade;

    private void Start()
    {
        SndManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        _bg = GetComponent<MoveBackGround>();
        _rool = GetComponent<StaffRool>();
        _fade = GameObject.Find("Fade").GetComponent<FadeScene>();
    }

    private void FixedUpdate()
    {
        SndManager.PlayBGM("EndScene_BGM");
        Window.WindowUpdate();
        _bg.BgMove();
        _rool.RoolUpdate();
        Rabbit.GetComponent<EndRabbit>().RabbitUpdate();
        Player.GetComponent<EndPlayer>().PlayerUpdate();
        Boss.GetComponent<EndBoss>().BossUpdate();

        if (Input.GetKey(KeyCode.L))
        {
            for (int i = 0; i < 3; i++)
            {
                _rool.RoolUpdate();
                Rabbit.GetComponent<EndRabbit>().RabbitUpdate();
                Player.GetComponent<EndPlayer>().PlayerUpdate();
                Boss.GetComponent<EndBoss>().BossUpdate();
            }
        }


        if (_rool.GetIsEnd())
        {
            _fade._isFadeOut = true;
        }

        if (_rool.GetIsEnd() && _fade.GetAlphColor() >= 0.98f)
        {
            SndManager.StopBgm();
            SceneManager.LoadScene("TitleScene");
        }
    }
}
