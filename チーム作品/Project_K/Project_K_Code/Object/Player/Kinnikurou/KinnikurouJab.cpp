#include "KinnikurouJab.h"

void KinnikurouJab::Update(int& imagePosX, int& imagePosY)
{
	m_isAttackCol = false;
	m_frameCount++;
	if (m_frameCount >= 3)
	{
		imagePosX++;
		m_frameCount = 0;

	}
	if (imagePosX >= 2)
	{
		imagePosX = 0;
		imagePosY++;
	}
	if (imagePosX >= 1 && imagePosY >= 1)
	{
		imagePosX = 0;
		imagePosY = 0;
	}
	if (imagePosX == 1 && imagePosY == 0)
	{
		m_isAttackCol = true;
	}
}
