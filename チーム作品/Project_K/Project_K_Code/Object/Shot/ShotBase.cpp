#include "ShotBase.h"
#include <DxLib.h>
//#include"game.h"
#include"../../Util/DrawFunctions.h"

void ShotBase::ChangeImage()
{
	m_changeSpeed++;

	if (m_changeSpeed = m_changeFrame)
	{
		m_changeSpeed = 0;

		m_imageNum++;

		if (m_imageNum >= m_imageMaxNum)
		{
			m_imageNum = 0;
		}
	}
}

ShotBase::ShotBase()
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	if (!IsExist())
	{
		m_Exist = false;
	}
}

void ShotBase::Draw()
{
	/*DrawCircle(static_cast<int>(m_Shot.Pos.x), static_cast<int>(m_Shot.Pos.y), 50,
		0xffffff, true);

	DrawBox(static_cast<int>(m_Shot.Pos.x) + m_Shot.shotSizeLeft, static_cast<int>(m_Shot.Pos.y) + m_Shot.shotSizeTop,
		static_cast<int>(m_Shot.Pos.x) + m_Shot.shotSizeRight, static_cast<int>(m_Shot.Pos.y) + m_Shot.shotSizeBottom,
		0xff0000, false);*/

	my::MyDrawRectRotaGraph(static_cast<int>(m_Shot.Pos.x), static_cast<int>(m_Shot.Pos.y),
		m_imageNum * static_cast<int>(m_imageSize.x), 0,
		static_cast<int>(m_imageSize.x),
			static_cast<int>(m_imageSize.y), m_imageScale, 0, m_handle, true, m_isTrans);
}


bool ShotBase::IsExist()
{
	// ‰æ–ÊŠO‚Éo‚½Žž‚Ìˆ—
	if (m_Shot.Pos.y > Game::kScreenHeight) return false;
	if (m_Shot.Pos.y < 0) return false;
	if (m_Shot.Pos.x > Game::kScreenWidth) return false;
	if (m_Shot.Pos.x < 0) return false;

	return true;
}
