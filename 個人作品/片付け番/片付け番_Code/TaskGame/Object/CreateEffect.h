#pragma once
#include <array>
#include <memory>
class ClearEffect;

class CreateEffect
{
private:
	int m_particleNum = 4096;
	int m_showerInterval = 2;
	int m_flowerInterval = 120;
	int m_auraInterval = 2;

	int m_handle = 0;

	float m_sinRate = 0.0f;
	int m_showerFrame = m_showerInterval;
	int m_flowerFrame = m_flowerInterval;
	int m_auraFrame = m_auraInterval;

	int m_startPosX = 200;
	int m_startPosY = 200;

	int m_animeNumX = 4;
	int m_animeNumY = 5;

	int m_testFrame = 0;
private:
	std::array<std::shared_ptr<ClearEffect>, 10> m_pClear;
	void AnimationUpdate();
public:
	CreateEffect();
	~CreateEffect();

	void Update();
	void Draw();
};

