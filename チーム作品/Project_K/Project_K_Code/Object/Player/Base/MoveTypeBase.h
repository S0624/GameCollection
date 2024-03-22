#pragma once

#include "../../Util/Vec2.h"

class MoveTypeBase //プレイヤーの基底クラス
{
public:
	MoveTypeBase() {};
	virtual ~MoveTypeBase() {};

	virtual void Update() {};// 更新

	int SetPosAttackLeft  () { return m_posAttackLeft;   } //SceneMainにプレイヤーの攻撃範囲を渡す
	int SetPosAttackTop   () { return m_posAttackTop;    }
	int SetPosAttackRight () { return m_posAttackRight;  }
	int SetPosAttackBottom() { return m_posAttackBottom; }

	int SetPosImageX() { return m_imagePosX; }// 画像のキャラのどこを描画をするかどうか
	int SetPosImageY() { return m_imagePosY; }

	int SetAttackDamage() { return m_attackDamage; }// 敵に与えるダメージ量

	bool IsSetMove() { return m_isMove; }
	void SetMoveTime(bool move) { m_isMove = move; }

protected:
	int m_posAttackLeft   = 0;// プレイヤーの攻撃範囲
	int m_posAttackTop    = 0;
	int m_posAttackRight  = 0;
	int m_posAttackBottom = 0;

	int m_frameCount = 0;// アニメーションを再生させる用フレームカウント

	int m_imagePosX = 0;// 画像の描画位置
	int m_imagePosY = 0;

	int m_attackDamage = 0;// プレイヤーがエネミーに与えるダメージ量
	bool m_isMove = false;
	Vec2 m_vec = { 0.0f,0.0f };// 運動量
};