#include"CreateEffect.h"
#include"ClearEffect.h"
#include "DxLib.h"
#include"../UI/game.h"
#include"../GameManager.h"
#include"../SoundManager.h"

namespace
{
	constexpr int kHandleIndex = 480;
}
void CreateEffect::AnimationUpdate()
{
	m_testFrame++;
	if (m_testFrame > 2)
	{
		m_animeNumX++;
		if (m_animeNumX >= 5)
		{
			m_animeNumY++;
			m_animeNumX = 0;
		}
		if (m_animeNumY >= 6)
		{
			m_animeNumY = 0;
			m_startPosY = GetRand(600) + 200;	//位置をランダムに生成する
			if (m_startPosX == 200)
			{
				m_startPosX = 1200;
			}
			else
			{
				m_startPosX = 200;
			}
		}
		if (m_animeNumX == 1 && m_animeNumY == 3)
		{
			// エフェクトの効果音を鳴らす
			SoundManager::GetInstance().Play(L"fireflower");
		}
		m_testFrame = 0;
	}
}
CreateEffect::CreateEffect()
{
	for (auto& clear : m_pClear)
	{
		clear = std::make_shared<ClearEffect>();
	}
	// 花火の画像
	m_handle = my::MyLoadGraph(L"../Date/Clear.png");

}

CreateEffect::~CreateEffect()
{
	DeleteGraph(m_handle);
}

void CreateEffect::Update()
{
	for (auto& clear : m_pClear)
	{
		if (!clear->IsExist())	continue;
		clear->Update();
	}

	m_flowerFrame--;

	if (m_flowerFrame <= 0)
	{
		int count = 0;
		// 発生位置から上に飛んで落ちていく
		for (auto& clear : m_pClear)
		{
			if (clear->IsExist())	continue;

			float randSin = static_cast<float>(GetRand(360)) / 360.0f;
			randSin *= DX_TWO_PI_F;
			float randSpeed = static_cast<float>(GetRand(160)) / 10.0f + 1.0f;

			Vec2 pos;
			pos.x = m_startPosX + cosf(randSin) * 2.0f;
			pos.y = m_startPosY + sinf(randSin) * 2.0f;

			Vec2 vec;
			vec.x = cosf(randSin) * randSpeed;
			vec.y = sinf(randSin) * randSpeed;

			clear->StartPos(pos);
			clear->SetVec(vec);
			clear->SetRadius(2.0f);
			clear->SetColor(0xff2020);
			clear->SetGravity(0.4f);

		}
		m_flowerFrame = m_flowerInterval;
	}
}

void CreateEffect::Draw()
{
	AnimationUpdate();

	my::MyDrawRectRotaGraph(m_startPosX, m_startPosY,			//表示座標
		kHandleIndex * m_animeNumX, kHandleIndex * m_animeNumY,			//切り取り左上
		kHandleIndex, kHandleIndex,							//幅、高さ
		0.5f, 0.0f,						//拡大率、回転角度
		m_handle, true);
}