#include "UI.h"
#include "DxLib.h"
#include "../Object/Player/Dinosaur/Dinosaur.h"
#include "../Object/Player/Elf/Elf.h"
#include "../Object/Player/Kinnikurou/Kinnikurou.h"
#include "../Object/Player/Witch/Witch.h"
#include"game.h"

namespace
{
	const int kWidthGauge = 100;
	const int kHightGauge = 40;
	const int kTimeBoxSize = 50;// 時間を表示する場所のボックスのサイズ
	const int kCenter = Game::kScreenWidth / 2;// 真ん中の位置
	const char* kFont = "HGP行書体";
	int kTextFont = 0;

	const char* kPlayerCursorHandle1 = "Data/Image/UI/1P.png";
	const char* kPlayerCursorHandle2 = "Data/Image/UI/2P.png";
}

UI::UI(int Hp1, int Hp2, PlayerBase* player1P, PlayerBase* player2P) :
	m_boxPos(kCenter, 90),	// 時間を表示するボックスの初期化
	m_timeCount(99 * 60),// 時間を図るタイマー
	m_time(0),// 表示する時間
	m_letter("%d")// 文字
{
	m_pPlayer[0] = nullptr;
	m_pPlayer[1] = nullptr;
	m_pPlayer[0] = player1P;
	m_pPlayer[1] = player2P;

	m_font = CreateFontToHandle(kFont, 70, -1, -1);// 使用するフォント、サイズ
	kTextFont = CreateFontToHandle(kFont, 40, -1, -1);// 使用するフォント、サイズ
	// 1Pの初期化
	m_ui1.m_pos = { m_boxPos.x - kTimeBoxSize,80 };
	m_ui1.m_temp = Hp1;
	m_ui1.m_life = m_ui1.m_temp;
	m_ui1.m_lower = m_ui1.m_life;
	m_ui1.m_countFrame = 50;// タイマーの初期化
	m_ui1.m_attackFlag = false;// 攻撃中かしるためのフラグ
	// 2Pの初期化
	m_ui2.m_pos = { m_boxPos.x + kTimeBoxSize,80 };
	m_ui2.m_temp = Hp2;
	m_ui2.m_life = m_ui2.m_temp;
	m_ui2.m_lower = m_ui2.m_life;
	m_ui2.m_countFrame = 50;// タイマーの初期化
	m_ui2.m_attackFlag = false;// 攻撃中かしるためのフラグ

	//ハンドルロード
	playerCursorHandle1 = LoadGraph(kPlayerCursorHandle1);
	playerCursorHandle2 = LoadGraph(kPlayerCursorHandle2);
}

UI::~UI()
{
	DeleteFontToHandle(m_font);
	DeleteFontToHandle(kTextFont);

	DeleteGraph(playerCursorHandle1);
	DeleteGraph(playerCursorHandle2);
}

void UI::Update()
{
	HpUpdate();
	FontUpdate();
}

void UI::Draw()
{
	HpDraw();
	FontDraw();

	m_pPlayer[0]->Draw();
}

void UI::HpUpdate()
{
	m_ui1.m_countFrame++;//タイマーのカウント
	m_ui2.m_countFrame++;//タイマーのカウント
	if (m_ui1.m_temp >= 0)
	{
		m_ui1.m_life--;// ゆっくり減らす
		if (m_ui1.m_life < m_ui1.m_temp)
		{
			m_ui1.m_life = m_ui1.m_temp;
		}
	}
	if (m_ui2.m_temp >= 0)
	{
		m_ui2.m_life--;// ゆっくり減らす
		if (m_ui2.m_life < m_ui2.m_temp)
		{
			m_ui2.m_life = m_ui2.m_temp;
		}
	}
	if (m_ui1.m_countFrame >= 40)
	{
		m_ui1.m_lower = m_ui1.m_life;// 仮のHPを今のHP似合わせる
		m_ui1.m_countFrame = 0;
	}

	if (m_ui2.m_countFrame >= 40)
	{
		m_ui2.m_lower = m_ui2.m_life;// 仮のHPを今のHP似合わせる
		m_ui2.m_countFrame = 0;
	}
	if (m_ui1.m_attackFlag)// 攻撃中だったらカウントを数えない
	{
		m_ui1.m_countFrame = 0;
	}
	if (m_ui2.m_attackFlag)// 攻撃中だったらカウントを数えない
	{
		m_ui2.m_countFrame = 0;
	}
	if (m_ui1.m_life <= 0)
	{
		m_ui1.m_lower = 0;
		m_ui1.m_life = 0;
	}
	if (m_ui2.m_life <= 0)
	{
		m_ui2.m_lower = 0;
		m_ui2.m_life = 0;
	}
}

void UI::HpDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);			// 見やすいようにちょっと黒フィルターをかけてる
	// 描画
	DrawBox(static_cast<int>(m_boxPos.x) - kTimeBoxSize, static_cast<int>(m_boxPos.y) - kTimeBoxSize,
		static_cast<int>(m_boxPos.x) + kTimeBoxSize, static_cast<int>(m_boxPos.y) + kTimeBoxSize,
		0x000000, true);
	DrawBox(static_cast<int>(m_ui1.m_pos.x), static_cast<int>(m_ui1.m_pos.y),
		static_cast<int>(m_ui1.m_pos.x) - (5 * 100), static_cast<int>(m_ui1.m_pos.y) + kHightGauge, 0x000000, true);
	DrawBox(static_cast<int>(m_ui2.m_pos.x), static_cast<int>(m_ui2.m_pos.y),
		static_cast<int>(m_ui2.m_pos.x) + (5 * 100), static_cast<int>(m_ui2.m_pos.y) + kHightGauge, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	//仮のHPの表示
	DrawBox(static_cast<int>(m_ui1.m_pos.x), static_cast<int>(m_ui1.m_pos.y),
		static_cast<int>(m_ui1.m_pos.x) - (5 * m_ui1.m_lower), static_cast<int>(m_ui1.m_pos.y) + kHightGauge, 0xff0000, true);
	DrawBox(static_cast<int>(m_ui2.m_pos.x), static_cast<int>(m_ui2.m_pos.y),
		static_cast<int>(m_ui2.m_pos.x) + (5 * m_ui2.m_lower), static_cast<int>(m_ui2.m_pos.y) + kHightGauge, 0xff0000, true);
	//現在HPの表示
	DrawBox(static_cast<int>(m_ui1.m_pos.x), static_cast<int>(m_ui1.m_pos.y),
		static_cast<int>(m_ui1.m_pos.x) - (5 * m_ui1.m_life), static_cast<int>(m_ui1.m_pos.y) + kHightGauge, 0x00ff00, true);
	DrawBox(static_cast<int>(m_ui2.m_pos.x), static_cast<int>(m_ui2.m_pos.y),
		static_cast<int>(m_ui2.m_pos.x) + (5 * m_ui2.m_life), static_cast<int>(m_ui2.m_pos.y) + kHightGauge, 0x00ff00, true);
	DrawBox(static_cast<int>(m_ui1.m_pos.x), static_cast<int>(m_ui1.m_pos.y),
		static_cast<int>(m_ui1.m_pos.x) - (5 * 100), static_cast<int>(m_ui1.m_pos.y) + kHightGauge, 0x000000, false);
	DrawBox(static_cast<int>(m_ui2.m_pos.x), static_cast<int>(m_ui2.m_pos.y),
		static_cast<int>(m_ui2.m_pos.x) + (5 * 100), static_cast<int>(m_ui2.m_pos.y) + kHightGauge, 0x000000, false);

	DrawBox(static_cast<int>(m_boxPos.x) - kTimeBoxSize, static_cast<int>(m_boxPos.y) - kTimeBoxSize,
		static_cast<int>(m_boxPos.x) + kTimeBoxSize, static_cast<int>(m_boxPos.y) + kTimeBoxSize, 0x000000, false);

	// HPの横にプレイヤーの表示
	DrawRectRotaGraph(static_cast<int>(m_ui1.m_pos.x - 500) + 20, 
		static_cast<int>(m_ui1.m_pos.y) - 25,
		0,0,
		100,50,
		1.0f,0.0f,
		playerCursorHandle1, true);
	DrawRectRotaGraph(static_cast<int>(m_ui2.m_pos.x + 500) + 5, 
		static_cast<int>(m_ui2.m_pos.y) - 25 ,
		0,0,
		100,50,
		1.0f,0.0f,
		playerCursorHandle2, true);
	
}

void UI::FontUpdate()
{
	// 時間を減らす
	m_timeCount--;
	if (m_timeCount < 0)
	{
		m_timeCount = 0;// 0よりちっちゃくならないように
	}
	if (m_time < 10)
	{
		m_letter = "0%d";// 一桁台になったら0を表示させる
	}
}

void UI::FontDraw()
{
	m_time = m_timeCount / 60;
	// 赤フォントの表示
	DrawFormatStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle(m_letter, 2, m_font)) / 2 + 5,
		100 - 35, 0x800000, m_font, m_letter, m_time);
	// 青フォントの表示
	DrawFormatStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle(m_letter, 2, m_font)) / 2,
		100 - 40, 0x7fffff, m_font, m_letter, m_time);
	
}


void UI::DrawPlayerCursor(Vec2 playerPos1, Vec2 playerPos2)
{
	DrawGraph(static_cast<int>(playerPos1.x) - 50, static_cast<int>(playerPos1.y) - 120,
		playerCursorHandle1, true);

	DrawGraph(static_cast<int>(playerPos2.x) - 50, static_cast<int>(playerPos2.y) - 120,
		playerCursorHandle2, true);
}
