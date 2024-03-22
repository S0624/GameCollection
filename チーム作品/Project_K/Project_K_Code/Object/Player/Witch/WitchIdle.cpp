#include "WitchIdle.h"

WitchIdle::WitchIdle() :
	m_animeWidth(0),
	m_animeHight(0),
	m_animeMax(0)
{
}

void WitchIdle::Init()
{
	m_animeHight = 0;
	m_animeWidth = 0;
	m_animeMax = 8;
}