#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneMapSelect.h"
#include "../Object/Player/Dinosaur/Dinosaur.h"
#include "../Object/Player/Elf/Elf.h"
#include "../Object/Player/Kinnikurou/Kinnikurou.h"
#include "../Object/Player/Witch/Witch.h"
#include "../Util/Vec2.h"
#include "../StringFunction.h"

#include "../UIAnimation.h"
#include "../ButtonNo.h"

#include "../Util/Sound.h"


namespace
{
	// プレイヤーのサイズ
	constexpr int kPlayerSize = 3;
	constexpr int kPlayerNum = 2;
	constexpr int kFonstSize = 250;
	constexpr int kWinNameFontPosX = 100;
	constexpr int kWinNameFontPosY = 100;
	constexpr int kColor = 0x000000;

	// フォントデータ
	const char* kFontName = "Valentina";
	const char* kFontName2 = "851レトロゴ";

}

SceneResult::SceneResult(bool isVictory1P, bool isVictory2P, PlayerBase* player1P, PlayerBase* player2P) :
	m_isTitle(false),
	m_isRetry(false),
	m_isVictory1P(isVictory1P),
	m_isVictory2P(isVictory2P)
{
	m_pPlayer[0] = nullptr;
	m_pPlayer[1] = nullptr;
	m_pPlayer[0] = player1P;
	m_pPlayer[1] = player2P;

	m_pString = new StringFunction;
	m_pAnimUI = new UIAnimation;

	m_font1 = LoadFontDataToHandle(kFontName, 100);
	m_font2 = LoadFontDataToHandle(kFontName2, 200);
	m_font3 = LoadFontDataToHandle(kFontName2, 250);
}

SceneResult::~SceneResult()
{
	delete m_pPlayer[0];
	delete m_pPlayer[1];
	delete m_pString;
	delete m_pAnimUI;

	DeleteFontToHandle(m_font1);
	DeleteFontToHandle(m_font2);
	DeleteFontToHandle(m_font3);
}

void SceneResult::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::ResultBgm, 200);

	bool isWin[2] = { m_isVictory1P ,m_isVictory2P };
	const char* fontName = "Valentina";
	const char* fontName2 = "851レトロゴ";

	// ボタンの初期設定
	m_pAnimUI->AddButton(Game::kScreenWidth / 2 - 300, Game::kScreenHeight - 170, 7, 3, ButtonNo::A);
	// 文字の初期設定
	m_pString->Add(Game::kScreenWidth/2 - 200, Game::kScreenHeight - 200, "もどる", 0xffffff, 100, fontName2);
	// UI初期化
	m_pAnimUI->Init();

	for (int i = 0; i < kPlayerNum; i++)
	{
		// どちらのプレイヤーが勝利したか
		if (isWin[i])
		{
			// プレイヤーの初期化
		//	m_pPlayer[i]->Init();
			// 魔女が消えるためUpdate関数を呼び出し応急処置
		//	m_pPlayer[i]->Update();
			// どのキャラクターが勝利したか
			if (dynamic_cast<Dinosaur*>(m_pPlayer[i]))
			{
				// 文字の左上座標
				Vec2 winPos = { static_cast<float>(Game::kScreenWidth) / 2.0f,
								static_cast<float>(Game::kScreenHeight) / 2.0f };
				// 表示文字
				const char* WinDino = "だいなそー WIN";
				// キャラクターの位置変更
				m_pPlayer[i]->SetPos(winPos);
				// キャラクターのサイズ変更
				m_pPlayer[i]->SetSize(kPlayerSize);
				// キャラクターのサイズ変更
				m_pString->Add(kWinNameFontPosX, kWinNameFontPosY, WinDino, kColor, kFonstSize, fontName2);
			}
			// どのキャラクターが勝利したか
			else if (dynamic_cast<Elf*>(m_pPlayer[i]))
			{
				// 文字の左上座標
				Vec2 winPos = { static_cast<float>(Game::kScreenWidth) / 2.0f,
					static_cast<float>(Game::kScreenHeight) / 2.0f - 500.0f };
				// 表示文字
				const char* WinEfl = "Elf WIN";
				// キャラクターの位置変更
				m_pPlayer[i]->SetPos(winPos);
				// キャラクターのサイズ変更
				m_pPlayer[i]->SetSize(kPlayerSize);
				// キャラクターのサイズ変更
				m_pString->Add(kWinNameFontPosX, kWinNameFontPosY, WinEfl, kColor, kFonstSize, fontName);
			}
			// どのキャラクターが勝利したか
			else if (dynamic_cast<Kinnikurou*>(m_pPlayer[i]))
			{
				// 文字の左上座標
				Vec2 winPos = { static_cast<float>(Game::kScreenWidth) / 2.0f,
					static_cast<float>(Game::kScreenHeight) / 2.0f };
				// 表示文字
				const char* WinKinniKun = "きんにくん WIN";
				// キャラクターの位置変更
				m_pPlayer[i]->SetPos(winPos);
				// キャラクターのサイズ変更
				m_pPlayer[i]->SetSize(kPlayerSize);
				// キャラクターのサイズ変更
				m_pString->Add(kWinNameFontPosX, kWinNameFontPosY, WinKinniKun, kColor, kFonstSize, fontName2);
			}
			// どのキャラクターが勝利したか
			else if (dynamic_cast<Witch*>(m_pPlayer[i]))			
			{
				// 文字の左上座標
				Vec2 winPos = { static_cast<float>(Game::kScreenWidth) / 2.0f,
					static_cast<float>(Game::kScreenHeight) / 2.0f };
				// 表示文字
				const char* WinWitch = "Witch WIN";
				// キャラクターの位置変更
				m_pPlayer[i]->SetPos(winPos);
				// キャラクターのサイズ変更
				m_pPlayer[i]->SetSize(kPlayerSize);
				// キャラクターのサイズ変更
				m_pString->Add(kWinNameFontPosX, kWinNameFontPosY, WinWitch, kColor, kFonstSize, fontName);
			}
		}
	}
}

void SceneResult::End()
{
	m_pPlayer[0]->End();
	m_pPlayer[1]->End();

	m_pAnimUI->End();

	// BGM 停止
	Sound::stopBgm(Sound::ResultBgm);

}

SceneBase* SceneResult::Update()
{

	m_pAnimUI->Update();

	// BGM ループ
	Sound::loopBgm(Sound::ResultBgm);

	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();

		if (!IsFading() && m_isFadeOut && m_isTitle)
		{
			return (new SceneTitle);
		}
		if (!IsFading() && m_isFadeOut && m_isRetry)
		{
			return (new SceneMapSelect);
		}
	}

	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1,1) || Pad::IsTrigger(PAD_INPUT_2,1) ||
			Pad::IsTrigger(PAD_INPUT_1, 2) || Pad::IsTrigger(PAD_INPUT_2, 2))
		{
			StartFadeOut();
		}
	}

	if (!m_isTitle && !m_isRetry)
	{
		if (Pad::IsTrigger(PAD_INPUT_1, 1) || Pad::IsTrigger(PAD_INPUT_1, 2))
		{
			m_isTitle = true;
		}
		else if (Pad::IsTrigger(PAD_INPUT_2,1) || Pad::IsTrigger(PAD_INPUT_2, 2))
		{
			m_isRetry = true;
		}
	}

	return this;
}

void SceneResult::Draw()
{

	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);
	
	m_pString->Draw();

	// 勝利状況
	// 引き分け
	if ((m_isVictory1P && m_isVictory2P) || (!m_isVictory1P && !m_isVictory2P))
	{
		m_pPlayer[0]->Draw();
		m_pPlayer[1]->Draw();
	}
	// 1Pの勝利
	else if (m_isVictory1P)
	{
		m_pPlayer[0]->Draw();
		
	}
	// 2Pの勝利
	else if(m_isVictory2P)
	{
		m_pPlayer[1]->Draw();
	}
	
	m_pAnimUI->Draw();
	m_pString->Draw();

	SceneBase::DrawFade();
}
