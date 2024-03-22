#include "KinnikuIdle.h"

void KinnikuIdle::Update(int& imagePosX, int& imagePosY)
{
	m_frameCount++;
	if (m_frameCount == 50)
	{
		imagePosX++;
		m_frameCount = 0;
	}
	if (imagePosX >= 2)
	{
		imagePosX = 0;
	}
}
