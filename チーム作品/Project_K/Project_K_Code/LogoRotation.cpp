#include "LogoRotation.h"
#include "Util/Pad.h"
#include "Util/DrawFunctions.h"
#include "Util/game.h"

#include <DxLib.h>

LogoRotation::LogoRotation():
	m_hLogo  (-1),
	m_pos    (0.0, 0.0),
	m_logoPos(0.0, 0.0),
	m_x(0),
	m_y(0),
	width(0),
	height(0)
{
	m_pos.x = 500.0f;
	m_pos.y = 500.0f;

	m_logoPos.x = m_pos.x + 300.0f;
	m_logoPos.y = m_pos.y + 300.0f;

	m_isTrans = false;
}

LogoRotation::~LogoRotation()
{
	DeleteGraph(m_hLogo);
}

void LogoRotation::Init()
{
	m_hLogo = my::MyLoadGraph("Data/Image/Logo/TitleLogo.png");

	DxLib::GetGraphSize(m_hLogo , &m_x, &m_y);
}

void LogoRotation::Update()
{
	// 回転スピード
	const float transSpeed = 0.3f + 0.7f;
	// 回転
	m_pos.x     += transSpeed;
	m_logoPos.x -= transSpeed;
	
	

	if (m_pos.x == m_logoPos.x)
	{
		//printfDx("半分\n");
		m_pos.x = 500.0f/2.0f;
		
		m_logoPos.x = 500.0f + 300.0f/2.0f;
	}

	if (Pad::IsPress(PAD_INPUT_3, 1))
	{
		m_pos.x = 500.0f;
		m_pos.y = 500.0f;

		m_logoPos.x = m_pos.x + 300.0f;
		m_logoPos.y = m_pos.y + 300.0f;
		m_size = 0.0f;
		m_rota = 0.0f;
		m_box = 0;
		m_box2 = 0;

	}
	if (m_size < 0.5f)
	{
		m_size += 0.01f;
		m_rota += 0.12f;
	}
	else
	{
		int speed = 100;
		m_rota = 0.0f;
		m_box += speed;
		m_box2 += speed;
	}

	//printfDx("%d\n", m_x);

}

void LogoRotation::Draw()
{

	//my::MyDrawExtendGraph(500, 300,
	//				      500+m_x /2.5 , 300+m_y / 2.5,
	//				      m_hLogo, true);

	// 読みこんだグラフィックを回転描画
	DrawRotaGraph(Game::kScreenWidth/2, 500, m_size, m_rota, m_hLogo, true);

	constexpr int y = Game::kScreenHeight - 300;
	constexpr int x = 100; 

	int color = 0x000000;

	// コメント
	DrawBox(
		x,
		0,
		x + 100,
		m_box2,
		0xffff00, true);

	// コメント
	DrawBox(
		0, 
		y,
		m_box,
		y + 100,
		0xff0000, true);



//	my::MyDrawExtendGraph(m_pos.x, m_pos.y, m_logoPos.x, m_logoPos.y, m_hLogo, true);

//	DrawFormatString(m_pos.x, m_pos.y, 0x000000, "m_pos = %f",m_pos.x);
//	DrawFormatString(m_logoPos.x, m_logoPos.y, 0x000000, "m_logoPos = %f", m_logoPos.x);
}

inline int LogoRotation::test(int x)
{
	return x * (2 - 1);
}

int LogoRotation::test2(int x)
{
	return x;
}
