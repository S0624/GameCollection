#pragma once
#include "../Common.h"
#include <vector>

/// <summary>
/// �X�e�[�W��ǂݍ��ރN���X
/// </summary>
enum class LayerType {
	BackGround,//�w�i
};

//�}�b�v�̍L�� * ���C���[���Ȃ̂ŁA2�̃x�N�^�[�����q�ɂ��Ă�
using MapData_t = std::vector < std::vector<unsigned char>>;

//�X�e�[�W�����Ǘ�����N���X
class Stage
{
public:
	void Load(const TCHAR* filePath);
	const MapData_t& GetMapData()const;
	const int GetChipId(int layerId,int chipX,int chipY)const;
	void GetMapSize(int& width,int& height);
private:
	/// <summary>
	/// �f�[�^�̓��e��XY�]�u����
	/// </summary>
	/// <param name="layerId">���C���[ID</param>
	void TransposeMapData(int layerId);
private:

	MapData_t m_mapData;
	int m_mapWidth = 0;
	int m_mapHeight = 0;
};

