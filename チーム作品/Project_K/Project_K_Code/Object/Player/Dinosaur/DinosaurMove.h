#pragma once
#include "DinosaurStateBase.h"
class DinosaurMove : public DinosaurStateBase
{
public:
	DinosaurMove(Vec2 vec)
	{
		m_vec = vec;
		m_imagePosY = 7;
		m_attackFlag = false;
		m_attackMotion = false;
	}
	virtual ~DinosaurMove();

	void IsMove(int padNum);

	virtual DinosaurStateBase* Update(int padNum) override;
};

