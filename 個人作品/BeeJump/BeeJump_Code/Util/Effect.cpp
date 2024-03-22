#include "Effect.h"
// EffekseerForDXLib.hをインクルードします。
//#include "EffekseerForDXLib.h"
#include<cassert>
Effect::Effect():
    m_effectHandle(),
    m_currentPlayEffect(),
    m_pos()
{
    m_pos.x = 0;
    m_pos.y = 10;
    m_pos.z = -50;
}

Effect::~Effect()
{
    //// 終了時にエフェクトの削除
    //DeleteEffekseerEffect(m_effectHandle);
    //Effkseer_End();
}

void Effect::Init()
{
    //SetUseDirect3DVersion(DX_DIRECT3D_11);

    //// フルスク切り替え時にデバイスがロストするのを防止
    //SetChangeScreenModeGraphicsSystemResetFlag(false);
    //Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    //// エフェクトのロード
    //m_effectHandle = LoadEffekseerEffect("Data/Effect/FireFlower.efk", 1.0f);
    //assert(m_effectHandle != -1);
    //m_sampleHandle = LoadGraph("Data/Img/Sample.png");
}

void Effect::Update()
{
    //m_pos.y = 10;
    //m_pos.z = -50;
    //m_pos.x += 10;

    //Effekseer_Sync3DSetting(); // Dxlibの3D設定をEffekseerに反映
    //// 再生中だったら再生しない
    //if (IsEffekseer3DEffectPlaying(m_currentPlayEffect))
    //{
    //    // スペースが押されたら
    //    if (Pad::IsTrigger(PAD_INPUT_3))
    //    {
    //        // もし再生中だったら止める
    //        StopEffekseer3DEffect(m_currentPlayEffect);
    //        // 位置をずらす
    //        m_pos.x = 120;
    //        m_currentPlayEffect = PlayEffekseer3DEffect(m_effectHandle);
    //        // エフェクトの位置を設定
    //        SetPosPlayingEffekseer3DEffect(m_currentPlayEffect, m_pos.x, m_pos.y, m_pos.z);
    //        assert(m_effectHandle != -1);

    //    }
    //}
    ////DrawGraph(0, 0, m_sampleHandle, true);
    //// エフェクトの更新処理
    //UpdateEffekseer3D();

}

void Effect::Draw()
{
    // エフェクトの表示
    //DrawEffekseer3D();
}