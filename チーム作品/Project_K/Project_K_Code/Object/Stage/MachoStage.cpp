//#include "MachoStage.h"
//#include <DxLib.h>
//#include "../../Util/game.h"
//
//namespace
//{
//	// テクスチャ情報
//	const char* kMachoBgFileName = "Data/Image/Stage/macho/city.png";
//}
//
//MachoStage::MachoStage(int stageNo) :
//	m_handle(-1),// グラフィックハンドルの初期化
//	StageBase(stageNo)
//{
//}
//
//void MachoStage::Init()
//{
//	//グラフィックのロード
//	m_handle = LoadGraph(kMachoBgFileName);
//}
//
//void MachoStage::Update()
//{
//	// 処理なし
//}
//
//void MachoStage::Draw()
//{
//	// 拡大描画
//	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_handle, false);
//}
