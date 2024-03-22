#include "Chicken.h"
#include"../../Util/game.h"
#include "../../Util/DrawFunctions.h"
#include"../../Util/Sound.h"
namespace
{
	const char* const kFilmName = "Data/Image/Player/Witch/Niwatori.png";
	constexpr int kCountFrame = 7;
}
Chicken::Chicken() :
	m_handle(0),
	m_movePos(0),
	m_reversal(false),
	m_move(0),
	m_pos(),
	m_animeFrame(0),
	m_animeMax(0),
	m_animeWidth(0),
	m_animeHight(0),
	m_exist(false),
	m_countFrame()
{

}

Chicken::~Chicken()
{
	my::MyDeleteGraph(m_handle);
}

void Chicken::Init()
{
	m_animeWidth = 1;
	m_animeHight = 0;
	m_animeMax = 10;
	m_handle = my::MyLoadGraph(kFilmName);
}

void Chicken::Update()
{
	if (m_exist)
	{
		Sound::loopBgm(Sound::WitchAttack3);// SEをならす
		m_animeFrame++;
		if (m_reversal && m_movePos == 40)
		{
			m_movePos *= -1;
		}
		if (m_animeFrame > 7)
		{
			m_animeHight++;
			m_move += m_movePos;
			m_animeFrame = 0;
			m_countFrame++;
		}
		if (m_animeHight >= m_animeMax)
		{
			m_animeHight = 0;
		}
		if (m_countFrame > kCountFrame)
		{
			m_exist = false;
			m_countFrame = 0;
		}
		if (m_pos.x >= Game::kScreenWidth || m_pos.x <= 0)
		{
			m_exist = false;
		}
	}
	else
	{
		m_movePos = 40;
		m_move = 0;
	}
}

void Chicken::Draw(int sizeup)
{
	if (m_exist)
	{
		my::MyDrawRectRotaGraph(static_cast<int>(m_pos.x) + static_cast<int>(m_move),
			static_cast<int>(m_pos.y),			//表示座標
			32 * m_animeWidth, 32 * m_animeHight,			//切り取り左上
			32, 32,							//幅、高さ
			3.0f * sizeup, 0.0f,						//拡大率、回転角度
			m_handle, true, m_reversal);
	}
}