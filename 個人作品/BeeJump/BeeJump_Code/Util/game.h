#pragma once
namespace Game
{
#ifdef _DEBUG
    // ウインドウモード設定
    //constexpr bool kWindowMode = false;
    constexpr bool kWindowMode = false;
#else // _DEBUG
    constexpr bool kWindowMode = true;
#endif
    jnm

    // ウインドウ名
    const char* const kTitleText = "Bee Jump";

    // ウインドウサイズ
    constexpr int kScreenWidth = 1600;
    constexpr int kScreenHeight = 900;

    // カラーモード
    constexpr int kColorDepth = 32;        // 32 or 16
};