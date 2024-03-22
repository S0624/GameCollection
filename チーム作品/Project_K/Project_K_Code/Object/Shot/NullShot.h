#pragma once
#include "ShotBase.h"
class NullShot : public ShotBase
{
public:
	NullShot()
	{
		m_Exist = false;
		m_NullShot = true;
	}

	virtual ~NullShot() {};

	virtual void Update() {};

	virtual void Draw() {};
};

