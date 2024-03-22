#include "DinosaurAttackPounce.h"
#include "DinosaurIdle.h"
#include"../.././Util/Sound.h"

namespace
{
	constexpr float kJumpPower = -15.0f;

	constexpr float kGravity = 1.25f;

	constexpr float kMoveSpeed = 12.0f;

	constexpr int kAttackFlagOn = 20;//攻撃フラグがOnになるタイミング
}

DinosaurAttackPounce::DinosaurAttackPounce(Vec2 vec, bool lookLeft)
{
	m_vec = vec;
	m_imagePosX = 0;//画像の番号X座標
	m_imagePosY = 4;//画像の番号Y座標
	m_vec.y = kJumpPower; //ジャンプ力

	//攻撃範囲
	m_attakSizeLeft = -130;
	m_attackSizeTop = 10;
	m_attackSizeRight = 0;
	m_attackSizeBottom = 80;
	
	m_attackMotion = true;

	//攻撃力
	m_attackDamage = 10;

	//攻撃中に進む方向を教える
	if (lookLeft)
	{
		m_vec.x = -kMoveSpeed;
	}
	else
	{
		m_vec.x = kMoveSpeed;
	}

	Sound::play(Sound::DinoAttack2);
}

DinosaurAttackPounce::~DinosaurAttackPounce()
{
}

DinosaurStateBase* DinosaurAttackPounce::Update(int padNum)
{
	m_attackFrame++;

	if (m_attackFrame == kAttackFlagOn)
	{
		m_attackFlag = true;
	}

	if (m_imagePosX < 3)
	{
		ChangeGraph(6, 6, false);
	}
	else
	{
		/*if (m_gapTime == 0)
		{
			m_attackFlag = true;
		}*/
		m_imagePosY = 5;

		m_imagePosX = 7 + (m_gapTime / 5);
		m_gapTime++;
	}

	if (m_vec.y < -kJumpPower)
	{
		/*m_Vec.y += m_JumpPower;*/
		m_vec.y += kGravity;
	}
	
	if (m_gapTime > 3)
	{
		m_vec.x = 0;
	}

	if (m_gapTime > 15)
	{
		return new DinosaurIdle({0,0});
	}

	return this;
}
