#pragma once
#include "DinosaurStateBase.h"
class DinosaurAttackPounce : public DinosaurStateBase
{
public:
	DinosaurAttackPounce(Vec2 vec, bool lookLeft);
	
	virtual ~DinosaurAttackPounce();

	virtual DinosaurStateBase* Update(int padNum) override;
};

