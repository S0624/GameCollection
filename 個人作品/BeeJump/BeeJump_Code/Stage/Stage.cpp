#include "Stage.h"
#include <string>
#include <cassert>

void Stage::Load(const TCHAR* filePath)
{
	//FMF�w�b�_�[(Platinum�̃h�L�������g�ɏ����Ă���)
	struct Header {
		int8_t id[4];			//���ʎq(FMF_)			1*4�o�C�g
		uint32_t size;			//�f�[�^�T�C�Y�@		4�o�C�g
		uint32_t mapWidth;		//�}�b�v�̕�			4�o�C�g
		uint32_t mapHeight;		//�}�b�v�̍����@		4�o�C�g
		uint8_t chiphWidth;		//�`�b�v(�Z�����)�̕�					1�o�C�g
		uint8_t chpHeight;		//�`�b�v(�Z�����)�̍���				1�o�C�g
		uint8_t layerCount;		//���C���[�̐�							1�o�C�g
		uint8_t bitCount;		//�P�Z��������̃r�b�g��(��8�Ńo�C�g��)	1�o�C�g
	};//20�o�C�g

	Header header;
	int handle =  FileRead_open(filePath);
	FileRead_read(&header,sizeof(header), handle);

	std::string strId;
	strId.resize(4);
	std::copy_n(header.id, 4, strId.begin());

	if (strId != "FMF_") {
		assert(0);
	}

	m_mapWidth = header.mapWidth;
	m_mapHeight = header.mapHeight;
	int layerCount = header.layerCount;
	//���C���[1������̃T�C�Y���v�Z����
	//�}�b�v�̕����}�b�v�̍���*(�`�b�v1������̃o�C�g��)
	int layerDataSize = header.mapWidth * header.mapHeight * (header.bitCount / 8);

	m_mapData.resize(layerCount);
	for (auto& layer : m_mapData) {
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}

	FileRead_close(handle);

	//���s������������t���̂��߂ɁA�f�[�^�����H
	for (int layerIdx = 0; layerIdx < layerCount; ++layerIdx) {
		TransposeMapData(layerIdx);
	}

}

const MapData_t& Stage::GetMapData() const
{
	return m_mapData;
}

const int Stage::GetChipId(int layerId, int chipX, int chipY) const
{
	assert(chipX < m_mapWidth);
	assert(chipY < m_mapHeight);
	auto index = chipY + chipX * m_mapHeight;
	return m_mapData[layerId][index];
}

void Stage::GetMapSize(int& width, int& height)
{
	width = m_mapWidth;
	height = m_mapHeight;
}

void Stage::TransposeMapData(int layerId)
{

	auto temp = m_mapData[layerId];//��������R�s�[���Ă���
	for (int Y = 0; Y < m_mapHeight; ++Y) {
		for (int X = 0; X < m_mapWidth; ++X) {
			//�ʏ��XY�w��̏ꍇ
			//Y*mapwidht_+x�Ƃ������ɂȂ�
			//����ɁA��200�c15�͈ێ�����K�v������B
			//�c�ɕ��ׂĂ�������
			//0�ׂ̗�1�i���ɂ�����
			int idxSrc = Y * m_mapWidth + X;	//Source Index
			int idxDst = Y + m_mapHeight * X;	//Destination Index

			//int idxSrc = Y * mapWidth_ + X;	//Source Index
			//int idxDst = Y + mapHeight_ * X;	//Destination Index
			m_mapData[layerId][idxDst] = temp[idxSrc];
		}
	}

}
