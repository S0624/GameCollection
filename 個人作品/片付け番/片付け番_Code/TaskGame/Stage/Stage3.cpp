#include "Stage3.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];
	
	constexpr int kIndexX = 8;
	constexpr int kIndexY = 3;
}


Stage3::Stage3()
{
	int Stage[Field::kFieldY][Field::kFieldX] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,1,1,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,1,4,1,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,4,1,2,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,1,4,1,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,3,4,1,1,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,3,3,5,3,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

void Stage3::FieldInit()
{
	m_Information->FieldInfo(kStage);
	m_Information->PlayerInfo(kIndexX, kIndexY);
}

