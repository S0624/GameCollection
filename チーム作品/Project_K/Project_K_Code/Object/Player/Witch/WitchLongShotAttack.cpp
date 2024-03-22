#include "WitchLongShotAttack.h"

namespace
{
	int kShift = -100;
}

WitchLongShotAttack::WitchLongShotAttack() :
	m_animeWidth(0),
	m_reversal(false),
	m_animeHight(0),
	m_indexX(0),
	m_shiftX(0),
	m_animeMax(0)
{

}

void WitchLongShotAttack::Init()
{
	m_indexX = 3;
	m_animeWidth = 6;
	m_animeHight = 0;
	m_animeMax = 9;
}

void WitchLongShotAttack::Update()
{
	m_shiftX = kShift;
}
