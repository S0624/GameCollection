#pragma once
#include<vector>

using MapData = std::vector<std::vector<unsigned char>>;
class MapChip
{
private:
	struct ChipData
	{
		uint8_t m_id[4];	// 識別子(FMF_)
		uint32_t m_size;// データサイズ
		uint32_t m_mapWidth;// マップの幅
		uint32_t m_mapHeight;// マップの高さ
		uint8_t  m_chipWidth;// チップ(セル1個)の幅
		uint8_t  m_chipHeight;// チップ(セル1個)の高さ
		uint8_t  m_layerCount;// レイヤー数
		uint8_t  m_bitCount;// 1セル当たりのビット数(÷8バイト数)
	};

	MapData m_mapData;
	int m_mapWidth = 0;
	int m_mapHeight = 0;	
private:
	/// <summary>
	/// データの内容をXY転置する
	/// </summary>
	/// <param name="layerId">レイヤーID</param>
	void TransposeMapData(int layerId);
public:
	void Load(const wchar_t* filePath);
	const MapData& GetMapData()const;
	const int GetChipId(int layerId, int chipX, int chipY)const;
	void GetMapSize(int& width, int& height);

};

