#pragma once
#include "../Base/MoveTypeBase.h"

class KinnikurouJab : public MoveTypeBase
{
public:
	void Update(int& imagePosX, int& imagePosY);// 更新

	bool IsAttackColJab() { return m_isAttackCol; }// 攻撃判定のタイミング

	bool m_isAttackCol = false;
private:
};

