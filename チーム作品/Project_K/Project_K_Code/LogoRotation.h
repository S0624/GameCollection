#pragma once

#include "Util/Vec2.h"

class LogoRotation
{
public:
	LogoRotation();
	virtual ~LogoRotation();

	void Init();
	void Update();
	void Draw();

	inline int test(int x);
	int test2(int x);
private:
	// 
	int m_hLogo;
	
	Vec2 m_pos;
	Vec2 m_logoPos;

	int m_box = 0;
	int m_box2 = 0;
	int m_x, m_y;

	bool m_isTrans;

	int width, height;

	float m_size = 0.0f;
	float m_rota = 0.0f;
};

