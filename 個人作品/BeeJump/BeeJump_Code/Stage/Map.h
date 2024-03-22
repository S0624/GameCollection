#pragma once
#include <vector>
#include<memory>
#include <map>
#include<string>
#include "../Common.h"

// �N���X�̐錾
class GameObject;
class Stage;
class Player;
class CurrentPlayerMap;

/// <summary>
/// �}�b�v��\������
/// </summary>
class Map
{
public:
	// �R���X�g���N�^
	Map(int selectNum);
	// �f�X�g���N�^
	~Map();

	// �}�b�v�̃��[�h
	void Load();
	// �}�b�v�̍X�V����
	void Update();
	// �}�b�v�̕`��
	void Draw();

	// �G���h���X��I�������Ƃ��ɍs������
	void SelectEndless();
	// �v���C���[�����̓����蔻��
	void CollisionDetection(Player* player);
	// �Q�[�����N���A�������̃t���O
	bool GameClearFlag() { return m_gameClearFlag; }

private:
	std::map <int, const char*> m_mapLoad;
	int m_selectNum;		// �I��ł���ԍ�
	std::vector<std::vector<int>> m_currentData;		// �ǂݍ��񂾃f�[�^���ꎞ�I�ɕۑ�����
	Stage* m_pStage;									// �X�e�[�W�N���X�̐錾
	std::vector<std::shared_ptr<GameObject>> m_pObject;	// �I�u�W�F�N�g�N���X�̐錾
	CurrentPlayerMap* m_pCurrentMap;					// �~�j�}�b�v�N���X�̐錾

	int m_dataColNum;		// ���̍ő吔
	int m_dataRowNum;		// �c�̍ő吔
	int m_max;				// �J�[�\���̑I�𐔂̍ő吔
	int m_maxRand;			// �����_���Ȑ��𐶐�����Ƃ��̍ő吔
	bool m_gameClearFlag;	// �Q�[�����N���A�������̐錾
	float m_collisionradius;// �����蔻��Ɏg5�p���锼�a�̑傫��
	int	m_objectPosX;		// �I�u�W�F�N�g�̉��̍ő�l���擾���邽�߂ɗp��
};

