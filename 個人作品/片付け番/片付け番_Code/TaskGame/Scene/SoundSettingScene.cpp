#include "SoundSettingScene.h"
#include"../UI/InputState.h"
#include"../SoundManager.h"
#include"DxLib.h"
#include"SceneManager.h"

namespace
{
    constexpr int init_wait_interval = 60;  //キー入力待ち間隔初期値
    constexpr int wait_interval_decrement_period = 5;  //入力待ち間隔が落ちていく感覚
}

SoundSettingScene::SoundSettingScene(SceneManager& manager) :
    SceneBase(manager)
{

}
void SoundSettingScene::Update(const InputState& input)
{
    auto& soundMgr = SoundManager::GetInstance();
    if (input.IsTrigger(InputType::pause))
    {
        m_manager.PopScene();
    }
}

void SoundSettingScene::Draw()
{
    constexpr int pw_width = 450;                             //キーコンフィグ枠の幅
    constexpr int pw_height = 350;                            //キーコンフィグ枠の高さ
    constexpr int pw_start_x = (640 - pw_width) / 2 + 50;     //キーコンフィグ枠に左
    constexpr int pw_start_y = (480 - pw_height) / 2 + 50;    //キーコンフィグ枠上
    //サウンドセッテイングセロファン(黒い)
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0x008800, true);

    //キーコンフィグメッセージ
    DrawString(pw_start_x + 10, pw_start_y + 10, L"SoundSetting", 0xffffaa);
    auto& soundMgr = SoundManager::GetInstance();
    //BGMの設定
    DrawFormatString(pw_start_x + 20, pw_start_y + 40, 0xffffaa, L"SE　Volume = %d", soundMgr.GetSEVolume());
    //SEの設定
    DrawFormatString(pw_start_x + 20, pw_start_y + 80, 0xffffaa, L"BGM　Volume = %d", soundMgr.GetBGVolume());
    //サウンドセッテイング枠線
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0xffffff, false);
}
