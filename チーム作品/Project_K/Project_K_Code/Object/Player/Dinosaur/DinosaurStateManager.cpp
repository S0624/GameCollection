#include "DinosaurStateManager.h"
#include <cassert>
#include "DinosaurAttackBite.h"
#include "DinosaurAttackPounce.h"
#include "DinosaurAttackScratch.h"
#include "DinosaurAttackShot.h"
#include "DinosaurIdle.h"
#include "DinosaurJump.h"
#include "DinosaurMove.h"
#include "DinosaurIdle.h"


DinosaurStateManager::DinosaurStateManager(int Handle) :
	m_handle(Handle),
	m_pState(nullptr)
{
}
// 初期化
void DinosaurStateManager::Init()
{
	m_pState = new DinosaurIdle({ 0,0 });
	m_deadFlag = false;
}
// 終了
void DinosaurStateManager::End()
{
	assert(m_pState);// 確認処理
	if (!m_pState)	return;

	//m_pAttack->End();// 終了処理
	//delete m_pScene;
}
// 毎フレームの処理
void DinosaurStateManager::Update(int padNum)
{
	

	if (m_deadFlag)
	{
		m_pState->SetDeadFlag();
	}
	if (Pad::IsPress(PAD_INPUT_LEFT, padNum) && !m_pState->GetAttackMotion())// XBOX X or Y
	{
		m_lookLeft = true;
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT, padNum) && !m_pState->GetAttackMotion())// XBOX X or Y
	{
		m_lookLeft = false;
	}
	assert(m_pState);// 確認処理
	if (!m_pState)	return;

	m_pState->SetLookFlag(m_lookLeft);
	DinosaurStateBase* pState = m_pState->Update(padNum);// AttackBaseのupdate処理呼び出し

	if (m_ondamageFlag)
	{
		pState = new DinosaurIdle({ 0,0 });
	}

	if (pState != m_pState)
	{
		//	m_pState->End();// 終了処理
		delete m_pState;

		m_pState = pState;
		m_pState->Init(m_handle);// 初期化
	}
}
// 描画
void DinosaurStateManager::Draw(Vec2 pos,int size)
{
	assert(m_pState);
	if (!m_pState)	return;
	m_pState->Draw(m_handle, m_lookLeft, pos, size);// 描画
}

bool DinosaurStateManager::GetshotFlag()
{
	return m_pState->GetshotFlag();
}

Vec2 DinosaurStateManager::GetVec()
{
	return m_pState->GetVec();
}

bool DinosaurStateManager::GetAttackFlag()
{
	return m_pState->GetAttackFlag();
}

int DinosaurStateManager::GetAttackSizeLeft()
{

	return ((m_lookLeft) ? m_pState->GetAttackSizeLeft() : -m_pState->GetAttackSizeRight());
}

int DinosaurStateManager::GetAttackSizeTop()
{
	return m_pState->GetAttackSizeTop();
}

int DinosaurStateManager::GetAttackSizeRight()
{
	return ((m_lookLeft) ? m_pState->GetAttackSizeRight() : -m_pState->GetAttackSizeLeft());
}

int DinosaurStateManager::GetAttackSizeBottom()
{
	return m_pState->GetAttackSizeBottom();
}

int DinosaurStateManager::GetOnDamage()
{
	return m_pState->GetAttackDamage();
}

void DinosaurStateManager::SetAttackFlag()
{
	m_pState->SetAttackFlag(false);
}
