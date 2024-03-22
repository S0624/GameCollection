#include "Common.h"
#include"Object/Player.h"
#include"Camera/Camera.h"
#include"Stage/Map.h"
#include"Object/BackGround.h"
#include"Scene/SceneManager.h"
#include "math.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // �g�p���� Direct3D �̃o�[�W������ 9EX �ɐݒ�
    SetUseDirect3DVersion(DX_DIRECT3D_9EX);
    
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);
    // �E�C���h�E���ݒ�
    SetMainWindowText("�Q�[����");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

    // �V�[���}�l�[�W���[�̐錾
    SceneManager* pSceneManager;
    pSceneManager = new SceneManager;
    pSceneManager->Init();

    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();

        // �X�V����
        pSceneManager->Update();
        // �`�揈��
        pSceneManager->Draw();

#ifdef  false
            DrawFormatString(100, 0, 0xff0000, "%d", GetDrawCallCount());
#endif //  false

        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }

    // �G���h����
    pSceneManager->End();
    // �f���[�g
    delete(pSceneManager);
    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}