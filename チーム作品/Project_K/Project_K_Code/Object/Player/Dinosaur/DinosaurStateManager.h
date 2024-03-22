#pragma once
#include <DxLib.h>
#include"DinosaurStateBase.h"
#include"../../Util/Vec2.h"
#include "../../Util/Pad.h"

class DinosaurStateManager
{
public:
	DinosaurStateManager(int Handle);
	virtual ~DinosaurStateManager() {}
	// 初期化
	void Init();
	// 終了
	void End();
	// 毎フレームの処理
	void Update(int padNum);
	// 描画
	void Draw(Vec2 pos, int size);

	bool GetshotFlag(); // ショットを撃つとき

	Vec2 GetVec();

	bool GetAttackFlag();

	int GetAttackSizeLeft();
	int GetAttackSizeTop();
	int GetAttackSizeRight();
	int GetAttackSizeBottom();

	bool GetLookLeft() { return m_lookLeft; }

	int GetOnDamage();

	void SetAttackFlag();

	void SetondamageFlag(bool ondamageFlag) { m_ondamageFlag = ondamageFlag; }

	//死んだときm_deadFlagをtrueに
	void SetDeadFlag() { m_deadFlag = true; }
	bool m_lookLeft; // 左を向いているかどうか

private:
	int m_handle;


	bool m_deadFlag = false; //死んでいるかどうか

	bool m_ondamageFlag = false; //攻撃を食らっているとき

	// シーンベースポインタ
	DinosaurStateBase* m_pState;
};

