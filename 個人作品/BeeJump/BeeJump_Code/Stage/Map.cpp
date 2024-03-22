#include "Map.h"
#include "Stage.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"
#include"../Util/CurrentPlayerMap.h"

namespace
{
	// ���f���̃n���h��
	const char* const kFieldHandle = "Data/Model/Block.mv1";	// �t�B�[���h�p�̃��f��
	const char* const kFlagHandle = "Data/Model/Flag.mv1";		// ���p�̃��f��
	// �����蔻��Ƃ��Ďg�p����t���[���̖��O
	const char* const kCollisionFrameNamu = "BoxCol";
	// �v���C���[�̈ʒu���󂯎��
	VECTOR kPlayerPos = { 0,0,0 };
	// �v���C���[�̓����蔻��̑傫�����󂯎��
	float kPlayerRad = 0;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map(int selectNum) :
	m_pCurrentMap(nullptr),
	m_selectNum(selectNum),
	m_dataColNum(0),
	m_dataRowNum(0),
	m_collisionradius(0),
	m_max(1),
	m_maxRand(3),
	m_gameClearFlag(false),
	m_objectPosX(0)
{	
	m_currentData.clear();
	// �}�b�v�̃��[�h
	m_pStage = new Stage;

	m_mapLoad[Easy] = "Data/Map/Easy.fmf" ;
	m_mapLoad[Normal] =  "Data/Map/Normal.fmf";
	m_mapLoad[Hard] = "Data/Map/Hard.fmf" ;
	m_mapLoad[Endless] =  "Data/Map/Normal.fmf" ;
	
	if (m_selectNum != Endless)
	{
		m_pStage->Load(m_mapLoad[m_selectNum]);
	}
	else if (m_selectNum == Endless)
	{
		SelectEndless();
	}
	// ��������ȊO�̐������I�΂ꂽ�ꍇ�A�Ƃ肠����Easy�����[�h����
	else
	{
		m_pStage->Load(m_mapLoad[Easy]);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	m_mapLoad.clear();
	delete(m_pStage);
	delete(m_pCurrentMap);
	m_pObject.clear();
}

/// <summary>
/// ���[�h
/// </summary>
void Map::Load()
{
	// currentData�ɊO���t�@�C������
	m_currentData.clear();
	std::vector<int> newColData;

	m_pStage->GetMapSize(m_dataRowNum, m_dataColNum);
	const auto mapData = m_pStage->GetMapData();
	for (int i = m_dataColNum - 1; i >= 0; i--)
	{
		newColData.clear();
		for (int j = 0; j < m_dataRowNum; j++)
		{
			newColData.push_back(m_pStage->GetChipId(0, j, i));
		}
		m_currentData.push_back(newColData);
	}
	// ���f���̓ǂݍ��ݏ���
	// �����R�s�[���Ďg�p���邽�ߍŏ��Ɉ�����ǂݍ���
	m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, 0, 0));
	m_pObject.back()->Init();
	int fieldHandle = m_pObject.back()->GetModelHandle();
	for (int i = 0; i < m_dataColNum; i++)
	{
		for (int j = 0; j < m_dataRowNum; j++)
		{
			if (m_currentData[i][j] == Field)
			{
				// �������̂̓R�s�[���Ďg��
				// �u���b�N�̏���������
				m_pObject.push_back(std::make_shared<GameObject>(fieldHandle, Field, j, i));
				//m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, j, i));
				m_pObject.back()->Init();
			}
			if (m_currentData[i][j] == Flag)
			{
				// �R�c���f���̓ǂݍ���
				// �t���O�̏���������
				m_pObject.push_back(std::make_shared<GameObject>(kFlagHandle, Flag, j, i));
				m_pObject.back()->Init();
			}

			// �I�u�W�F�N�g�̉��̍ő�l���擾���邽�߂̏���
			// ���̐��l���傫�������琔�l��������
			if (m_objectPosX < m_pObject.back()->GetPosX())
			{
				m_objectPosX = m_pObject.back()->GetPosX();
			}
		}
	}
	// �G���h���X����Ȃ�������~�j�}�b�v��\��������
	if (m_selectNum != Endless)
	{
		m_pCurrentMap = new CurrentPlayerMap(m_objectPosX);
	}
}

/// <summary>
/// �X�V
/// </summary>
void Map::Update()
{
	// �X�V����
	for (const auto& obj : m_pObject)
	{
		obj->Update();
		// �����蔻��̏��
		MV1SetupCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex());
	}

	// �s�K�v�ȃI�u�W�F�N�g�̍폜����
	for (int i = 0; i < m_pObject.size() - 1; i++)
	{
		if (!m_pObject[i]->IsExist())
		{
			// ���݂��Ă��Ȃ�������v�f���폜
			m_pObject.erase(m_pObject.begin() + i);
			// �̈���R���e�i�̃T�C�Y�܂Ő؂�l�߂�
			m_pObject.shrink_to_fit();
		}
	}
	// ������ʊO�Ɍ�������Q�[���N���A����ɂ���
	if (m_pObject.size() <= m_max)
	{
		m_gameClearFlag = true;
	}
	// endless�̏���
	if (m_selectNum == Endless && m_pObject[m_pObject.size() - 1]->IsDrawFlag())
	{
		SelectEndless();
	}
	// �����N���X�̒��g���󂶂�Ȃ������珈��������
	if (m_pCurrentMap)
	{
		m_pCurrentMap->Update();
	}
	//printfDx("%d\n", m_pObject.size());
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	// �`�揈��
	for (const auto& obj : m_pObject)
	{
		obj->Draw();
	}
	// �����N���X�̒��g���󂶂�Ȃ������珈��������
	if (m_pCurrentMap)
	{
		m_pCurrentMap->Draw();
	}
}

void Map::SelectEndless()
{
	int random = GetRand(m_maxRand);
	//printfDx("%d\n", random);
	switch (random)
	{
	case 0:
		m_pStage->Load("Data/Map/Random1.fmf");
		break;
	case 1:
		m_pStage->Load("Data/Map/Random2.fmf");
		break;
	case 2:
		m_pStage->Load("Data/Map/Random3.fmf");
		break;
	case 3:
		m_pStage->Load("Data/Map/Random4.fmf");
		break;
	default:
		m_pStage->Load("Data/Map/Random1.fmf");
		break;
	}
	Load();
}

void Map::CollisionDetection(Player* player)
{
	// �v���C���[�̈ʒu�A�����蔻��͈̔͂�n��
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
	MV1_COLL_RESULT_POLY_DIM result;// ������f�[�^

	for (const auto& obj : m_pObject)
	{
		result = MV1CollCheck_Capsule(obj->GetModelHandle(), obj->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (obj->GameObjectNum() == Field)
		{
			if (!m_gameClearFlag)
			{
				if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
				{
					player->IsExistPlayer(true);
					player->PlayerDropPoint(static_cast<int>(result.Dim[1].Position[1].y));
				}
			}
		}
		else if (obj->GameObjectNum() == Flag)
		{
			if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
			{
				m_gameClearFlag = true;
			}
		}
		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
}