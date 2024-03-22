#include "Stage.h"
#include <string>
#include <cassert>

void Stage::Load(const TCHAR* filePath)
{
	//FMFヘッダー(Platinumのドキュメントに書いてある)
	struct Header {
		int8_t id[4];			//識別子(FMF_)			1*4バイト
		uint32_t size;			//データサイズ　		4バイト
		uint32_t mapWidth;		//マップの幅			4バイト
		uint32_t mapHeight;		//マップの高さ　		4バイト
		uint8_t chiphWidth;		//チップ(セル一個)の幅					1バイト
		uint8_t chpHeight;		//チップ(セル一個)の高さ				1バイト
		uint8_t layerCount;		//レイヤーの数							1バイト
		uint8_t bitCount;		//１セル当たりのビット数(÷8でバイト数)	1バイト
	};//20バイト

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
	//レイヤー1個当たりのサイズを計算する
	//マップの幅＊マップの高さ*(チップ1個当たりのバイト数)
	int layerDataSize = header.mapWidth * header.mapHeight * (header.bitCount / 8);

	m_mapData.resize(layerCount);
	for (auto& layer : m_mapData) {
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}

	FileRead_close(handle);

	//実行時メモリ小売t化のために、データを加工
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

	auto temp = m_mapData[layerId];//いったんコピーしておく
	for (int Y = 0; Y < m_mapHeight; ++Y) {
		for (int X = 0; X < m_mapWidth; ++X) {
			//通常のXY指定の場合
			//Y*mapwidht_+xという風になる
			//さらに、横200縦15は維持する必要がある。
			//縦に並べていきたい
			//0の隣は1段下にしたい
			int idxSrc = Y * m_mapWidth + X;	//Source Index
			int idxDst = Y + m_mapHeight * X;	//Destination Index

			//int idxSrc = Y * mapWidth_ + X;	//Source Index
			//int idxDst = Y + mapHeight_ * X;	//Destination Index
			m_mapData[layerId][idxDst] = temp[idxSrc];
		}
	}

}
