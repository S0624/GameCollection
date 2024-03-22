//#include "SceneDemo.h"
//#include "SceneTitle.h"
//#include"SceneManager.h"
//#include"../UI/game.h"
//#include"../UI/InputState.h"
//#include"../GameManager.h"
//#include<DxLib.h>

//void SceneDemo::FadeInUpdate(const InputState& input)
//{
//	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
//	if (--m_fadeTimer == 0) {
//		m_updateFunc = &SceneDemo::NormalUpdate;
//		m_fadeValue = 0;
//	}
//}
//
//void SceneDemo::NormalUpdate(const InputState& input)
//{
//	//アニメーションの処理（ボタン）
//	m_animation++;
//	if (m_animation > 60)
//	{
//		m_displayCount++;
//		if (m_displayCount >= 5 * 4)
//		{
//			m_animation = 0;
//			m_displayCount = 0;
//		}
//	}
//
//
//	//「次へ」ボタンが押されたら次へ
//	if (input.IsTrigger(InputType::next))
//	{
//		m_updateFunc = &SceneDemo::FadeOutUpdate;
//	}
//}
//
//void SceneDemo::FadeOutUpdate(const InputState& input)
//{
//	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
//	if (++m_fadeTimer == m_fadeInterval) {
//		m_manager.ChangeScene(new SceneTitle(m_manager));
//		return;
//	}
//}
//
//SceneDemo::SceneDemo(SceneManager& manager) :
//	SceneBase(manager),
//	m_updateFunc(&SceneDemo::FadeInUpdate)
//{
//	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");
//	m_guideFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 42, -1, -1);
//	m_demoFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 64, -1, -1);
//	m_strEx = static_cast<int>(strlen("Aボタンを押してください"));
//}
//
//SceneDemo::~SceneDemo()
//{
//}
//
//void SceneDemo::Update(const InputState& input)
//{
//	(this->*m_updateFunc)(input);
//}
//
//void SceneDemo::Draw()
//{
//	int posX = (Game::kScreenWindth -
//		GetDrawStringWidthToHandle(L"Aボタンを押してください", m_strEx, m_guideFont)) / 2;
//	int posY = Game::kScreenHeight - 200;
//	int animeNum = (m_displayCount / 5) + 1;
//
//	//点滅処理
//	DrawStringToHandle(posX + 5, posY, L" ボタンを押してください", 0xffffff, m_guideFont);	//ガイドの表示
// 
//	//ボタンの処理（アニメーションの追加）
//	my::MyDrawRectRotaGraph(posX - 5, posY + 25,			//表示座標
//		32 + (16 * animeNum), 16 + (16 * 2),			//切り取り左上
//		16, 16,							//幅、高さ
//		3.0f, 0.0f,						//拡大率、回転角度
//		m_buttonHandle, true);
//}