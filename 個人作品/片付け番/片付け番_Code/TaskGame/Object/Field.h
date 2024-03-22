#pragma once
#include"../UI/Vec2.h"
#include<stack>

class FieldInformation;

class Field
{
public:
	//盤面のサイズ
	static constexpr int kSize = 48;					//横
	static constexpr int kFieldX = 20;					//横
	static constexpr int kFieldY = 12;					//縦
	static constexpr int kWidth = kSize * 5;			//横幅
	static constexpr int kHeight = kSize * 3;			//高さ

private:
	// 現在の盤面データ
	int m_field[kFieldY][kFieldX];
	int m_handle;
	int m_groundHandle;			//空の時の画像
	int m_boxHandle;			//箱の画像
	int m_wallHandle;			//壁の画像
	int m_pinHandle;			//置き場所の画像
	int m_indexSize = 0;
	float m_index = 0.0;
	int m_shift = 0;

	int m_storageNum;			//箱を置くべき場所の残り
	bool m_drawFlag;			//移動中の箱を表示するかどうかのフラグ
	float m_boxMoveSpeed;		//箱の移動スピード
	Vec2 m_pos;					//現在の箱の位置
	Vec2 m_boxNextPos;			//次の箱の場所の位置
	int m_boxType;				//箱のタイプ（普通の箱か、置かれているか）
	bool m_moveBox = false;		//箱が移動中かどうか
	int m_step = 0;
	enum
	{
		empty,		//何も置かれていない
		ground,		//床
		wall,		//壁
		storage,	//置き場所（箱を置く場所）
		box,		//箱
		input,		//置かれた
		nextPos,	//次に置く場所の記憶
	};

	std::stack<int>m_tempField[kFieldY][kFieldX];
public:
	Field();
	~Field();

	//更新処理
	void Update();
	//描画処理
	void Draw();
	void DrawField(int x,int y);

	//プレイヤーが動かせるか配列のデータを見る関数
	bool IsMovable(int posX, int posY, int x, int y);
	//
	//プレイヤーの次の場所が動かせるか配列のデータを見る関数
	bool IsMovablePos(int x, int y);

	//ゲームクリアか判定
	bool GameClear()const;

	//フィールドの情報を持ってくる関数
	int FieldInfo(int field[kFieldY][kFieldX]);
	int StepLimit(int step);
	int StepLimit();

	//箱を移動させるための情報を持つ関数
	void MoveFrame(int posX, int posY, int x, int y, int type);
	//箱を移動させる処理
	void MoveFrame();

	//箱が移動中かどうか判定
	bool MoveBox()const;

	//フィールドの一つ戻す実装
	void tempFieldInput();
	//フィールドの一つ戻す実装
	void tempFieldOut();
};