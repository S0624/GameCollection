#pragma once
namespace Game
{
#ifdef _DEBUG
    // �E�C���h�E���[�h�ݒ�
    //constexpr bool kWindowMode = false;
    constexpr bool kWindowMode = false;
#else // _DEBUG
    constexpr bool kWindowMode = true;
#endif
    jnm

    // �E�C���h�E��
    const char* const kTitleText = "Bee Jump";

    // �E�C���h�E�T�C�Y
    constexpr int kScreenWidth = 1600;
    constexpr int kScreenHeight = 900;

    // �J���[���[�h
    constexpr int kColorDepth = 32;        // 32 or 16
};