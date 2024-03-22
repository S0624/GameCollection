#pragma once
#include"../Scene/SceneBase.h"
#include"../UI/InputState.h"
class SoundSettingScene : public SceneBase
{
private:
	int m_waitInterval = 60;	//値が変化するインターバル
	int m_pressTimer = 0;		//押しっぱなしの時間

public:
	SoundSettingScene(SceneManager& manager);
	~SoundSettingScene(){}
	void Update(const InputState& input);
	void Draw();
};

