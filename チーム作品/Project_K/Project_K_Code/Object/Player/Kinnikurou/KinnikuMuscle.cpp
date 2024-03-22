#include "KinnikuMuscle.h"
#include "DxLib.h"

void KinnikuMuscle::Update(int& imagePosX, int& imagePosY)
{


	m_isAttackCol = false;
	m_frameCount++;

	// ƒtƒŒ[ƒ€ˆ—
	if (imagePosX >= 0 && imagePosY >= 1)
	{
		m_nextCount = 15;
	}
	else if(imagePosX == 3 && imagePosY == 0)
	{
		m_nextCount = 1;
	}
	else
	{
		m_nextCount = 2;
	}

	if (m_frameCount >= m_nextCount)
	{
		imagePosX++;
		m_frameCount = 0;

	}
	if (imagePosX >= 4)
	{
		imagePosX = 0;
		imagePosY++;
	}
	if (imagePosX >= 3 && imagePosY >= 1)
	{
		imagePosX = 0;
		imagePosY = 0;
	}
	if (imagePosX == 3 && imagePosY == 0)
	{
		m_isAttackCol = true;
	}
}
