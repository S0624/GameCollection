#include "CurrentPlayerMap.h"

CurrentPlayerMap::CurrentPlayerMap(int maxMapPosX):
	m_maxMapPosX(maxMapPosX),
	m_minMapHandle(-1),
	m_playerHandle(-1),
	m_playerStartPos(0),
	m_playerPosX(0),
	m_playerMove(0),
	m_mapRate(3.0f),
	m_mapHandleSizeWidth(),
	m_mapHandleSizeHight(),
	m_playerHandleSizeWidth(),
	m_playerHandleSizeHight()
{
	// �摜�̃��[�h
	m_minMapHandle = LoadGraph("Data/Img/MinMap.png");
	m_playerHandle = LoadGraph("Data/Img/Bee.png");

	// �摜�T�C�Y�̎擾
	GetGraphSize(m_minMapHandle,&m_mapHandleSizeWidth, &m_mapHandleSizeHight);
	GetGraphSize(m_playerHandle,&m_playerHandleSizeWidth, &m_playerHandleSizeHight);

	// �v���C���[(�摜)�̃X�^�[�g�n
	m_playerStartPos = 220 - (m_mapHandleSizeWidth / 2 + m_playerHandleSizeWidth / 2);
	// �v���C���[(�摜)�̌��ݒn
	m_playerPosX = m_playerStartPos;
}

CurrentPlayerMap::~CurrentPlayerMap()
{
	// �摜�̍폜����
	DeleteGraph(m_minMapHandle);
	DeleteGraph(m_playerHandle);
}

void CurrentPlayerMap::Update()
{
	// �v���C���[(�摜)���X�N���[��������
	m_playerMove++;
	// �ő�l���X�N���[�����Ȃ��悤�ɏ���
	if (m_playerMove > m_maxMapPosX)
	{
		m_playerMove = m_maxMapPosX;
	}
	// �v���C���[(�摜)�̈ړ�������
	// ���̏ꏊ�@ = �i�񂾋��� * �Q�[�W�̒���/�Q�[�W�̍ő吔
	m_playerPosX = m_playerStartPos + (m_playerMove * (100 * m_mapRate) / m_maxMapPosX);

}

void CurrentPlayerMap::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			// �u�����h���[�h���������ăX�R�A�̃p�l���𔼓����ɂ���
	DrawBox(20, 30, 400, 180, 0x000000, true);
														// �X�R�A�ł̕\��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�

	// �}�b�v(�摜)�̕\��
	DrawRectRotaGraph(200, 70,
		0, 0, m_mapHandleSizeWidth, m_mapHandleSizeHight,
		m_mapRate, 0.0f,
		m_minMapHandle,
		true, false);

	// �v���C���[(�摜)�̕\��
	DrawRectRotaGraph(m_playerPosX, 70,
		0, 0, m_playerHandleSizeWidth, m_playerHandleSizeHight,
		0.35f, 0.0f,
		m_playerHandle,
		true, false);
}
