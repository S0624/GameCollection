#pragma once
#include "SceneBase.h"
#include"../Common.h"

class SceneDebug :
	public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	int m_cursolNum;
	int m_max;
};