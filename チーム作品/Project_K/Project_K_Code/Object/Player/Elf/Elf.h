#pragma once

#include "../Base/PlayerBase.h"

#include <vector>

class ElfIdle;
class ElfRun;
class ElfJump;
class ElfAttackArrowChargeShot;
class ElfAttackArrowShot;
class ElfAttackArrowPunch;
class ElfAttackArrowUp;

//class ShotBase;

class Elf : public PlayerBase
{
public:
	Elf();
	~Elf();

	void Init();// 初期化
	void End();// 終了処理
	void Update();// 更新
	void Draw();// 描画
private:

	void UpdateControl();// 操作

	void AnimStop();// アニメーション停止

	void AnimSwitch();// アニメと攻撃範囲を指定

	void UpdateHitColl();// 自身の当たり判定

	void UpdateGravity();// 重力関連

	void AnimIdol(); // 待機状態アニメーション
	void AnimRun();  // 走りアニメーション
	void AnimJump(); // ジャンプアニメーション
	void AnimAttackPunch();     // パンチアニメーション
	void AnimAttackNormalShot();// 通常ショットアニメーション
	void AnimAttackChargeShit();// チャージショットアニメーション
	void AnimAttackUpShit();    // 上攻撃アニメーション

private:
	int m_handle;// 画像ハンドル
	int m_shotHandle;//ショットハンドル

	int m_imageX, m_imageY;// 画像描画位置

	int m_gapTime;

	int m_chargeHitPos = 0;

	int m_chargeShotCount = 0;

	float m_jumpAcc = 0.0f;

	bool m_isAttack;// 攻撃ができるかどうか

	bool m_isAttackHit;

	bool m_isDirection;// 向いている方向

	ElfIdle* m_pIdle;// 待機
	ElfRun* m_pRun; // 走り
	ElfJump* m_pJump;
	ElfAttackArrowChargeShot* m_pChargeShot;// 攻撃
	ElfAttackArrowShot* m_pShoot;      // 攻撃
	ElfAttackArrowPunch* m_pPunch;     // 攻撃
	ElfAttackArrowUp* m_pUp;        // 攻撃


};


