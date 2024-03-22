#include "DinosaurIdle.h"
#include "../Base/PlayerBase.h"
#include "DinosaurAttackScratch.h"
#include "DinosaurAttackPounce.h"
#include "DinosaurAttackShot.h"
#include "DinosaurAttackBite.h"
#include"DinosaurDead.h"
#include"DinosaurJump.h"
#include"DinosaurMove.h"

DinosaurIdle::~DinosaurIdle()
{
}

DinosaurStateBase* DinosaurIdle::Update(int padNum)
{
	m_vec.x = 0;

	ChangeGraph(3, 9 , true);

	if (m_deadFlag)
	{
		return new DinosaurDead({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_LEFT,padNum) || (Pad::IsPress(PAD_INPUT_RIGHT, padNum)))// XBOX X or Y
	{
		return new DinosaurMove({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_UP, padNum))// XBOX A
	{
		return new DinosaurJump({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_2, padNum))// XBOX B
	{
		return new DinosaurAttackBite({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_3, padNum))// XBOX X or Y
	{
		return new DinosaurAttackScratch({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_4, padNum))// XBOX X or Y
	{
		return new DinosaurAttackShot({ 0,0 });
	}
	if (Pad::IsPress(PAD_INPUT_1, padNum))// XBOX X or Y
	{
		return new DinosaurAttackPounce({ 0,0 }, m_lookLeft);
	}

	return this;
}
