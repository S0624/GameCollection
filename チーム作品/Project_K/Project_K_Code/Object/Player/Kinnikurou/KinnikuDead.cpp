#include "KinnikuDead.h"

void KinnikuDead::Update(int& imagePosX, int& imagePosY)
{
	m_frameCount++;
	if (m_frameCount == m_nextCount)
	{
		imagePosX++;
		m_frameCount = 0;
	}
	if (imagePosX >= 3)
	{
		imagePosY++;
		imagePosX = 0;
	}
	if (imagePosX >= 3 && imagePosY >= 3)
	{
		imagePosX = 2;
		imagePosY = 3;
	}
}
