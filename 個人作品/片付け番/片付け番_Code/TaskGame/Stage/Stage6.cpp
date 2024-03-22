#include "Stage6.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];

	constexpr int kIndexX = 14;
	constexpr int kIndexY = 5;
}


Stage6::Stage6()
{
	int Stage[Field::kFieldY][Field::kFieldX] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,2,1,1,1,1,2,0,0,0,0,0},
		{0,0,0,0,0,0,2,2,3,1,4,2,2,1,2,2,0,0,0,0},
		{0,0,0,0,0,0,2,3,3,4,1,4,1,1,1,2,0,0,0,0},
		{0,0,0,0,0,0,2,3,3,1,4,1,4,1,2,2,0,0,0,0},
		{0,0,0,0,0,0,2,2,2,2,2,2,1,1,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};


	for (int x = 0; x < Field::kFieldX; x++)		//仮で壁の追加
	{
		for (int y = 0; y < Field::kFieldY; y++)		//仮で壁の追加
		{
			kStage[y][x] = Stage[y][x];
		}
	}


	FieldInit();
}

void Stage6::FieldInit()
{
	m_Information->FieldInfo(kStage);
	m_Information->PlayerInfo(kIndexX, kIndexY);
}
