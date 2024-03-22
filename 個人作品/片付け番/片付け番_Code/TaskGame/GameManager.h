#pragma once
#include<tchar.h>

//自分用ライブラリ用名前空間
namespace my
{
	//画像の読み込み
	int MyLoadGraph(const TCHAR* path);

	//画像の表示
	int MyDrawRectRotaGraph(int x, int y, int left, int top,
		int width, int height, float scale, float angle, int handle, bool transFlag);

	//フォントの読み込み
	void MyFontPath(const TCHAR* path);
}
