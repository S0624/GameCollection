#include "FontFunction.h"
#include"DxLib.h"

// フォント読み込み
void font::MyFontPath(const TCHAR* path)
{
	LPCTSTR font_path = reinterpret_cast<LPCTSTR>(path); // 読み込むフォントファイルのパス

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//フォントの読み込みが失敗したら読み込み失敗を出す
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
}