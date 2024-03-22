#pragma once
#include "SceneBase.h"
#include<memory>	//「スマートポインタ」を使うためのinclude
class MapChip;
class InputState;
class Player;

//タイトルシーン
class SceneTitle : public SceneBase
{
private:
	MapChip* m_pMap;
	Player* m_pPlayer;
	static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //フェードタイマー
	float m_fadeValue = 255; //黒矩形とのブレンド具合
	//フェードインの時のUpdeta関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);
	//Update用メンバ関数ポインタ
	void (SceneTitle::* m_updateFunc)(const InputState& input);
private:
	int m_backHandle;
	int m_roomHandle;
	int m_BgSound;
	int m_displayCount;
	int m_TitleFont;
	int m_guideFont;
	int m_strTitle;
	int m_strEx;
	int m_strNum;
	int m_buttonHandle = 0;
	int m_titleHandle = 0;
	int m_animation = 0;
public:
	SceneTitle(SceneManager& manager);
	~SceneTitle();
	void Update(const InputState& input);
	void DrawBackground();
	void Draw();
};