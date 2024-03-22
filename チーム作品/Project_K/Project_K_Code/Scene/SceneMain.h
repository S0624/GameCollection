#pragma once
#include "SceneBase.h"
#include "../Util/Vec2.h"

#include <fstream>
#include <string>
#include <vector>
#include <memory>

class StageBase;		// ステージ
class SceneBase;
class PlayerBase;
class Collision;
class UI;			// UI

class SceneMain : public SceneBase
{
public:
	SceneMain(PlayerBase* Player1, PlayerBase* Player2, int StageNo);
	virtual ~SceneMain();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	StageBase* m_pStageBase;	// ステージセレクトシーン
	void UpdateCountDown(); //試合開始前のカウント
	void UpdateMain();//試合開始
	void UpdateDead();//片方が死んだらまたは時間切れになったら
private:
	PlayerBase* m_pPlayer[2];
	Collision* m_pColl;
	UI* m_pUi;

	bool m_isVictory1P;// 1Pの勝敗
	bool m_isVictory2P;// 2Pの勝敗

	void (SceneMain::*m_updateFunc)();// Updateのメンバ関数ポインタ


	int m_countDown; //�J�E���g�_�E��


	int m_font;// フォントハンドル

	int m_timeUpDrawCount;// TIME OUT描画時間

};


	