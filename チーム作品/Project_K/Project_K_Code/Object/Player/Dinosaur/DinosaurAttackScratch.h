#pragma once
#include "DinosaurStateBase.h"
#include"../.././Util/Sound.h"

class DinosaurAttackScratch : public DinosaurStateBase
{
public:
	DinosaurAttackScratch(Vec2 vec)
	{
		m_vec = vec;
		m_imagePosX = 4; //‰æ‘œ‚Ì”Ô†XÀ•W
		m_imagePosY = 8;//‰æ‘œ‚Ì”Ô†YÀ•W

		//UŒ‚”ÍˆÍ
		m_attakSizeLeft = -100;
		m_attackSizeTop = 30;
		m_attackSizeRight = 0;
		m_attackSizeBottom = 100;

		//UŒ‚—Í
		m_attackDamage = 6;

		//UŒ‚‚ª”­¶‚·‚é‚Ü‚Å‚ÌŠÔ
		m_attackFrame = 0;
		m_attackMotion = true;

		Sound::play(Sound::DinoAttack3);

	}
	virtual ~DinosaurAttackScratch();

	virtual DinosaurStateBase* Update(int padNum) override;
};

