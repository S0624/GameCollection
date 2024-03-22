#pragma once
#include "../Base/MoveTypeBase.h"
class Chicken :
	public MoveTypeBase
{
public:
	Chicken();// コンストラクタ
	virtual ~Chicken();// デストラクタ
	void Init();// 初期化
	void Update();// 更新処理
	void Draw(int sizeup);// 描画処理

	void SetReversal(bool reversal) { m_reversal = reversal; }// 反転しているか
	void SetPos(Vec2 pos) { m_pos = pos; }// プレイヤーの位置
	void SetFlag(bool flag) { m_exist = flag; }// 存在しているかのフラグをセット
	bool IsExist() { return m_exist; }// 存在しているかのフラグ
	float GetMovePos() { return m_move; }// 位置を渡す
	Vec2 GetPos() { return m_pos; }// プレイヤーの位置を記憶する
private:
	int m_handle;// 画像
	bool m_reversal;// 反転
	Vec2 m_pos;// 位置
	float m_movePos;// 動いた位置
	float m_move;// 動いた分の位置
	int m_animeFrame;// フレーム
	int m_animeMax;// アニメーションの末尾番号
	int m_animeWidth;// アニメーションのいち
	int m_animeHight;// アニメーションの地位
	bool m_exist;// 存在
	int m_countFrame;//	時間経過で消すので時間を数える関数
};

