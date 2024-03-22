#pragma once
#include "DinosaurStateBase.h"
class DinosaurDead : public DinosaurStateBase
{
public:
	DinosaurDead(Vec2 vec)
	{
		m_vec = vec;
		m_imagePosX = 0;
		m_imagePosY = 6;
		m_attackFlag = false;
	}
	virtual ~DinosaurDead();

	virtual DinosaurStateBase* Update(int padNum) override;
};

