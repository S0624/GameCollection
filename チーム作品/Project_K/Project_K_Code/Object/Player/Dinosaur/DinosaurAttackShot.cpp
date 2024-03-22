#include "DinosaurAttackShot.h"
#include "DinosaurIdle.h"

namespace
{
	constexpr int kImageNum = 5;

	constexpr int k = 5;
}

DinosaurAttackShot::~DinosaurAttackShot()
{
}

DinosaurStateBase* DinosaurAttackShot::Update(int padNum)
{
	if (m_imagePosX < kImageNum)
	{
		ChangeGraph(8, 6, false);
	}
	else
	{
		m_imagePosX = kImageNum;
		m_gapTime++;
	}

	if (m_pastShotFlag)
	{
		m_shotFlag = false;
	}

	if (m_imagePosX == 3 && !m_pastShotFlag)
	{
		m_pastShotFlag = true;
		m_shotFlag = true;
	}

	if (m_gapTime > 15)
	{
		return new DinosaurIdle(m_vec);
	}

	return this;
}
