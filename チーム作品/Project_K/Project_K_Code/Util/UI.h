#pragma once
#include"Vec2.h"
class PlayerBase;

class UI
{
public:
	UI(int Hp1, int Hp2, PlayerBase* player1P, PlayerBase* player2P);
	virtual ~UI();

	void Init() {}// 初期化
	void Update();// 更新処理
	void Draw();// 描画処理

	void HpUpdate();
	void HpDraw();

	void FontUpdate();
	void FontDraw();

	void GetHp1(int hp) { m_ui1.m_temp = hp; }// 1PのHP
	void GetHp2(int hp) { m_ui2.m_temp = hp; }// 2PのHP
	void AttackFlag1(bool flag) { m_ui1.m_attackFlag = flag; }
	void AttackFlag2(bool flag) { m_ui2.m_attackFlag = flag; }


	void DrawPlayerCursor(Vec2 playerPos1,Vec2 playerPos2); //プレイヤーのカーソル表示

	int GetTime()const { return m_time; }


private:

	Vec2 m_boxPos;
	// ポインタ
	PlayerBase* m_pPlayer[2];// プレイヤーベース
	struct  UIData
	{
		Vec2 m_pos = { 0,0 };// HPバーの位置
		int m_temp = 0;// HPをうけとる用の変数
		int m_life = 0;// 各プレイヤーのHP
		int m_lower = 0;// 仮で保存するHP用の変数
		int m_countFrame = 0;// 仮のHPを減らすタイマー
		bool m_attackFlag = false;// 攻撃中かどうかを調べる
	};

	int m_font = 0;// フォント
	UIData m_ui1;// 1P
	UIData m_ui2;// 2P

	int m_timeCount;// 時間カウント用
	int m_time;// 表示用時間
	const char* m_letter;// 文字

	int playerCursorHandle1 = -1; //プレイヤーのカーソルハンドル
	int playerCursorHandle2 = -1; //プレイヤーのカーソルハンドル
};
