#include "SceneMain.h"
#include "SceneResult.h"
#include "../Object/Player/Dinosaur/Dinosaur.h"
#include "../Object/Player/Elf/Elf.h"
#include "../Object/Player/Kinnikurou/Kinnikurou.h"
#include "../Object/Player/Witch/Witch.h"
#include "../Object/Stage/StageBase.h"
#include "../Util/DrawFunctions.h"
#include "../condition.h"
#include <assert.h>
#include"../Object/Shot/ShotBase.h"
#include"../Util/Collision.h"
#include "../Util/UI.h"
#include "../Util/Sound.h"

#include <iostream>

namespace
{
	// GO!テキストの座標
	const int kGoFontPosX = Game::kScreenWidth / 2 - 100;
	const int kGoFontPosY = Game::kScreenHeight / 2 - 100;

	// TIME OUTのテキストの座標
	const int kTimeUpFontPosX = Game::kScreenWidth / 2 - 150;
	const int kTimeUpFontPosY = Game::kScreenHeight / 2 - 100;

	const char* kFont = "HGP行書体";// フォント

	constexpr int kShotDamage = 7; //ショットダメージ
}

SceneMain::SceneMain(PlayerBase* Player1, PlayerBase* Player2, int StageNo) :
	m_isVictory1P(false),
	m_isVictory2P(false),
	m_countDown(240),
	m_font(-1),
	m_timeUpDrawCount(60)

{
	m_pStageBase = new StageBase(StageNo);

	m_font = CreateFontToHandle(kFont, 140, -1, -1);// 使用するフォント

	m_pPlayer[0] = Player1;
	m_pPlayer[1] = Player2;
	m_pColl = new Collision(m_pPlayer[0], m_pPlayer[1]);
	m_pUi = new UI(m_pPlayer[0]->GetHp(), m_pPlayer[1]->GetHp(), m_pPlayer[0], m_pPlayer[1]);

	m_updateFunc = &SceneMain::UpdateCountDown;
}

SceneMain::~SceneMain()
{
	// メモリの開放
	delete m_pStageBase;
	//delete m_pPlayer[0];
	//delete m_pPlayer[1];
	delete m_pColl;
	delete m_pUi;
	
}

void SceneMain::Init()
{

	// BGM 再生
	Sound::startBgm(Sound::MainBgm, 255);

	m_pPlayer[0]->SetPadNum(1);
	m_pPlayer[1]->SetPadNum(2);

	m_pPlayer[0]->Init();
	m_pPlayer[1]->Init();

	m_pStageBase->Init();
}

void SceneMain::End()
{
	// BGM 停止
	Sound::stopBgm(Sound::MainBgm);


	//m_pPlayer[0]->End();
	//m_pPlayer[1]->End();

}

SceneBase* SceneMain::Update()
{
	// BGM ループ
	Sound::loopBgm(Sound::MainBgm);

	(this->*m_updateFunc)();
	// シーン遷移
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		if (!IsFading() && m_isFadeOut)
		{
			// trueの場合
			// m_isVictory1P = 1Pの勝利
			// m_isVictory2P = 2Pの勝利
			return(new SceneResult(m_isVictory1P, m_isVictory2P, m_pPlayer[0], m_pPlayer[1]));// 1ステージ切り替え
		}
	}

	if (m_pUi->GetTime() <= 0)
	{
		m_timeUpDrawCount--;
		
	}

	// フェードインアウトしていない時
	if (!IsFading())
	{
		// デバッグ用シーン遷移
		if (m_pPlayer[0]->GetHp() <= 0 || m_pPlayer[1]->GetHp() <= 0 || m_timeUpDrawCount <= 0)
		{
			m_pUi->Update();
			StartFadeOut();
		}
	}

	return this;
	//return(new SceneResult(true, m_isVictory2P, m_pPlayer[0], m_pPlayer[1]));// 1ステージ切り替え
}

void SceneMain::Draw()
{
	// ステージの描画
	m_pStageBase->Draw();

	// UIの描画
	m_pUi->Draw();

	// プレイヤーの描画
	m_pPlayer[0]->Draw();
	m_pPlayer[1]->Draw();

	//プレイヤーカーソル描画
	m_pUi->DrawPlayerCursor(m_pPlayer[0]->GetPos(), m_pPlayer[1]->GetPos());

	// 試合始まる前のカウントダウン
	if (m_countDown > 60)
	{
		// 赤フォントの表示
		DrawFormatStringToHandle(kGoFontPosX + 50 + 5,
			kGoFontPosY + 50 + 5, 0x800000, m_font, "%d", m_countDown / 60);
		// 青フォントの表示
		DrawFormatStringToHandle(kGoFontPosX + 50,
			kGoFontPosY + 50, 0x7fffff, m_font, "%d", m_countDown / 60);
	}
	// GO!描画
	if (m_countDown <= 60 && m_countDown > 0)
	{
		DrawFormatStringToHandle(kGoFontPosX + 5,
			kGoFontPosY + 5, 0x800000, m_font, "GO!");
		DrawFormatStringToHandle(kGoFontPosX,
			kGoFontPosY, 0x7fffff, m_font, "GO!");
	}
	if (m_countDown <= 0)
	{
		m_countDown = 0;
	}

	// タイムアウト描画
	if (m_pUi->GetTime() <= 0)
	{
		DrawFormatStringToHandle(kTimeUpFontPosX + 5,
			kTimeUpFontPosY + 5, 0x800000, m_font, "TIME\n UP");
		DrawFormatStringToHandle(kTimeUpFontPosX,
			kTimeUpFontPosY, 0x7fffff, m_font, "TIME\n UP");
	}


	SceneBase::DrawFade();
}

void SceneMain::UpdateCountDown()
{
	// カウントダウン
	m_countDown--;

	if (m_countDown <= 0)

	{
		m_updateFunc = &SceneMain::UpdateMain;
	}

	
}

void SceneMain::UpdateMain()
{
	m_pPlayer[0]->Update();
	m_pPlayer[1]->Update();

	m_pPlayer[0]->moveLimit();
	m_pPlayer[1]->moveLimit();

	// UIの更新処理
	m_pUi->Update();
	m_pUi->GetHp1(m_pPlayer[0]->GetHp());// 1PのHPを渡す
	m_pUi->GetHp2(m_pPlayer[1]->GetHp());// 2PのHPを渡す
	m_pUi->AttackFlag1(false);// 攻撃中のフラグ
	m_pUi->AttackFlag2(false);// 攻撃中のフラグ

	float toPlayer1 = m_pPlayer[1]->GetPos().x - m_pPlayer[0]->GetPos().x;
	float toPlayer2 = m_pPlayer[0]->GetPos().x - m_pPlayer[1]->GetPos().x;

	if (m_pColl->IsColl1())
	{
		m_pPlayer[0]->OnDamage(m_pPlayer[1]->GetDamage());
		m_pPlayer[0]->SetOnDamageFrame();
		m_pPlayer[0]->SetKnockBack(toPlayer1);
		m_pPlayer[1]->SetAttackFlag(false);
		m_pUi->AttackFlag1(true);// 攻撃中のフラグ
	}

	if (m_pColl->IsColl2())
	{
		m_pPlayer[1]->OnDamage(m_pPlayer[0]->GetDamage());
		m_pPlayer[1]->SetOnDamageFrame();
		m_pPlayer[1]->SetKnockBack(toPlayer2);
		m_pPlayer[0]->SetAttackFlag(false);
		m_pUi->AttackFlag2(true);// 攻撃中のフラグ
	}

	if (m_pColl->ShotColl1())
	{
		m_pPlayer[0]->OnDamage(kShotDamage);
		m_pPlayer[0]->SetOnDamageFrame();
		m_pPlayer[0]->SetKnockBack(toPlayer1);
		m_pPlayer[1]->SetAttackFlag(false);
		m_pUi->AttackFlag1(true);// 攻撃中のフラグ
	}

	if (m_pColl->ShotColl2())
	{
		m_pPlayer[1]->OnDamage(kShotDamage);
		m_pPlayer[1]->SetOnDamageFrame();
		m_pPlayer[1]->SetKnockBack(toPlayer2);
		m_pPlayer[1]->SetAttackFlag(false);
		m_pUi->AttackFlag2(true);// 攻撃中のフラグ
	}

	if (m_pColl->AttackColl())
	{
		m_pPlayer[0]->OnDamage(m_pPlayer[1]->GetDamage());
		m_pPlayer[0]->SetOnDamageFrame();
		m_pPlayer[1]->SetAttackFlag(false);
		m_pPlayer[1]->OnDamage(m_pPlayer[0]->GetDamage());
		m_pPlayer[1]->SetOnDamageFrame();
		m_pPlayer[0]->SetAttackFlag(false);
		m_pPlayer[0]->SetKnockBack(toPlayer1);
		m_pPlayer[1]->SetKnockBack(toPlayer2);
	}

	// 1Pの勝利
	if (m_pPlayer[1]->GetHp() <= 0 || (m_pUi->GetTime() <= 0 && m_pPlayer[1]->GetHp() < m_pPlayer[0]->GetHp()))
	{
		m_isVictory1P = true;
	}
	// 2Pの勝利
	else if (m_pPlayer[0]->GetHp() <= 0 || (m_pUi->GetTime() <= 0 && m_pPlayer[1]->GetHp() > m_pPlayer[0]->GetHp()))
	{
		m_isVictory2P = true;
	}

	// デバッグ用シーン遷移
	if (m_pPlayer[0]->GetHp() <= 0 || m_pPlayer[1]->GetHp() <= 0 || m_pUi->GetTime() <= 0)
	{
		m_updateFunc = &SceneMain::UpdateDead;
	}
	// ステージ更新
	m_pStageBase->Update();

//	return this;
}

void SceneMain::UpdateDead()
{
	// ステージの描画
	m_pStageBase->Draw();

	// UIの描画
	m_pUi->Draw();

	// プレイヤーの描画
	m_pPlayer[0]->Draw();
	m_pPlayer[1]->Draw();

	// デバッグ用当たり判定描画
	m_pPlayer[0]->DebugDrawCollision();
	m_pPlayer[1]->DebugDrawCollision();

	SceneBase::DrawFade();
}
