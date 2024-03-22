#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include "../Util/Vec2.h"

class LogoRotation;
class UIAnimation;
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	LogoRotation* m_pLogo;
	UIAnimation* m_pUiAnim;
};

