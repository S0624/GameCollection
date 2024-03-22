#include<DXLib.h>
#include<assert.h>
#include"GameManager.h"

namespace my
{
	//画像の読み込み
	int MyLoadGraph(const TCHAR* path)
	{
		int handle = LoadGraph(path);
		//読み込めていなかったら処理を止める
		assert(handle >= 0);
		return handle;
	}
	//画像の表示
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg)
	{
		return DrawRectRotaGraph(x, y,
			left, top,
			width, height,
			scale, angle,
			handle, transFlg);
	}

	//フォントの読み込み
	void MyFontPath(const TCHAR* path)
	{
		LPCWSTR font_path = reinterpret_cast<LPCWSTR>(path); // 読み込むフォントファイルのパス

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		}
	//フォントの読み込みが失敗したら読み込み失敗を出す
		else {
			// フォント読込エラー処理
			MessageBox(NULL, L"フォント読込失敗", L"", MB_OK);
		}

	}



}