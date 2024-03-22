#pragma once
#include "../Common.h"

class CurrentPlayerMap
{
public:
	// コンストラクタ(マップの一番ゴールに近いブロックの位置をもらってくる)
	CurrentPlayerMap(int maxMapPosX);
	// デストラクタ
	~CurrentPlayerMap();

	// 更新処理
	void Update();
	// 描画
	void Draw();

private:
	int	m_maxMapPosX;		// オブジェクトの横の最大値を取得するために用意
	int m_minMapHandle;		// ミニマップの画像
	int m_playerHandle;		// プレイヤーの画像

	int m_playerStartPos;	// プレイヤー(画像)のスタート地
	int m_playerPosX;		// プレイヤー(画像)の現在地
	int m_playerMove = 0;	// プレイヤー(画像)の移動量
	float m_mapRate = 3.0f;	// マップ(画像)の大きさ

	int m_mapHandleSizeWidth;	//マップの大きさの取得(横)
	int m_mapHandleSizeHight;	//マップの大きさの取得(縦)
	int m_playerHandleSizeWidth;//プレイヤーの大きさの取得(横)
	int m_playerHandleSizeHight;//プレイヤーの大きさの取得(縦)
};

