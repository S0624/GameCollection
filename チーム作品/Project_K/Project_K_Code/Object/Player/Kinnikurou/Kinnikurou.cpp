#include "Kinnikurou.h"
#include "../../condition.h"
#include "../../Util/DrawFunctions.h"
#include "../../../Util/Sound.h"
#include "KinnikuIdle.h"
#include "KinnikurouJab.h"
#include "KinnikuMuscle.h"
#include "KinnikuUpper.h"
#include "KinnikuMizo.h"
#include "KinnikuRun.h"
#include "KinnikuJump.h"
#include "KinnikuDead.h"

namespace
{
	// 画像の名前
	const char* const kIdle = "Data/Image/Player/Kinnikurou/Idle.png";
	const char* const kJab = "Data/Image/Player/Kinnikurou/AttackNeutral.png";
	const char* const kMuscle = "Data/Image/Player/Kinnikurou/AttackSide.png";
	const char* const kUpper = "Data/Image/Player/Kinnikurou/AttackUp.png";
	const char* const kMizo = "Data/Image/Player/Kinnikurou/AttackDown.png";
	const char* const kRun = "Data/Image/Player/Kinnikurou/Run.png";
	const char* const kJump = "Data/Image/Player/Kinnikurou/Jump.png";
	const char* const kFall = "Data/Image/Player/Kinnikurou/Fall.png";
	const char* const kDead = "Data/Image/Player/Kinnikurou/Die.png";
}

Kinnikurou::Kinnikurou() :
	m_charHandle(-1),
	m_idleHandle(-1),
	m_jabHandle(-1),
	m_muscleHandle(-1),
	m_UpperHandle(-1),
	m_MizoHandle(-1),
	m_RunHandle(-1),
	m_JumpHandle(-1),
	m_FallHandle(-1),
	m_DeadHandle(-1),
	m_imgPosX(0),
	m_imgPosY(0),
	m_imgWidth(0),
	m_imgHeight(0),
	m_motionCount(0),
	m_initCount(0),
	m_jumpAcc(0),
	m_charDirection(false),
	m_charRun(false),
	m_isAttack(false),
	m_isJump(true)
{
	m_pIdle = new KinnikuIdle;
	m_pJab = new KinnikurouJab;
	m_pMuscle = new KinnikuMuscle;
	m_pUpper = new KinnikuUpper;
	m_pMizo = new KinnikuMizo;
	m_pRun = new KinnikuRun;
	m_pJump = new KinnikuJump;
	m_pDead = new KinnikuDead;
}

Kinnikurou::~Kinnikurou()
{
	delete m_pIdle;
	delete m_pJab;
	delete m_pMuscle;
	delete m_pUpper;
	delete m_pMizo;
	delete m_pRun;
	delete m_pJump;
	delete m_pDead;
}

void Kinnikurou::Init()
{
	m_idleHandle = my::MyLoadGraph(kIdle);
	m_jabHandle = my::MyLoadGraph(kJab);
	m_muscleHandle = my::MyLoadGraph(kMuscle);
	m_UpperHandle = my::MyLoadGraph(kUpper);
	m_MizoHandle = my::MyLoadGraph(kMizo);
	m_RunHandle = my::MyLoadGraph(kRun);
	m_JumpHandle = my::MyLoadGraph(kJump);
	m_FallHandle = my::MyLoadGraph(kFall);
	m_DeadHandle = my::MyLoadGraph(kDead);

	m_pos.x = 0;
	m_pos.y = 0;

	m_imgPosX = 0;
	m_imgPosY = 0;

	m_sizeLeft = -50;
	m_sizeTop = -50;
	m_sizeRight = 50;
	m_sizeBottom = 50;

	CharDefaultPos(m_charDirection);
}

void Kinnikurou::End()
{
	my::MyDeleteGraph(m_idleHandle);
	my::MyDeleteGraph(m_jabHandle);
	my::MyDeleteGraph(m_muscleHandle);
	my::MyDeleteGraph(m_UpperHandle);
	my::MyDeleteGraph(m_MizoHandle);
	my::MyDeleteGraph(m_RunHandle);
	my::MyDeleteGraph(m_JumpHandle);
	my::MyDeleteGraph(m_FallHandle);
	my::MyDeleteGraph(m_DeadHandle);
}

void Kinnikurou::Update()
{
	m_stiffen--;
	if (m_hp > 0)
	{
		// ノックバック
		UpdateKnockBack();
		// モーションのカウントダウン
		MotionCountDown();

		if (m_motionCount == 0 && !m_charRun)
		{
			m_moveType = 0;
		}

		if (m_moveType == 0)
		{
			if (m_initCount <= 0)
			{
				ImgposInit();
				m_initCount++;
			}
		}
		// ジャンプ更新処理
		if (m_motionCount == 0)
		{
			m_pJump->Update(m_jumpAcc, m_pos.y, m_padNum);

		}
		// ジャンプしている間の挙動
		if (m_pJump->IsJump())
		{
			m_moveType = static_cast<int>(moveType::Jump);
			if (Pad::IsPress(PAD_INPUT_RIGHT, m_padNum))
			{
				m_pos.x += 10;
				m_charDirection = false;
				m_charRun = true;
			}
			if (Pad::IsPress(PAD_INPUT_LEFT, m_padNum))
			{
				m_pos.x -= 10;
				m_charDirection = true;
				m_charRun = true;
			}
		}
		// ジャンプしていないときの処理
		else
		{
			// 攻撃していないとき
			if (m_motionCount == 0)
			{
				// 走る
				UpdateRun();
				// 攻撃
				UpdateAttack();
			}
		}

		// 硬直固定
		if (m_stiffen <= 0)
		{
			m_stiffen = 0;
		}

		if (!Pad::IsPress(PAD_INPUT_RIGHT, m_padNum) || !Pad::IsPress(PAD_INPUT_LEFT, m_padNum))
		{
			m_charRun = false;
		}

		if ((Pad::IsRelase(PAD_INPUT_RIGHT, m_padNum) || Pad::IsRelase(PAD_INPUT_LEFT, m_padNum)) && m_motionCount == 0)
		{
			ImgposInit();
		}


		// アイドル状態
		if (m_moveType == static_cast<int>(moveType::Idol))
		{
			m_pIdle->Update(m_imgPosX, m_imgPosY);
		}
		// ジャブ攻撃
		if (m_moveType == static_cast<int>(moveType::Attack1))
		{
			if (!m_charDirection)
			{
				// 当たり判定
				CollisionSize(30, -30, 90, 10);
			}
			else if (m_charDirection)
			{
				// 当たり判定
				CollisionSize(-90, -30, -30, 10);
			}

			m_pJab->Update(m_imgPosX, m_imgPosY);
		}
		// 胸筋衝撃波
		if (m_moveType == static_cast<int>(moveType::Attack2))
		{
			if (!m_charDirection)
			{
				// 当たり判定
				CollisionSize(-50, -90, 100, 90);
			}
			else if (m_charDirection)
			{
				CollisionSize(-100, -90, 50, 90);
			}


			m_pMuscle->Update(m_imgPosX, m_imgPosY);
		}
		// アッパー攻撃
		if (m_moveType == static_cast<int>(moveType::Attack3))
		{
			if (!m_charDirection)
			{
				// 当たり判定
				CollisionSize(30, -80, 100, 80);
			}
			else if (m_charDirection)
			{
				CollisionSize(-100, -80, -30, 80);
			}

			m_pUpper->Update(m_imgPosX, m_imgPosY);
		}
		// みぞおち攻撃
		if (m_moveType == static_cast<int>(moveType::Attack4))
		{
			if (!m_charDirection)
			{
				// 当たり判定
				CollisionSize(30, -10, 80, 10);
			}
			else if (m_charDirection)
			{
				CollisionSize(-80, -10, -30, 10);
			}

			m_pMizo->Update(m_imgPosX, m_imgPosY, m_testCount);
		}
		// 走る状態
		if (m_moveType == static_cast<int>(moveType::Run))
		{
			m_pRun->Update(m_imgPosX, m_imgPosY);
		}
	}
	else
	{
		// 死んだときの処理
		m_moveType = static_cast<int>(moveType::Dead);
		m_pDead->Update(m_imgPosX, m_imgPosY);
	}
}

void Kinnikurou::Draw()
{
	if (!m_isSpawn)
	{
		CharDefaultPos(m_charDirection);
		m_isSpawn = true;
	}

	// アイドル状態
	if (m_moveType == static_cast<int>(moveType::Idol))
	{
		HandleAssignment(m_idleHandle, 18, 23);
	}
	// ジャブ攻撃状態
	else if (m_moveType == static_cast<int>(moveType::Attack1))
	{
		HandleAssignment(m_jabHandle, 56 / 2, 23);
	}
	// マッスル攻撃状態
	else if (m_moveType == static_cast<int>(moveType::Attack2))
	{
		HandleAssignment(m_muscleHandle, 27, 24);
	}
	// アッパー攻撃状態
	else if (m_moveType == static_cast<int>(moveType::Attack3))
	{
		HandleAssignment(m_UpperHandle, 27, 24);
	}
	// みぞおち攻撃状態
	else if (m_moveType == static_cast<int>(moveType::Attack4))
	{
		HandleAssignment(m_MizoHandle, 27, 24);
	}
	// 移動状態
	else if (m_moveType == static_cast<int>(moveType::Run))
	{
		HandleAssignment(m_RunHandle, 54 / 3, 72 / 3);
	}
	else if (m_moveType == static_cast<int>(moveType::Jump))
	{
		if (m_pJump->IsFall())
		{
			HandleAssignment(m_FallHandle, 24, 22);
		}
		else
		{
			HandleAssignment(m_JumpHandle, 19, 21);
		}
		
		ImgposInit();
	}
	else if (m_moveType == static_cast<int>(moveType::Dead))
	{
		HandleAssignment(m_DeadHandle, 90 / 3, 96 / 3);
	}

	// キャラクターの描画
	my::MyDrawRectRotaGraph(static_cast<int> (m_pos.x), static_cast<int> (m_pos.y),
		m_imgPosX * m_imgWidth, m_imgPosY * m_imgHeight,
		m_imgWidth, m_imgHeight,
		5.0f * m_sizeUp, 0.0f,
		m_charHandle,
		true, m_charDirection);

	AttackCol();

}

void Kinnikurou::ImgposInit()
{
	m_imgPosX = 0;
	m_imgPosY = 0;
	m_testCount = 0;
}

void Kinnikurou::AttackCol()
{
	bool isAttack = m_pJab->IsAttackColJab() || 
					m_pMuscle->IsAttackColMuscle() || 
					m_pUpper->IsAttackColUpper() || 
					m_pMizo->IsAttackColMizo();
	// 攻撃判定のタイミング
	if (isAttack)
	{
		m_attackFlag = true;
	}
	else
	{
		m_attackFlag = false;
	}

	if (m_attackFlag)
	{
		if (m_moveType == static_cast<int>(moveType::Attack1))
		{
			m_damage = 1;
			Sound::play(Sound::KinnikuAttack1);
		}
		if (m_moveType == static_cast<int>(moveType::Attack2))
		{
			m_damage = 20;
			Sound::play(Sound::KinnikuAttack2);
		}
		if (m_moveType == static_cast<int>(moveType::Attack3))
		{
			m_damage = 2;
			Sound::play(Sound::KinnikuAttack3);
		}
		if (m_moveType == static_cast<int>(moveType::Attack4))
		{
			m_damage = 30;
			Sound::play(Sound::KinnikuAttack4);
		}
	}
	else
	{
		m_damage = 0;
	}
}

void Kinnikurou::InitAttackFlag()
{
	m_pJab->m_isAttackCol = false;
	m_pMuscle->m_isAttackCol = false;
	m_pUpper->m_isAttackCol = false;
	m_pMizo->m_isAttackCol = false;
}

void Kinnikurou::UpdateKnockBack()
{
	// ノックバック
	KnockBack();
	// ノックバックしているときの処理
	if (m_onDamageFrame > 0)
	{
		ImgposInit();
		m_moveType = static_cast<int>(moveType::Idol);
		m_motionCount = 0;
		InitAttackFlag();
		m_jumpAcc = 0;
	}
}

void Kinnikurou::MotionCountDown()
{
	// モーションのカウントダウン
	if (m_motionCount != 0)
	{
		m_motionCount--;
		if (m_motionCount <= 0) m_motionCount = 0;
	}
}

void Kinnikurou::UpdateRun()
{
	if (Pad::IsPress(PAD_INPUT_RIGHT, m_padNum))
	{
		m_moveType = static_cast<int>(moveType::Run);
		m_pos.x += 10;
		m_charDirection = false;
		m_charRun = true;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT, m_padNum))
	{
		m_moveType = static_cast<int>(moveType::Run);
		m_pos.x -= 10;
		m_charDirection = true;
		m_charRun = true;
	}
}

void Kinnikurou::UpdateAttack()
{
	if (m_stiffen <= 0)
	{
		if (Pad::IsTrigger(PAD_INPUT_1, m_padNum))
		{
			m_moveType = static_cast<int>(moveType::Attack1);// ジャブ攻撃状態
			ImgposInit();
			m_motionCount = 3 * 3;
			m_stiffen = 15;
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_2, m_padNum))
	{
		m_moveType = static_cast<int>(moveType::Attack2);// マッスル攻撃状態
		ImgposInit();
		m_motionCount = 2 * 3 + 15 * 3 + 1;
	}
	if (Pad::IsTrigger(PAD_INPUT_3, m_padNum))
	{
		m_moveType = static_cast<int>(moveType::Attack3);// アッパー攻撃状態
		ImgposInit();
		m_motionCount = 5 * 4;
	}
	if (Pad::IsTrigger(PAD_INPUT_4, m_padNum))
	{
		m_moveType = static_cast<int>(moveType::Attack4);// みぞおち攻撃状態
		ImgposInit();
		m_motionCount = 70 + 2 * 2 + 40 -1;
	}
}

void Kinnikurou::CollisionSize(int left, int top, int right, int bottom)
{
	m_attackSizeLeft = left;
	m_attackSizeTop = top;
	m_attackSizeRight = right;
	m_attackSizeBottom = bottom;
}

void Kinnikurou::HandleAssignment(int handle, int width, int height)
{
	m_charHandle = handle;
	m_imgWidth = width;
	m_imgHeight = height;
}
