#pragma once
#include "DinosaurStateBase.h"
#include"../.././Util/Sound.h"
class DinosaurAttackBite : public DinosaurStateBase
{
public:
	DinosaurAttackBite(Vec2 vec)
	{
		m_vec = vec;
		m_imagePosX = 0; //‰æ‘œ‚Ì”Ô†XÀ•W
		m_imagePosY = 5;//‰æ‘œ‚Ì”Ô†YÀ•W

		//UŒ‚”ÍˆÍ
		m_attakSizeLeft = -130;
		m_attackSizeTop = 0;
		m_attackSizeRight = 0;
		m_attackSizeBottom = 80;

		//UŒ‚—Í
		m_attackDamage = 8;

		m_attackMotion = true;

		Sound::play(Sound::DinoAttack1);
	}
	virtual ~DinosaurAttackBite();

	virtual DinosaurStateBase* Update(int padNum) override;
};

