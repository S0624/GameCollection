#pragma once

namespace Game
{
	//ウィンドウモード
#ifdef _DEBUG
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif
	//ウィンドウ名
	const char* const kTitleText = "Project_K";
	//ウィンドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	//カラーモード
	constexpr int kColorDepth = 32; //３２or１６
};