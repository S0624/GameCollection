#pragma once
#include <DxLib.h>
#include<tchar.h>
#include "Util/game.h"
#include "Util/Pad.h"
#include "Util/SoundManager.h"

namespace Color
{
	const int kBlack = 0x000000;		// 黒
	const int kBrown = 0xA52A2A;		// 茶
	const int kRed = 0xff0000;			// 赤
	const int kPeach = 0xff00ff;		// 桃
	const int kGreen = 0x00ff00;		// 緑
	const int kBlue = 0x0000ff;			// 青
	const int kLightBlue = 0x00ffff;	// 水
	const int kYellow = 0xffff00;		// 黄
	const int kYellowGreen = 0x9ACD32;	// 黄緑
	const int kWhite = 0xffffff;		// 白
}

namespace font
{
	//フォントの読み込み
	void MyFontPath(const TCHAR* path);
};

// 選ばれた難易度
enum Mode
{
	Easy,		// イージー
	Normal,		// ノーマル
	Hard,		// ハード
	Endless,	// エンドレス
};