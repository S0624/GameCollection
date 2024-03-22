#include "KinnikuMizo.h"

void KinnikuMizo::Update(int& imagePosX, int& imagePosY, int& framecount)
{
	m_isAttackCol = false;
	framecount++;

	if (imagePosX == 0 && imagePosY == 0)
	{
		m_nextCount = 70;
	}
	else if (imagePosX == 3 && imagePosY == 0)
	{
		m_nextCount = 40;
	}
	else if(imagePosX == 2 && imagePosY == 0)
	{
		m_nextCount = 1;
	}
	else
	{
		m_nextCount = 2;
	}

	if (framecount >= m_nextCount)
	{
		imagePosX++;
		framecount = 0;

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
