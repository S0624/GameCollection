#include "DxLib.h"

#include"Scene/SceneTitle.h"
#include"Scene/SceneSelect.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // windowモード設定
    ChangeWindowMode(Game::kWindowMode);
    SetWindowSizeChangeEnableFlag(true);//ウィンドウモードの拡大縮小（サイズ変更）が可能になります
    SetAlwaysRunFlag(true);//dxlib.exeにフォーカス合わせなくても更新処理を続けてくれる関数です

    // ウインドウ名設定
    SetMainWindowText(L"片付け番");
    
    // 画面サイズの設定
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    SceneManager* scene;
    InputState* input;

    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);

    input = new InputState;
    scene = new SceneManager;
    scene->ChangeScene(new SceneTitle(*scene));
    //scene->ChangeScene(new SceneSelect(*scene));
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();
        input->Update();
        scene->Update(*input);
        scene->Draw();
        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (input->IsPressed(InputType::end))
        {
            break;
        }
        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    delete input;
    delete scene;
    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}