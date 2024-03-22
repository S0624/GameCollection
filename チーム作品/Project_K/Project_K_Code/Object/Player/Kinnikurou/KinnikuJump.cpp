#include "KinnikuJump.h"

namespace
{
	// 重力
	constexpr float kGravity = 0.5f;
	// ジャンプ力
	constexpr float kJumpPower = 24.0f;
}

KinnikuJump::KinnikuJump() :
	m_isJumping(true),
	m_isFalling(false)
{
}

KinnikuJump::~KinnikuJump()
{
}

void KinnikuJump::Update(float& jumpAcc, float& posY,int padNum)
{
	m_isJumping = true;
	m_isFalling = false;
	jumpAcc += kGravity;// 重力
	posY += jumpAcc;// ジャンプ力
	if (posY >= 600.0f)
	{
		posY = 600.0f;
		jumpAcc = 0.0f;
		m_isJumping = false;
	}
	// ジャンプしていないとき
	if (!m_isJumping)
	{
		if (Pad::IsTrigger(PAD_INPUT_UP, padNum))
		{
			jumpAcc = -kJumpPower;
		}
	}

	if (jumpAcc >= 0)
	{
		m_isFalling = true;
	}
}

bool KinnikuJump::IsJump()
{
	return m_isJumping;
}

bool KinnikuJump::IsFall()
{
	return m_isFalling;
}

