#pragma once
#include "../Base/MoveTypeBase.h"

class KinnikuMuscle : public MoveTypeBase
{
public:
	void Update(int& imagePosX, int& imagePosY);// 更新

	bool IsAttackColMuscle() { return m_isAttackCol; }// 攻撃判定のタイミング

	// 攻撃判定があるかどうか
	bool m_isAttackCol = false;
private:

	int m_nextCount = 0;
};

