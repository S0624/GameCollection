using Mono.Cecil.Cil;
using System.Collections;
using System.Collections.Generic;
//using UnityEditor.ShaderGraph.Internal;
using UnityEngine;
using UnityEngine.UI;

public class TitleOption : MonoBehaviour
{
    // ボリュームの変更量
    private const float kValueNum = 0.02f;

    public GameObject OptionCas;
    public Slider BgmSlider;
    public Slider SeSlider;
    public TitleSelect SelectFrame;
    public SoundManager SndManager;

    public GameObject BgmHandle;
    public GameObject SeHandle;

    private bool _isSelect;
    private int _index;
    // 音量調節傾け度合い
    float axisPower;

    float _fadeAlpha;
    private Color _handleColor;
    // フェードインアウトの真偽.
    private bool _isFadeIn;
    private bool _isFadeOut;

    void Start()
    {
        OptionCas.SetActive(false);
        _isSelect = false;
        _isFadeIn = false;
        _isFadeOut = false;
        _handleColor = SelectFrame.GetComponent<Image>().color;
    }

    // Update is called once per frame
    public void OptionUpdate()
    {
        // 非アクティブなら処理しない
        if (!OptionCas.activeSelf) return;

        // Bボタン押したら終了
        if (Input.GetKeyDown("joystick button 0"))
        {
            SndManager.PlaySE("1_3_1_OneBack");

            _isFadeIn = false;
            _isFadeOut = true;
        }

        // Aボタン押したら変更開始
        if (Input.GetKeyDown("joystick button 1"))
        {
            SndManager.PlaySE("1_3_1_Push");

            _index = SelectFrame.GetIndex();

            if (_isSelect)
            {
                _handleColor.r = 1.0f;
                _handleColor.g = 1.0f;
                _handleColor.b = 1.0f;
            }
            else
            {
                _handleColor.r = 1.0f;
                _handleColor.g = 0.54f;
                _handleColor.b = 0.0f;
            }

            ChangeHandle();

            _isSelect = !_isSelect;
        }

        if (!_isSelect)
        {
            SelectFrame.SelectUpdate();
        }

        if (_isSelect)
        {
            // スティックによる音量調節
            axisPower = Input.GetAxis("Horizontal");
            ChangeVolume(kValueNum * axisPower);
        }
    }

    // 音の調整
    private void ChangeVolume(float volume)
    {
        if (_index == 0)
        {
            SndManager.MasterVolumeChangeBgm(volume);
        }
        else
        {
            SndManager.MasterVolumeChangeSe(volume);
        }
    }

    // スライダーの位置を変更
    public void ChangeValue()
    {
        BgmSlider.value = SndManager.GetVolumeBgm();
        SeSlider.value = SndManager.GetVolumeSe();
    }

    // 選択しているとき色をオレンジに
    private void ChangeHandle()
    {
        if (_index == 0)
        {
            BgmHandle.GetComponent<Image>().color = _handleColor;
        }
        else
        {
            SeHandle.GetComponent<Image>().color = _handleColor;
        }
    }

    // フェード処理.
    public void FadeUpdate()
    {
        // 非アクティブなら処理しない
        if (!OptionCas.activeSelf) return;

        if (_fadeAlpha <= 0.0f && _isFadeOut)
        {
            _isFadeOut = false;
            OptionCas.SetActive(false);
        }
        // 透明度を固定化.
        if (_fadeAlpha >= 1.0f)
        {
            _fadeAlpha = 1.0f;
            _isFadeIn = false;
        }

        // フェードイン.
        if (_isFadeIn)
        {
            _fadeAlpha += 0.08f;
            OptionCas.GetComponent<CanvasGroup>().alpha = _fadeAlpha;
        }
        // フェードアウト.
        else if (_isFadeOut)
        {
            _fadeAlpha -= 0.08f;
            OptionCas.GetComponent<CanvasGroup>().alpha = _fadeAlpha;
        }
    }

    public bool GetIsActive()
    {
        return OptionCas.activeSelf;
    }

    public void Indicate()
    {
        // アクティブなら処理しない
        if (OptionCas.activeSelf) return;

        OptionCas.SetActive(true);
        OptionCas.GetComponent<CanvasGroup>().alpha = _fadeAlpha;
        _isFadeIn = true;
    }
}
