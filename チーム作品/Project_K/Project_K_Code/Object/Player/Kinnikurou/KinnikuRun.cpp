#include "KinnikuRun.h"

void KinnikuRun::Update(int& imagePosX, int& imagePosY)
{
	m_frameCount++;
	if (m_frameCount == 5)
	{
		imagePosX++;
		m_frameCount = 0;

	}
	if (imagePosX >= 3)
	{
		imagePosX = 0;
		imagePosY++;
	}
	if (imagePosX >= 2 && imagePosY >= 2)
	{
		imagePosX = 0;
		imagePosY = 0;
	}
}
