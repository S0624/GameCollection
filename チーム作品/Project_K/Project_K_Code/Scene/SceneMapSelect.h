#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include "../Util/Vec2.h"

class SceneMapSelect : public SceneBase
{
public:
	SceneMapSelect();			// コンストラクタ
	virtual ~SceneMapSelect();	// デストラクタ

	virtual void Init();		// 初期化
	virtual void End();
	
	virtual SceneBase* Update() override;	// 更新
	virtual void Draw();		// 描画

	// ステージが選ばれた時の処理
	//bool IsSelected() { return };

private:
	Vec2 m_pos;	// 座標	

	//**** UI用グラフィックハンドル ****//
	int m_stageHandle;	// 各ステージ縮小表示のハンドル
	int m_handle[5];	// 各ステージのハンドル
	int m_bgHandle;		// 背景
	int m_font;			// フォントハンドル

	// マップ判別用の番号変数
	int m_mapNum;

	// マップの状態
	enum StageState
	{
		RandStage = 1,	// ランダムステージ
		DinoStage,		// 恐竜ステージ
		ElfStage,		// エルフステージ
		MachoStage,		// マッチョステージ
		WizardStage,	// 魔女ステージ
	};
};

