#pragma once
#include "../../Util/Vec2.h"
#include "../../Util/game.h"
#include "../Stage/StageBase.h"
#include<vector>

class StageBase
{
public :
	StageBase(int StageNo);			// コンストラクタ
	virtual ~StageBase();	// デストラクタ

	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画

	int MapRead();	// マップの読み込み

	int GetStartX() const { return m_startX; }	// 始点座標Xの取得
	int GetStartY() const { return m_startY; }	// 始点座標Yの取得
	int GetEndX() const { return m_endX; }		// 終点座標Xの取得
	int GetEndY() const { return m_endY; }		// 終点座標Yの取得

	struct MapInfo
	{
		Vec2 m_pos;		// マップの座標
		int m_chipNo=0;	// マップチップの番号
	};

protected :
	std::vector<MapInfo> m_data;// vector型の2次元配列変数

	int m_handle;	// グラフィックハンドル
	int m_bgHandle;	// 背景用グラフィックハンドル
	int m_subPos;	// マッチョグラフィックハンドルの座標差分

	int m_startX;	// 始点の座標X
	int m_startY;	// 始点の座標Y
	int m_endX;		// 終点の座標X
	int m_endY;		// 終点の座標Y

	int m_stageNo;			// ステージの番号
	const char* m_filePath;	// ステージのcsvパス
};

