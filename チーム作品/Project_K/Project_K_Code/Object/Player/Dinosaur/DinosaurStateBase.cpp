#include "DinosaurStateBase.h"
#include"DxLib.h"
#include "../../../Util/DrawFunctions.h"

namespace
{
	constexpr int kGraphSizeX = 640;
	constexpr int kGraphSizeY = 640;
}

void DinosaurStateBase::Init(int Handle)
{
	m_handle = Handle;
}

void DinosaurStateBase::Draw(int handle , bool lookRight, Vec2 pos,int size)
{
	my::MyDrawRectRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 640 * m_imagePosX, 220 * m_imagePosY,
		640, 220, 1 * size, 0, handle, true, lookRight);
}

void DinosaurStateBase::ChangeGraph(int ChangeSpeed, int GraphNum, bool ChangeY)
{
	m_frameCount++;

	if (m_frameCount > ChangeSpeed)
	{
		m_frameCount = 0;
		m_imagePosX++;

		if (m_imagePosX >= GraphNum)
		{
			m_imagePosX = 0;

			if (ChangeY)
			{
				if (m_imagePosY == 0)
				{
					m_imagePosY = 1;
					return;
				}

				if (m_imagePosY == 1)
				{
					m_imagePosY = 0;
					return;
				}
			}
		}
	}
}