#pragma once

#include "../Base/PlayerBase.h"

class KinnikuIdle;
class KinnikurouJab;
class KinnikuMuscle;
class KinnikuUpper;
class KinnikuMizo;
class KinnikuRun;
class KinnikuJump;
class KinnikuDead;

class Kinnikurou : public PlayerBase
{
public:
	Kinnikurou();
	virtual ~Kinnikurou();

	void Init  ();// 初期化
	void End   ();// 終了処理
	void Update();// 更新
	void Draw()override;// 描画

	void ImgposInit();// 画像位置の初期化
	void AttackCol();// 攻撃のタイミング
	void InitAttackFlag();// 攻撃フラグの初期化
	void UpdateKnockBack();// ノックバック中の処理
	void MotionCountDown();// モーションのフレームカウントダウン

	void UpdateRun();// 走りモーション
	void UpdateAttack();// 攻撃モーション
	void CollisionSize(int left, int top, int Right, int Bottom);// 攻撃判定の代入
	void HandleAssignment(int handle, int width, int height);

private:
	// ポインタ
	KinnikuIdle* m_pIdle;// アイドル状態
	KinnikurouJab* m_pJab;// ジャブ攻撃状態
	KinnikuMuscle* m_pMuscle;// 胸筋衝撃波攻撃状態
	KinnikuUpper* m_pUpper;// アッパー攻撃状態
	KinnikuMizo* m_pMizo;// みぞおち攻撃状態
	KinnikuRun* m_pRun;// 移動状態
	KinnikuJump* m_pJump;// ジャンプ状態
	KinnikuDead* m_pDead;// 死亡状態

	// ハンドル
	int m_charHandle;// キャラクター全体
	int m_idleHandle;// アイドル状態
	int m_jabHandle;// ジャブ攻撃状態
	int m_muscleHandle;// 胸筋衝撃波攻撃状態
	int m_UpperHandle;// アッパー攻撃状態
	int m_MizoHandle;// みぞおち攻撃状態
	int m_RunHandle;// 移動状態
	int m_JumpHandle;// ジャンプ状態
	int m_FallHandle;// 落下状態
	int m_DeadHandle;// 死亡状態

	// 画像の座標
	int m_imgPosX;// X
	int m_imgPosY;// Y

	// 画像の一片の長さ
	int m_imgWidth;// X
	int m_imgHeight;// Y

	// モーション終わりのカウント
	int m_motionCount;

	// 初期化回数
	int m_initCount;

	// ジャンプ加速度
	float m_jumpAcc;

	// キャラの向き
	bool m_charDirection;

	// キャラが移動状態かどうか
	bool m_charRun;

	// キャラの攻撃判定のタイミング
	bool m_isAttack;

	// キャラがジャンプ中かどうか
	float m_isJump;

	// テスト変数
	int m_stiffen = 0;// 硬直

	int m_testCount = 0;
};

