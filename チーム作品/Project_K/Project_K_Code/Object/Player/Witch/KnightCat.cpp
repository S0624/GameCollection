#include "KnightCat.h"
#include "../../Util/DrawFunctions.h"
#include"../../Util/Sound.h"

namespace
{
	const char* const kFilmName = "Data/Image/Player/Witch/Nekochan.png";
}
KnightCat::KnightCat() :
	m_handle(0),
	m_reversal(false),
	m_pos(0,0),
	m_movePos(20),
	m_animeFrame(0),
	m_animeMax(0),
	m_animeWidth(0),
	m_animeHight(0),
	m_exist(false),
	m_timeCount(0)
{

}

KnightCat::~KnightCat()
{
	my::MyDeleteGraph(m_handle);
}

void KnightCat::Init()
{
	m_animeWidth = 2;
	m_animeHight = 0;
	m_animeMax = 4;
	m_handle = my::MyLoadGraph(kFilmName);
}

void KnightCat::Update()
{
	if (m_exist)
	{
	// SE ループ
	Sound::loopBgm(Sound::WitchAttack4);// SEをならす
		if (m_reversal)
		{
			m_movePos = -50;
		}
		else
		{
			m_movePos = 20;
		}
		m_animeFrame++;
		m_timeCount++;
		if (m_animeFrame > 10)
		{
			m_animeHight++;
			m_animeFrame = 0;
		}
		if (m_animeHight >= m_animeMax)
		{
			m_animeHight = 0;
		}
		if (m_timeCount > 60 * 3)
		{
			m_exist = false;
			m_timeCount = 0;
		}
	}
}

void KnightCat::Draw(int sizeup)
{
	if (m_exist)
	{
		my::MyDrawRectRotaGraph(static_cast<int>(m_pos.x) + static_cast<int>(m_movePos),
			static_cast<int>(m_pos.y),			//表示座標
			32 * m_animeWidth, 32 * m_animeHight,			//切り取り左上
			32, 32,							//幅、高さ
			3.0f * sizeup, 0.0f,						//拡大率、回転角度
			m_handle, true, m_reversal);
	}
}