#pragma once
#pragma once
#include<vector>

class Field;
class Player;

class Stage1;
class Stage2;
class Stage3;
class Stage4;
class Stage5;
class Stage6;
class Stage7;
class Stage8;
class Stage9;
class Stage10;

class FieldInformation
{
private:
	Field* m_pField;
	Player* m_pPlayer;
	Stage1* m_pStage1;
	Stage2* m_pStage2;
	Stage3* m_pStage3;
	Stage4* m_pStage4;
	Stage5* m_pStage5;
	Stage6* m_pStage6;
	Stage7* m_pStage7;
	Stage8* m_pStage8;
	Stage9* m_pStage9;
	Stage10* m_pStage10;

private:

	int m_limit = 100;
	int m_stageNum = 0;

public:
	FieldInformation();
	~FieldInformation();

	//int Num(int num);
	void StageNum(int num);

	void SetField(Field* pField) { m_pField = pField; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void FieldInfo(int field[10][20]);

	void PlayerInfo(int x, int y);

	void Init();
	void FieldInit();

	int StepLimit();
};