#pragma once
#include "SceneBase.h"

class CharaChoice;
class PlayerBase;
class SelectUI;

class SceneCharacterSelect : public SceneBase
{
public:
	SceneCharacterSelect(int StageNo);
	virtual ~SceneCharacterSelect();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:

	int m_stageNo;	// ステージの番号

	PlayerBase* m_Player[2];

	CharaChoice* m_CharaChoice;
	SelectUI* m_pUi;
};