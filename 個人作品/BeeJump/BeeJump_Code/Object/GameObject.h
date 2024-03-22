#pragma once

#include "../Common.h"
#include<memory>
#include<vector>

// �N���X�̐錾
class Model;
class Player;

/// <summary>
/// �u���b�N�\���N���X
/// </summary>
enum Object
{
	Empty,		// ��
	Field,		// ��
	Flag,		// ��(�S�[��)
};

class GameObject
{
public:
	// �R���X�g���N�^
	// ���f���̃n���h���A�g�p���铖���蔻��̃t���[���A�`�悷��ʒu��X��Y���W
	GameObject(const char* modelhnadle, int objNum, int blockX, int blockY);
	GameObject(int modelhnadle, int objNum, int blockX, int blockY);

	// �f�X�g���N�^
	~GameObject();				

	// ����������
	void Init(){};			
	// �X�V
	void Update();			
	// �`��
	void Draw();		

	// ��ʓ��Ƀu���b�N�����邩�ǂ���
	bool IsExist();

	bool IsDrawFlag();

	// ���f���n���h���̎擾
	int GetModelHandle() const;
	//	�����蔻��̎擾
	int GetCollisionFrameIndex() const;
	
	const int GameObjectNum() const { return m_objectNum; }
	const int GetPosX() const { return m_pos.x; }	// �ő�l���擾���邽�߂ɗp��

private:
	std::shared_ptr<Model> m_pModel;// ���f���̕\��
	int		m_modelHandle;	// ���f���n���h��
	VECTOR	m_pos;			// �|�W�V����

	const float m_speed;	// �X�N���[���̃X�s�[�h
	const float m_scale;	// ���f���̑傫��

	int m_blockX;			// �u���b�N�̈ʒu��������Ă���
	int m_blockY;			// �u���b�N�̈ʒu��������Ă���

	bool m_drawRange;		//	�`�悵�Ă����͈͂��ǂ���
	bool m_isExist;			//	0��菬�����Ȃ����ǂ���
	int m_objectNum;		//  �I�u�W�F�N�g�̎g�p���Ă���ԍ�
};

