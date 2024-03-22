#include "DinosaurMove.h"
#include "DinosaurStateBase.h"
#include <DxLib.h>
#include "DinosaurIdle.h"
#include"DinosaurJump.h"
#include"DinosaurAttackBite.h"
#include"DinosaurAttackPounce.h"
#include"DinosaurAttackScratch.h"
#include"DinosaurAttackShot.h"
#include"DinosaurDead.h"

namespace
{
	constexpr float kMoveSpeed = 10.0f;
}


DinosaurMove::~DinosaurMove()
{
}

void DinosaurMove::IsMove(int padNum)
{
	m_vec.x = 0;
	if (Pad::IsPress(PAD_INPUT_LEFT, padNum))// XBOX X or Y
	{
		m_vec.x = -kMoveSpeed;
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT, padNum))
	{
		m_vec.x = kMoveSpeed;
	}
}

DinosaurStateBase* DinosaurMove::Update(int padNum)
{
	ChangeGraph(3, 6, true);

	IsMove(padNum);

	if (m_deadFlag)
	{
		return new DinosaurDead( {0,0});
	}

	//if (Pad::IsPress(PAD_INPUT_UP, padNum))// XBOX X or Y
	//{
	//	return new DinosaurJump(m_Pos,m_Vec);
	//}

	if (Pad::IsPress(PAD_INPUT_UP, padNum))// XBOX A
	{
		return new DinosaurJump(m_vec);
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

	if (m_vec.x != 0)	// キャラクターが動いているとき
	{
		return this;
	}

	return new DinosaurIdle(m_vec);
}
