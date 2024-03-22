#pragma once
#include "DinosaurStateBase.h"
class DinosaurJump : public DinosaurStateBase
{
public:
	DinosaurJump(Vec2 vec);
	
	virtual ~DinosaurJump();

	virtual DinosaurStateBase* Update(int padNum) override;
};

