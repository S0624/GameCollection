#pragma once

#include "../Base/PlayerBase.h"
// 必要なクラスの宣言
class WitchIdle;
class WitchRun;
class WitchShotAttack;
class WitchLongShotAttack;
class WitchCharge;
class Chicken;
class KnightCat;
class WitchDead;

class Witch : public PlayerBase
{
public:
	Witch();// コンストラクタ
	virtual ~Witch();// デストラクタ

	// 初期化
	void Init();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// パッドがおされた時の状態
	void UpdateInputKey();
	// プレイヤーの状態
	void UpdatePlayerState();
	// プレイヤーのジャンプ処理
	void UpdateJump();
	// プレイヤーの通常状態アニメーション処理
	void UpdateAnim();
	// プレイヤーの死亡アニメーション処理
	void UpdateDead();
	//プレイヤーの当たり判定
	void UpdatePlayerJudge();
	//プレイヤーの攻撃の当たり判定
	void UpdateAttackJudge();
private:
	// 魔女の状態のクラスのロード
	WitchIdle* m_pIdle;// アイドル状態
	WitchRun* m_pRun;// 走ってる
	WitchShotAttack* m_pShot;// ちっちゃい氷
	WitchLongShotAttack* m_pLongShot;// 四連氷
	WitchCharge* m_pCharge;// チャージ
	Chicken* m_pChicken;// にわとり
	KnightCat* m_pKnightCat;// ねこちゃん
	WitchDead* m_pDead;// 死亡

	int m_handle;// 画像
	int m_animeWidth;// 画像の横
	int m_animeHight;// 画像の縦
	bool m_reversal;// 画像を反転させるかどうか
	int m_animeLoopCount;// チャージするときのループする回数をいれる変数
	int m_LoopCount;// 何回ループしたか数える変数
	int m_animeFrame;//アニメーションの速さ
	int m_animeMax;//アニメーションの最大値
	int m_indexX;// 画像の横の切り取り幅
	float m_playerjudge;// 画像によるずれを補正する変数
	int m_shiftX;// 画像のサイズが違うことによる問題を補正する変数
	bool m_animeFlag;// アニメーションが行われているかのフラグ

	float m_temp;// ジャンプ用に元居た高さをいれる変数
	bool m_jumpFlag;// ジャンプ中かどうかのフラグ
	int m_jumpPower;// ジャンプのパワー
	bool m_tempFlag1;// 攻撃中か（にわとり）　力業実装のために用意しましたその1
	bool m_tempFlag2;// 攻撃中か（ねこちゃん）力業実装のために用意しましたその2
	int m_movement;// ジャンプするときにXを動かす分
};