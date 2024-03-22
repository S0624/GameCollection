#include "DinosaurDead.h"

DinosaurDead::~DinosaurDead()
{
}

DinosaurStateBase* DinosaurDead::Update(int padNum)
{
	if (m_imagePosX < 5)
	{
		ChangeGraph(5, 10, false);
	}

	return this;
}
