#pragma once
#include "../Common.h"

class CurrentPlayerMap
{
public:
	// �R���X�g���N�^(�}�b�v�̈�ԃS�[���ɋ߂��u���b�N�̈ʒu��������Ă���)
	CurrentPlayerMap(int maxMapPosX);
	// �f�X�g���N�^
	~CurrentPlayerMap();

	// �X�V����
	void Update();
	// �`��
	void Draw();

private:
	int	m_maxMapPosX;		// �I�u�W�F�N�g�̉��̍ő�l���擾���邽�߂ɗp��
	int m_minMapHandle;		// �~�j�}�b�v�̉摜
	int m_playerHandle;		// �v���C���[�̉摜

	int m_playerStartPos;	// �v���C���[(�摜)�̃X�^�[�g�n
	int m_playerPosX;		// �v���C���[(�摜)�̌��ݒn
	int m_playerMove = 0;	// �v���C���[(�摜)�̈ړ���
	float m_mapRate = 3.0f;	// �}�b�v(�摜)�̑傫��

	int m_mapHandleSizeWidth;	//�}�b�v�̑傫���̎擾(��)
	int m_mapHandleSizeHight;	//�}�b�v�̑傫���̎擾(�c)
	int m_playerHandleSizeWidth;//�v���C���[�̑傫���̎擾(��)
	int m_playerHandleSizeHight;//�v���C���[�̑傫���̎擾(�c)
};

