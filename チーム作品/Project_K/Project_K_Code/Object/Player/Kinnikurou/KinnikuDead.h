#pragma once
#include "../Base/MoveTypeBase.h"

class KinnikuDead : public MoveTypeBase
{
public:
	void Update(int& imagePosX, int& imagePosY);// 更新
private:
	int m_nextCount = 5;// 次のモーションに移行する時間
};

