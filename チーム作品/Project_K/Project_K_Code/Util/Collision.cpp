#include "Collision.h"
#include"../Object/Player/Dinosaur/Dinosaur.h"
#include"../Object/Player/Kinnikurou/Kinnikurou.h"
#include<cassert>

#include"../Object/Shot/ShotBase.h"

namespace
{
	//ショット最大数
	constexpr int kShotNum = 4;
}

Collision::Collision(PlayerBase* Player1, PlayerBase* Player2)
{
	m_Player[0] = Player1;
	m_Player[1] = Player2;
}

Collision::~Collision()
{
}

// プレイヤー2の攻撃がプレイヤー1に当たったか
bool Collision::IsColl1()
{
	if (!m_Player[1]->GetAttackFlag())
	{
		return false;
	}

	int PlayerLeft = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetSizeLeft();
	int PlayerTop = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetSizeTop();
	int PlayerRight = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetSizeRight();
	int PlayerBottom = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetSizeBottom();

	int PlayerAtkLeft = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetAttackSizeLeft();
	int PlayerAtkTop = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetAttackSizeTop();
	int PlayerAtkRight = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetAttackSizeRight();
	int PlayerAtkBottom = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetAttackSizeBottom();

	if (PlayerLeft > PlayerAtkRight) return false;
	if (PlayerRight < PlayerAtkLeft) return false;
	if (PlayerTop > PlayerAtkBottom) return false;
	if (PlayerBottom < PlayerAtkTop)return false;

	
	
	return true;
} // 

// プレイヤー1の攻撃がプレイヤー2に当たったか
bool Collision::IsColl2()
{
	if (!m_Player[0]->GetAttackFlag())
	{
		return false;
	}

	int PlayerLeft = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetSizeLeft();
	int PlayerTop = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetSizeTop();
	int PlayerRight = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetSizeRight();
	int PlayerBottom = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetSizeBottom();

	int PlayerAtkLeft = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetAttackSizeLeft();
	int PlayerAtkTop = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetAttackSizeTop();
	int PlayerAtkRight = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetAttackSizeRight();
	int PlayerAtkBottom = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetAttackSizeBottom();

	if (PlayerLeft > PlayerAtkRight) return false;
	if (PlayerRight < PlayerAtkLeft) return false;
	if (PlayerTop > PlayerAtkBottom) return false;
	if (PlayerBottom < PlayerAtkTop)return false;



	return true;
}

// プレイヤー2のショットがプレイヤー1に当たったか
bool Collision::ShotColl1()
{
	int PlayerLeft = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetSizeLeft();
	int PlayerTop = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetSizeTop();
	int PlayerRight = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetSizeRight();
	int PlayerBottom = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetSizeBottom();

	

	for (int i = 0; i < kShotNum; i++)
	{
		if (!m_Player[1]->GetShot(i)->GetExist())
		{
			continue;
		}


		int PlayerShotLeft = static_cast<int>(m_Player[1]->GetShot(i)->GetPos().x + m_Player[1]->GetShot(i)->GetSizeLeft());
		int PlayerShotTop = static_cast<int>(m_Player[1]->GetShot(i)->GetPos().y + m_Player[1]->GetShot(i)->GetSizeTop());
		int PlayerShotRight = static_cast<int>(m_Player[1]->GetShot(i)->GetPos().x + m_Player[1]->GetShot(i)->GetSizeRight());
		int PlayerShotBottom = static_cast<int>(m_Player[1]->GetShot(i)->GetPos().y + m_Player[1]->GetShot(i)->GetSizeBottom());

		if (PlayerLeft > PlayerShotRight) continue;
		if (PlayerRight < PlayerShotLeft) continue;
		if (PlayerTop > PlayerShotBottom) continue;
		if (PlayerBottom < PlayerShotTop) continue;

		m_Player[1]->GetShot(i)->SetExist();
		return true;
	}

	return false;
}

// プレイヤー1のショットがプレイヤー2に当たったか
bool Collision::ShotColl2()
{
	int PlayerLeft = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetSizeLeft();
	int PlayerTop = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetSizeTop();
	int PlayerRight = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetSizeRight();
	int PlayerBottom = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetSizeBottom();

	

	for (int i = 0; i < kShotNum; i++)
	{
		if (!m_Player[0]->GetShot(i)->GetExist())
		{
			continue;
		}


		int PlayerShotLeft = static_cast<int>(m_Player[0]->GetShot(i)->GetPos().x + m_Player[0]->GetShot(i)->GetSizeLeft());

	//	printfDx("%d\n", PlayerShotLeft);
		int PlayerShotTop = static_cast<int>(m_Player[0]->GetShot(i)->GetPos().y + m_Player[0]->GetShot(i)->GetSizeTop());
		int PlayerShotRight = static_cast<int>(m_Player[0]->GetShot(i)->GetPos().x + m_Player[0]->GetShot(i)->GetSizeRight());
		int PlayerShotBottom = static_cast<int>(m_Player[0]->GetShot(i)->GetPos().y + m_Player[0]->GetShot(i)->GetSizeBottom());

		if (PlayerLeft > PlayerShotRight) continue;
		if (PlayerRight < PlayerShotLeft) continue;
		if (PlayerTop > PlayerShotBottom) continue;
		if (PlayerBottom < PlayerShotTop) continue;

		m_Player[0]->GetShot(i)->SetExist();
		return true;
	}

	return false;
}

// プレイヤーの攻撃同士が当たったか
bool Collision::AttackColl()
{
	if (!m_Player[0]->GetAttackFlag())
	{
		return false;
	}

	if (!m_Player[1]->GetAttackFlag())
	{
		return false;
	}

	int PlayerAtkLeft1 = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetAttackSizeLeft();
	int PlayerAtkTop1 = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetAttackSizeTop();
	int PlayerAtkRight1 = static_cast<int>(m_Player[0]->GetPos().x) + m_Player[0]->GetAttackSizeRight();
	int PlayerAtkBottom1 = static_cast<int>(m_Player[0]->GetPos().y) + m_Player[0]->GetAttackSizeBottom();

	int PlayerAtkLeft2 = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetAttackSizeLeft();
	int PlayerAtkTop2 = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetAttackSizeTop();
	int PlayerAtkRight2 = static_cast<int>(m_Player[1]->GetPos().x) + m_Player[1]->GetAttackSizeRight();
	int PlayerAtkBottom2 = static_cast<int>(m_Player[1]->GetPos().y) + m_Player[1]->GetAttackSizeBottom();

	if (PlayerAtkLeft1 > PlayerAtkRight2) return false;
	if (PlayerAtkRight1 < PlayerAtkLeft2) return false;
	if (PlayerAtkTop1 > PlayerAtkBottom2) return false;
	if (PlayerAtkBottom1 < PlayerAtkTop2) return false;

	return true;
}