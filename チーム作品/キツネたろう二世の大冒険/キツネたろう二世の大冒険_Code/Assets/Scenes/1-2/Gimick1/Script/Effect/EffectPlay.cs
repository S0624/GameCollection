using UnityEngine;

// エフェクトを再生するスクリプト.
public class EffectPlay : MonoBehaviour
{
    // 波紋のエフェクトの取得.
    [SerializeField] private GameObject TapEffect;
    // プレイヤーの手の取得.
    private GameObject _handObject = null;
    // 線のエフェクトの取得.
    private EffectLine _effectLine = null;
    // パネルの名前の取得.
    private string _panelName = null;
    // サウンドの取得(SEを鳴らすために使用).
    private SoundManager _soundManager = null;
    // クリアしたときにclearの画像を表示させる.
    [SerializeField] private GenerateImg _img;
    private bool _isSePlaying = false;
    private int _genereteCount = 0;
    // エフェクトの初期化処理.
    public void EffectInit()
    {
        _effectLine = GetComponent<EffectLine>();
        _effectLine.LineInit();
    }
    // パネルの名前の取得.
    public void GetPanelName(string name)
    {
        _panelName = name;
    }
    // サウンドのデータを取得する.
    public void GetSoundData(SoundManager sound)
    {
        _soundManager = sound;
    }
    // プレイヤーの手取得.
    public void GetPlayerObject(GameObject handobj)
    {
        // オブジェクトを取得.
        _handObject = handobj;
    }
    // ボタンを押したかどうかの取得.
    public void CheckTap(bool buttonFlag)
    {
        _effectLine.LineEndDraw();
        // ボタンを押したフラグがたっていたら.
        if (buttonFlag)
        {
            NewTapEffect();
        }
    }
    //タップエフェクトを出す
    private void NewTapEffect()
    {
        // 効果音を鳴らす.
        _soundManager.PlaySE("1_2_1_Button");
        // 手の位置と回転率をそのままいれて手の位置から波紋エフェクトを生成.
        Instantiate(TapEffect, _handObject.transform.position, _handObject.transform.localRotation, transform);
        _effectLine.LineGenerate(_handObject.transform.position, _panelName);
    }
    // Gimmickをクリアしたときのエフェクトの処理.
    public void EffectClearGenerete(bool generete)
    {
        // クリアしていたら.
        if (generete)
        {
            if (!_isSePlaying)
            {
                if (_genereteCount < 2)
                {
                    _genereteCount++;
                    // クリアテキストの表示.
                    _img.GenerateClearText();
                }
                // 一回だけならしたいのでフラグをtrueにする.
                _isSePlaying = true;
                // クリア音を鳴らす.
                _soundManager.PlaySE("1_2_1_Clear");
            }
            // 最後の線のエフェクトを生成する.
            _effectLine.LineClearGenerete(_panelName);
        }
        else
        {
            _isSePlaying =false;
        }
    }
    // ギミックを間違った時にエフェクトをすべて消す.
    public void EffectDestory(bool destory)
    {
        if (destory)
        {
            // 不正解テキストの表示.
            _img.GenerateResetText();
            // 不正解の音を鳴らす.
            _soundManager.PlaySE("1_2_1_Miss");
            // 線のエフェクトを壊す.
            _effectLine.LineDestroy(_panelName);
        }
    }
    // エフェクトの記憶しているポジションをリセットする.
    public void EffectPosReset()
    {
        _effectLine.PosAllErase(_panelName);
    }
    // クリアしたらテキストを生成する.
    public void GenaretaImg()
    {
        // クリアしたことをテキストで表示.
        if (_effectLine.GetClearFlag())
        {
            // BGMをとめる.
            _soundManager.StopBgm();
            // 一回だけ画像を生成する.
            _img.GenerateCompleteImage();
        }
    }
}
