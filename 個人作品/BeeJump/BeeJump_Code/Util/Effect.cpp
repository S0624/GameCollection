#include "Effect.h"
// EffekseerForDXLib.h���C���N���[�h���܂��B
//#include "EffekseerForDXLib.h"
#include<cassert>
Effect::Effect():
    m_effectHandle(),
    m_currentPlayEffect(),
    m_pos()
{
    m_pos.x = 0;
    m_pos.y = 10;
    m_pos.z = -50;
}

Effect::~Effect()
{
    //// �I�����ɃG�t�F�N�g�̍폜
    //DeleteEffekseerEffect(m_effectHandle);
    //Effkseer_End();
}

void Effect::Init()
{
    //SetUseDirect3DVersion(DX_DIRECT3D_11);

    //// �t���X�N�؂�ւ����Ƀf�o�C�X�����X�g����̂�h�~
    //SetChangeScreenModeGraphicsSystemResetFlag(false);
    //Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    //// �G�t�F�N�g�̃��[�h
    //m_effectHandle = LoadEffekseerEffect("Data/Effect/FireFlower.efk", 1.0f);
    //assert(m_effectHandle != -1);
    //m_sampleHandle = LoadGraph("Data/Img/Sample.png");
}

void Effect::Update()
{
    //m_pos.y = 10;
    //m_pos.z = -50;
    //m_pos.x += 10;

    //Effekseer_Sync3DSetting(); // Dxlib��3D�ݒ��Effekseer�ɔ��f
    //// �Đ�����������Đ����Ȃ�
    //if (IsEffekseer3DEffectPlaying(m_currentPlayEffect))
    //{
    //    // �X�y�[�X�������ꂽ��
    //    if (Pad::IsTrigger(PAD_INPUT_3))
    //    {
    //        // �����Đ�����������~�߂�
    //        StopEffekseer3DEffect(m_currentPlayEffect);
    //        // �ʒu�����炷
    //        m_pos.x = 120;
    //        m_currentPlayEffect = PlayEffekseer3DEffect(m_effectHandle);
    //        // �G�t�F�N�g�̈ʒu��ݒ�
    //        SetPosPlayingEffekseer3DEffect(m_currentPlayEffect, m_pos.x, m_pos.y, m_pos.z);
    //        assert(m_effectHandle != -1);

    //    }
    //}
    ////DrawGraph(0, 0, m_sampleHandle, true);
    //// �G�t�F�N�g�̍X�V����
    //UpdateEffekseer3D();

}

void Effect::Draw()
{
    // �G�t�F�N�g�̕\��
    //DrawEffekseer3D();
}