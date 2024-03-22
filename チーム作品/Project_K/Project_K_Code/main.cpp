#include <DxLib.h>
#include "Util/game.h"
#include "Scene/SceneManager.h"
#include "Util/Sound.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode             (Game::kWindowMode                                         );// windowモード設定
	SetMainWindowText            (Game::kTitleText                                          );// ウインドウ名設定
	SetGraphMode                 (Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);// 画面サイズの設定
	SetWindowSizeChangeEnableFlag(true                                                      );// ウインドウモードの時にウインドウのサイズ変更できる
	SetAlwaysRunFlag			 (true                                                      );// ウインドウがアクティブではない状態でも処理を続行する

	if (DxLib_Init() == -1)// ＤＸライブラリ初期化処理
	{
		return -1;// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);// ダブルバッファモード

	// サウンドをロードする
	Sound::load();


	SceneManager scene;
	scene.Init();// シーンの初期化

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		
		ClearDrawScreen();// 画面のクリア

		scene.Update();// シーンの更新処理
		scene.Draw();// シーンの描画

		ScreenFlip();// 裏画面を表画面を入れ替える

		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;// escキーを押したら終了する

		while (GetNowHiPerformanceCount() - time < 16667) {}// fpsを60に固定
	}

	scene.End();// シーンの終了処理

	Sound::unload();

	DxLib_End();// ＤＸライブラリ使用の終了処理

	return 0;// ソフトの終了 
}