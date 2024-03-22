#pragma once
#include "../Base/MoveTypeBase.h"
#include "../../Util/common.h"

class KinnikuJump : public MoveTypeBase
{
public:
	KinnikuJump();
	virtual ~KinnikuJump();

	void Update(float& jumpAcc, float& posY, int padNum);

	bool IsJump();
	bool IsFall();
private:
	bool m_isJumping;
	bool m_isFalling;
};

