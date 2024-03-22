#include "Dinosaur.h"
#include "../../../condition.h"
#include "DinosaurStateManager.h"
#include"../../Shot/ShotBase.h"
#include"../../Shot/DinoShot.h"
#include"../../Shot/NullShot.h"
#include<cassert>

namespace
{
	const char* kFilename = "Data/Image/Player/kyouryuu/Enemy.png";
	const char* kShotFilename = "Data/Image/Player/kyouryuu/Shot.png";

	constexpr int kAttackDuration = 10; //攻撃持続時間
}

Dinosaur::Dinosaur() :
	m_handle(-1)
{
	m_handle = LoadGraph(kFilename);
	m_shotHandle = LoadGraph(kShotFilename);
	m_pStateManager = new DinosaurStateManager(m_handle);
	m_pStateManager->Init();
	m_pos = { 0.0f,0.0f };
}

Dinosaur::~Dinosaur()
{
}

void Dinosaur::Init()
{
	//プレイヤーのサイズを代入
	m_sizeLeft = -80;
	m_sizeTop = -50;
	m_sizeRight = 80;
	m_sizeBottom = 110;
	
	CharDefaultPos(m_pStateManager->m_lookLeft);

	m_pos.y = 550;
}

void Dinosaur::End()
{
}

void Dinosaur::Update()
{
	// hpが0になったらm_StateManagerのm_deadFlagをtrueに
	if (m_hp <= 0)
	{
		m_pStateManager->SetDeadFlag();
	}

	//ダメージを食らってからm_onDamageFrameが0になるまで攻撃を受けない
	KnockBack();
	if (m_onDamageFrame > 0)
	{
		m_pStateManager->SetondamageFlag(true); //攻撃を受けている状態のときtrue
	}
	else
	{
		m_pStateManager->SetondamageFlag(false); //攻撃を受けている状態のときfalse
	}

	// StateManagerのアップデート
	m_pStateManager->Update(m_padNum);

	GetAttackSize(); //攻撃のサイズ取得

	// ダメージ取得
	m_damage = m_pStateManager->GetOnDamage();

	// 攻撃フラグ取得
	m_attackFlag = m_pStateManager->GetAttackFlag();

	// 攻撃フラグがtrueのとき
	if (m_attackFlag)
	{
		// カウントを増やす
	//	attackCountUp();
	}
	else// falseのとき
	{
		// カウントを0に
		m_attackFrameCount = 0;
	}

	// m_posの値を取得
	m_pos += m_pStateManager->GetVec();

	if (m_pStateManager->GetVec().y == 0)
	{
		m_pos.y += 5;
	}

	if (m_pos.y > 550)
	{
		m_pos.y = 550;
	}

	for (int i = 0; i < kShotMax; i++)
	{
		// ショットの存在が消え、NullShotではないときm_ShotにNullShotを入れる
		if (!m_pShot[i]->GetExist() && !m_pShot[i]->GetNullShot())
		{
			m_pShot[i] = new NullShot();
		}
	}

	//ショットアップデート
	for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i]->Update();
	}

	////いなくなった敵は消えてもらう
	////消す命令のくせに、実際には決してなくて、後ろによけてるだけ
	//auto rmIt = std::remove_if(//条件に合致したものを消す
	//	m_Shot.begin(),	//対象はm_Enemyの最初から
	//	m_Shot.end(),		//最後まで
	//	//消えてもらう条件を表すラムダ式
	//	//trueだと消える。falseだと消えない
	//	[](ShotBase* &pShot) {
	//		return !pShot->IsExist();
	//	});

	////実際に範囲を指定して消す
	//m_Shot.erase(rmIt, m_Shot.end());
	////ここまでやらないと実際には消えないので注意

	// ショットのフラグたたったとき
	if (m_pStateManager->GetshotFlag())
	{
		for (int i = 0; i < kShotMax; i++)
		{
			// ショットが存在しないとき
			if (!m_pShot[i]->GetExist())
			{
				if (m_pStateManager->GetLookLeft())
				{
					m_pShot[i] = new DinoShot(m_pos, { -15,0 });
				}
				else
				{
					m_pShot[i] = new DinoShot(m_pos, { 15,0 });
				}
				m_pShot[i]->SetHandle(m_shotHandle);
				break; //ループ抜ける
			}
		}
	}
}

void Dinosaur::Draw()
{
	// キャラクター表示
	m_pStateManager->Draw(m_pos, m_sizeUp);

	//ショット表示
	for (int i = 0; i < kShotMax; i++)
	{
		if (m_pShot[i] != nullptr)
		{
			m_pShot[i]->Draw();
		}
	}

	//// m_attackFlagがtrueのとき攻撃当たり判定を表示
	//if (m_attackFlag)
	//{
	//	/*DrawBox(static_cast<int>(m_pos.x) + m_attackSizeLeft, static_cast<int>(m_pos.y) + m_attackSizeTop,
	//		static_cast<int>(m_pos.x) + m_attackSizeRight, static_cast<int>(m_pos.y) + m_attackSizeBottom,
	//		0xff0000, false);*/
	//}

	//DrawBox(static_cast<int>(m_pos.x) + m_sizeLeft, static_cast<int>(m_pos.y) + m_sizeTop,
	//	static_cast<int>(m_pos.x) + m_sizeRight, static_cast<int>(m_pos.y) + m_sizeBottom,
	//	0xff0000, false);
}

void Dinosaur::GetAttackSize()
{
	m_attackSizeLeft = m_pStateManager->GetAttackSizeLeft();
	m_attackSizeTop = m_pStateManager->GetAttackSizeTop();
	m_attackSizeRight = m_pStateManager->GetAttackSizeRight();
	m_attackSizeBottom = m_pStateManager->GetAttackSizeBottom();
}

void Dinosaur::SetAttackFlag(bool attackFlag)
{
	m_attackFlag = attackFlag;
	m_pStateManager->SetAttackFlag();
}

//ShotBase* Dinosaur::GetShot(int i)
//{
//	return m_Shot[i];
//}
