#pragma once
#include "../../../condition.h"
#include"../../Util/Vec2.h"
#include "../../Util/Pad.h"

class DinosaurStateBase
{
public:
	//デストラクタ
	virtual ~DinosaurStateBase() {};

	//初期化
	virtual void Init(int Handle);

	//アップデート
	virtual DinosaurStateBase* Update(int padNum) { return this; }

	//画像表示
	virtual void Draw(int handle, bool lookRight,Vec2 pos,int size);

	//毎フレームごとに表示する画像を変更
	virtual void ChangeGraph(int ChangeSpeed, int GraphNum, bool ChangeY);

	//移動ベクトル取得
	virtual Vec2 GetVec() { return m_vec; }
	
	//ショットを撃ったかどうかのフラグ
	virtual bool GetshotFlag() { return m_shotFlag; }

	//攻撃しているかどうかフラグ取得
	virtual bool GetAttackFlag() { return m_attackFlag; }
	//攻撃が当たった時にフラグをセット(falseにする)
	virtual bool SetAttackFlag(bool attackFlag) { return m_attackFlag = attackFlag; }

	// キャラクターが死んでいるかどうか
	virtual void SetDeadFlag() { m_deadFlag = true; }

	//キャラクターが向いている方向
	virtual void SetLookFlag(bool RightFlag) { m_lookLeft = RightFlag; }

	//キャラクターのサイズを取得
	int GetAttackSizeLeft() { return m_attakSizeLeft; }
	int GetAttackSizeTop() { return m_attackSizeTop; }
	int GetAttackSizeRight() { return m_attackSizeRight; }
	int GetAttackSizeBottom() { return m_attackSizeBottom; }

	//攻撃力取得
	int GetAttackDamage() { return m_attackDamage; }
	
	//攻撃モーションかどうか取得
	bool GetAttackMotion() { return m_attackMotion; }

protected:
	int m_handle;

	bool m_shotFlag = false;	//ショットフラグ
	bool m_lookLeft = false;	// 左を向いているか
	bool m_deadFlag = false; //死んでいるかどうか

	int m_attakSizeLeft = 0;
	int m_attackSizeTop = 0;
	int m_attackSizeRight = 0;
	int m_attackSizeBottom = 0;

	int m_frameCount = 0;// アニメーションを再生させる用フレームカウント

	int m_imagePosX = 0;// 画像の描画位置
	int m_imagePosY = 0;

	int m_gapTime = 0; // 後隙

	int m_attackFrame = 0;//攻撃フラグがtrueになるまでの時間

	int m_attackDamage = 0;// プレイヤーがエネミーに与えるダメージ量
	bool m_attackFlag = false; //攻撃判定があるとき
	bool m_isMove = false;
	Vec2 m_vec = { 0.0f,0.0f };// 運動量

	bool m_attackMotion = false; //攻撃モーションのとき
};

