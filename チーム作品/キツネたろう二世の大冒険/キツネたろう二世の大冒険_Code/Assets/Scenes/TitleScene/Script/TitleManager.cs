using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TitleManager : MonoBehaviour
{
    public TitleAnimDirector AnimDirector;
    public GameObject Canvas;
    public FadeScene FadeSrc;
    public SoundManager SndManager;
    private TitleWindow _window;
    private TitleSelect _select;
    private TitleOption _option;
    private MoveBackGround _bg;

    private void Start()
    {
        _window = GameObject.Find("windmill:windmill:polySurface132").GetComponent<TitleWindow>();
        _select = GameObject.Find("SeelctFrame").GetComponent<TitleSelect>();
        _option = GetComponent<TitleOption>();
        _bg = GetComponent<MoveBackGround>();
    }

    private void Update()
    {
        // フェード処理に移行したら変更しない
        if (FadeSrc._isFadeOut) return;
        
        if (GetComponent<TitleOption>().GetIsActive())
        {
            _option.OptionUpdate();

            return;
        }

        _select.SelectUpdate();
        if (Input.GetKeyDown("joystick button 0"))
        {
            SndManager.PlaySE("1_3_1_Push");

            if (_select.GetIndex() == 0)
            {
                OnStart();
            }
            else
            {
                OnOption();
            }
        }
    }

    private void FixedUpdate()
    {
        SndManager.PlayBGM("TitleScene_BGM");
        _window.WindowUpdate();
        _bg.BgMove();

        if (FadeSrc._isFadeIn)
        {
            Canvas.GetComponent<CanvasGroup>().alpha = 1.0f - FadeSrc.GetAlphColor();
        }

        if (FadeSrc._isFadeOut)
        {
            Canvas.GetComponent<CanvasGroup>().alpha = 1.0f - FadeSrc.GetAlphColor();

            if (FadeSrc.GetAlphColor() > 1.0f)
            {
                SndManager.StopBgm();
                SceneManager.LoadScene("MainScene1-1");
            }
        }
        else
        {
            _option.FadeUpdate();
            _option.ChangeValue();
        }
    }

    // スタートする処理.
    public void OnStart()
    {
        AnimDirector.SetStart();
        FadeSrc._isFadeOut = true;
    }

    // オプション開く処理.
    public void OnOption()
    {
        _option.Indicate();
    }
}
