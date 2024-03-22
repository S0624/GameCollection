#pragma once

#include "../Common.h"
#include<memory>

class Model;
class GameObject;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	// コンストラクタ
	Player();				
	// デストラクタ
	~Player();				


	// 初期化処理
	void Init() {};			
	// 更新
	void Update();			
	// 描画
	void Draw();			

	// プレイヤーの位置の取得
	const VECTOR& GetPlayerPos() const { return m_pos; }
	// プレイヤーの当たり判定の取得
	const float GetCollisionRadius()const { return m_colradius; }

	// プレイヤーの生死判定
	bool IsExistPlayer() { return m_isExist; }
	// プレイヤーの生死判定
	bool IsExistPlayer(bool isexist) { return m_isExist = isexist; }
	// プレイヤーの落下地点の予測
	int PlayerDropPoint(int _dropPos) { return m_dropPos = _dropPos; }

	// OPTIMIZE ゲームクリアフラグを受け取る
	bool GameClearFlag(bool flag) { return m_gameSituation = flag; }
private:
	// プレイヤーモデル
	std::shared_ptr<Model> m_pModel;

	int		m_modelHandle;	// モデルハンドル
	VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向
	float   m_colradius;	// 当たり判定に使用する半径の大きさ
	bool	m_isExist;		// プレイヤーが死亡したかどうか
	int     m_dropPos;		// 箱の位置によって落ちる場所を変える	

	 const float m_speed;	// スピードの変更
	 const float m_scale;	// モデルの大きさ　
	 float       m_jumpAcc;	// ジャンプ
	 int	m_attachIndex;	// 総時間取得するアニメーションのアタッチ番号
	 int	m_totalTime;	// アニメーションの総再生時間
	 float	m_animTime;		// 現在のアニメーションの再生時間
	 int	m_attachAnimNum;// 再生したいアニメーションの番号

	 // OPTIMIZE ゲームクリアフラグを受け取る
	 bool m_gameSituation;	// ゲームの状態を受け取る
};
