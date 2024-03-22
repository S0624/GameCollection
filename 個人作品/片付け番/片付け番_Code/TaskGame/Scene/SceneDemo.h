//#pragma once
//#include "SceneBase.h"
//#include<memory>	//「スマートポインタ」を使うためのinclude
//class InputState;
//
//class SceneDemo : public SceneBase
//{
//private:
//	//std::shared_ptr<MapChip>m_map;
//	static constexpr int m_fadeInterval = 30;
//	int m_fadeTimer = m_fadeInterval; //フェードタイマー
//	float m_fadeValue = 255; //黒矩形とのブレンド具合
//
//	//フェードインの時のUpdeta関数
//	void FadeInUpdate(const InputState& input);
//	//通常状態のUpdate関数
//	void NormalUpdate(const InputState& input);
//	//フェードアウトの時のUpdate関数
//	void FadeOutUpdate(const InputState& input);
//	//Update用メンバ関数ポインタ
//	void (SceneDemo::* m_updateFunc)(const InputState& input);
//
//private:
//	int m_animation = 0;
//	int m_backHandle = 0;
//	int m_roomHandle = 0;
//	int m_BgSound = 0;
//	int m_displayCount = 0;
//	int m_demoFont = 0;
//	int m_guideFont = 0;
//	int m_strTitle = 0;
//	int m_strEx = 0;
//	int m_strNum = 0;
//	int m_buttonHandle = 0;
//
//
//public:
//	SceneDemo(SceneManager& manager);
//	~SceneDemo();
//
//	void Update(const InputState& input);
//	void Draw();
//};
//
