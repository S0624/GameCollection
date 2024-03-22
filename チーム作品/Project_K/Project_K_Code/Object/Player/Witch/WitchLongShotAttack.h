#pragma once
#include "../Base/MoveTypeBase.h"
class WitchLongShotAttack :
    public MoveTypeBase
{
public:
	WitchLongShotAttack();// コンストラクタ
	virtual ~WitchLongShotAttack() {}// デストラクタ

	void Init();// 初期化
	void Update();// 更新処理

	int IndexX() { return m_animeWidth; }// アニメーションのセット用
	int IndexY() { return m_animeHight; }// アニメーションのセット用
	int SizeX() { return m_indexX; }// サイズ変更
	int ShiftX() { return m_shiftX; }// ずらしよう
	int AnimeMax() { return m_animeMax; }// アニメーションのセット用
	void SetReversal(bool reversal) { m_reversal = reversal; }// 反転
private:
	int m_animeWidth;// 横
	int m_animeHight;// 縦
	int m_animeMax;//末尾
	int m_indexX;// サイズ
	int m_shiftX;// ずらす
	bool m_reversal;// 反転
};

