#pragma once

#include "ShotBase.h"

class ElfShot : public ShotBase
{
public:
	ElfShot(Vec2 Pos, Vec2 Vec)
	{
		m_Shot.Pos = Pos;
		m_Shot.Vec = Vec;

		m_Shot.shotSizeLeft   = -20;
		m_Shot.shotSizeTop    = -20;
		m_Shot.shotSizeRight  =  60;
		m_Shot.shotSizeBottom =  20;

		m_Exist = true;
		m_NullShot = false;
		m_isTrans = false;

		m_imageMaxNum = 5;
		m_imageScale = 3;
		m_imageSize = { 288.0f ,128.0f };
	}
	virtual ~ElfShot();

	virtual void Update() override;
};
