#include "KinnikuUpper.h"

void KinnikuUpper::Update(int& imagePosX, int& imagePosY)
{
	m_isAttackCol = false;
	m_frameCount++;
	if (m_frameCount >= 5)
	{
		imagePosX++;
		m_frameCount = 0;

	}
	if (imagePosX >= 4)
	{
		imagePosX = 0;
	}
	if (imagePosX == 2 && imagePosY == 0)
	{
		m_isAttackCol = true;
	}
}
