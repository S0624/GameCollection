#pragma once

#include "../Base/MoveTypeBase.h"

class ElfJump : public MoveTypeBase
{
public:
	ElfJump();
	virtual ~ElfJump() {}

	void Update();// XV
	float Gravity();
private:
	float m_jumpAcc;
};

