#pragma once
#include "DinosaurStateBase.h"
#include"../.././Util/Sound.h"

class DinosaurAttackShot : public DinosaurStateBase
{
public:
	DinosaurAttackShot(Vec2 vec) : 
		m_pastShotFlag(false)
	{
		m_vec = vec;
		m_imagePosX = 0;
		m_imagePosY = 2;

		m_attackFlag = false;

		// ショットの処理だから攻撃の当たり判定は実際はないため
		// 絶対に当たらない値にした
		m_attakSizeLeft = -10000;
		m_attackSizeTop = -10000;
		m_attackSizeRight = -10000;
		m_attackSizeBottom = -10000;
		m_attackMotion = false;

		Sound::play(Sound::DinoAttack4);
	}
	virtual ~DinosaurAttackShot();

	virtual DinosaurStateBase* Update(int padNum) override;

private:
	bool m_pastShotFlag;
};

