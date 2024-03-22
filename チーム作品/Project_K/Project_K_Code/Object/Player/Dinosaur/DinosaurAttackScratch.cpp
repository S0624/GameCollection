#include "DinosaurAttackScratch.h"
#include "DinosaurIdle.h"

namespace
{
	constexpr int kAttackFlagOn = 3;//攻撃フラグがOnになるタイミング

	constexpr int kAttackFlagOff = 10;//攻撃フラグがOffになるタイミング
}

DinosaurAttackScratch::~DinosaurAttackScratch()
{
}

DinosaurStateBase* DinosaurAttackScratch::Update(int padNum)
{
	m_attackFrame++;

	if (m_attackFrame == kAttackFlagOn)
	{
		m_attackFlag = true;
	}

	if (m_attackFrame == kAttackFlagOff)
	{
		m_attackFlag = false;
	}
	if (m_imagePosX < 7)
	{
		ChangeGraph(4, 10, false);
	}
	else
	{
		m_imagePosX = 7;
		m_gapTime++;
	}

	if (m_gapTime > 5)
	{
		return new DinosaurIdle(m_vec);
	}
	return this;
}
