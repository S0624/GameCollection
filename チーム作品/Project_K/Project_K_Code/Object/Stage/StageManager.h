#pragma once
#include <memory>

class StageBase;	// ステージベース

class StageManager
{
public:
	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画

private:
	std::shared_ptr<StageBase> m_pStage;	// ステージベースのポインタ変数
};

