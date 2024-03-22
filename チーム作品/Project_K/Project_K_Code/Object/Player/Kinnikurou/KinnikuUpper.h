#pragma once
#include "../Base/MoveTypeBase.h"

class KinnikuUpper : public MoveTypeBase
{
public:
	void Update(int& imagePosX, int& imagePosY);// 更新

	bool IsAttackColUpper() { return m_isAttackCol; }// 攻撃判定のタイミング

	bool m_isAttackCol = false;
private:
};

