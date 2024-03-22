#include "Stage9.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];

	constexpr int kIndexX = 6;
	constexpr int kIndexY = 8;
}


Stage9::Stage9()
{
	int Stage[Field::kFieldY][Field::kFieldX] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0},
		{0,0,0,0,0,0,2,2,2,2,2,3,1,1,1,2,0,0,0,0},
		{0,0,0,0,0,0,2,1,1,2,3,3,2,2,1,2,0,0,0,0},
		{0,0,0,0,0,0,2,1,1,4,3,3,1,1,1,2,0,0,0,0},
		{0,0,0,0,0,0,2,1,1,2,1,3,2,1,2,2,0,0,0,0},
		{0,0,0,0,0,2,2,2,1,2,2,4,2,1,1,2,0,0,0,0},
		{0,0,0,0,0,2,1,4,1,1,1,1,4,4,1,2,0,0,0,0},
		{0,0,0,0,0,2,1,2,4,2,1,1,2,1,1,2,0,0,0,0},
		{0,0,0,0,0,2,1,1,1,2,2,2,2,2,2,2,0,0,0,0},
		{0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};


	for (int x = 0; x < Field::kFieldX; x++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
	{
		for (int y = 0; y < Field::kFieldY; y++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
		{
			kStage[y][x] = Stage[y][x];
		}
	}


	FieldInit();
}

void Stage9::FieldInit()
{
	m_Information->FieldInfo(kStage);
	m_Information->PlayerInfo(kIndexX, kIndexY);
}
