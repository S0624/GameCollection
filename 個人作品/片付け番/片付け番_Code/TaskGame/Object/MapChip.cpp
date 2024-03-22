#include "MapChip.h"
#include"DxLib.h"
#include<string>
#include<cassert>

void MapChip::TransposeMapData(int layerId)
{
	auto temp = m_mapData[layerId];	//いったんコピーしておく
//理由としてはコピーせずに転置しようとすると元のデータが消える	

	for (int Y = 0; Y < m_mapHeight; ++Y)
	{
		for (int X = 0; X < m_mapWidth; ++X)
		{
			//通常のXY指定の場合
			//Y * mapWidth_ + X という風になる。
			//さらに、横200縦15は維持する必要がある
			//縦に並べていきたい
			//０の隣は1段下にしたい	
			int idxSrc = Y * m_mapWidth + X;		//Source Index
			int idxDst = Y + m_mapHeight * X;	//Destination Index
			m_mapData[layerId][idxDst] = temp[idxSrc];

		}
	}
}

void MapChip::Load(const wchar_t* filepath)
{
	ChipData chip;
	int handle = FileRead_open(filepath);
	FileRead_read(&chip, sizeof(chip), handle);

	m_mapWidth = chip.m_mapWidth;
	m_mapHeight = chip.m_mapHeight;
	int layerCount = chip.m_layerCount;		// レイヤー1個当たりのサイズを計算する
	// マップの幅*マップの高さ*(チップ1個当たりのバイト数)
	int layerDataSize = chip.m_mapWidth * chip.m_mapHeight * (chip.m_bitCount / 8);
	m_mapData.resize(layerCount);
	for (auto& layer : m_mapData)
	{
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}
	FileRead_close(handle);
}

const MapData& MapChip::GetMapData() const
{
	return m_mapData;
}

const int MapChip::GetChipId(int layerId, int chipX, int chipY) const
{
	auto address = chipY * m_mapWidth + chipX;
	return m_mapData[layerId][address];
}

void MapChip::GetMapSize(int& width, int& height)
{
	width = m_mapWidth;
	height = m_mapHeight;
}
