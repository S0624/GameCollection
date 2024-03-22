#include "DinosaurJump.h"
#include"DinosaurIdle.h"

namespace
{
	constexpr float kJumpPower = -20.0f;

	constexpr float kGravity = 0.8f;
}

DinosaurJump::DinosaurJump(Vec2 vec)
{	
	m_vec.x = vec.x;
	m_imagePosX = 0;
	m_imagePosY = 4;
	m_vec.y = kJumpPower;
	m_attackFlag = false;
	m_attackMotion = true;
}

DinosaurJump::~DinosaurJump()
{
}

DinosaurStateBase* DinosaurJump::Update(int padNum)
{
	m_vec.y += kGravity;

	if (m_imagePosX < 3)
	{
		ChangeGraph(8, 6, false);
	}
	else
	{
		m_imagePosX = 3;
		m_gapTime++;
	}

	if (m_vec.y > -kJumpPower)
	{
		m_vec.y = 0;
		return new DinosaurIdle(m_vec);
	}

	return this;
}
