#pragma once
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../Util/Vec2.h"
#include<array>

class ShotBase;
class ShotNull;

namespace
{
	// ショット数最大
	constexpr int kShotMax = 4;
}

// プレイヤーの基底クラス
class PlayerBase
{
public:
	PlayerBase();

	virtual ~PlayerBase() {};

	virtual void Init() {};	// 初期化
	virtual void End() {};	// 終了処理
	virtual void Update() {};	// 更新
	virtual void Draw() {};	// 描画

	// プレイヤーのサイズの当たり判定
	int GetSizeLeft() { return m_sizeLeft; }
	int GetSizeTop() { return m_sizeTop; }
	int GetSizeRight() { return m_sizeRight; }
	int GetSizeBottom() { return m_sizeBottom; }

	// プレイヤーの攻撃の当たり判定
	int GetAttackSizeLeft() { return m_attackSizeLeft; }
	int GetAttackSizeTop() { return m_attackSizeTop; }
	int GetAttackSizeRight() { return m_attackSizeRight; }
	int GetAttackSizeBottom() { return m_attackSizeBottom; }

	// アタックフラグ取得(攻撃したときtrue)
	bool GetAttackFlag() { return m_attackFlag; }
	// アタックフラグセット(攻撃が当たった時に連続でヒットするのを防ぐためfalseにする)
	virtual void SetAttackFlag(bool attackFlag) { m_attackFlag = attackFlag; }

	const int GetAttackFrame() const { return m_attackFrameCount; }

	// SceneMainにどの攻撃をしているかを渡す
	const int SetMove() const { return m_moveType; }

	// SceneMainから攻撃状態を受け取る
	void GetMove(int check) { m_moveType = check; }

	// SceneMainからプレイヤーが受けるダメージを受け取る
	int GetDamage() { return m_damage; }

	// ダメージを食らう時の処理()
	void OnDamage(int damage) { m_hp -= damage; }

	// 攻撃を食らったときダメージフレームに15を加える
	void SetOnDamageFrame() { m_onDamageFrame = 25; }

	// プレイヤーの体力取得
	const int GetHp() const { return m_hp; }

	// パッド番号取得(プレイヤー1とプレイヤー２を分けるため)
	void SetPadNum(int padNum) { m_padNum = padNum; }

	//ノックバックの処理(toPlayerはプレイヤーとプレイヤーの距離を求めるためのもの)
	void SetKnockBack(float toPlayer);

	void SetSize(int size) { m_sizeUp = size; }

	//ポジション取得
	Vec2 GetPos() { return m_pos; }
	void SetPos(Vec2 pos) { m_pos = pos; }

	//ショットポインタ取得
	ShotBase* GetShot(int i) { return m_pShot[i]; }

	//デバッグドローコリジョン
	void DebugDrawCollision();

	// ノックバック使用
	void KnockBack();

	/// <summary>
	/// キャラクターの初期位置
	/// </summary>
	/// <param name="posX">X座標</param>
	/// <param name="posY">Y座標</param>
	/// <param name="direction">キャラクターの向き</param>
	void CharDefaultPos(bool& direction);

	void moveLimit(); //画面外にキャラクターが出たとき
protected:
//	void attackCountUp();

	void damageMove(); //ダメージを受けた時の移動処理


	// プレイヤーのサイズ
	int m_sizeLeft = 0;
	int m_sizeTop = 0;
	int m_sizeRight = 0;
	int m_sizeBottom = 0;

	// 攻撃の判定
	int m_attackSizeLeft = 0;
	int m_attackSizeTop = 0;
	int m_attackSizeRight = 0;
	int m_attackSizeBottom = 0;

	// パッド番号
	int m_padNum = 0;

	// 攻撃発生から何フレーム経ったか
	int m_attackFrameCount = 0;

	// 攻撃を食らったときに次のモーションに移行するまでの時間
	int m_onDamageFrame = 0;
	// 攻撃を食らったとき
//	bool m_onDamageFlag;

	int m_moveType = 0;
	int m_hp = 100;	// プレイヤーの体力量(100が標準)
	int m_damage = 0;		// プレイヤーが受けるダメージ

	int m_sizeUp = 1;// プレイヤーのサイズの倍率

	bool m_attackFlag = false;	// 攻撃中かどうか

	bool m_isSpawn = false;	// キャラクターがスポーンされたかどうか

	Vec2 m_pos = { 0.0f,0.0f };	// 位置
	Vec2 m_vec = { 0.0f,0.0f };	// 運動量

	std::array<ShotBase*, kShotMax> m_pShot; // 画面上に存在できるショットポインタの配列

	Vec2 m_knockBack; // ノックバックベクトル
};