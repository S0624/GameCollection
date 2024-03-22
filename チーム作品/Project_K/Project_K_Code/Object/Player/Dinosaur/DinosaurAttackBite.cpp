#include "DinosaurAttackBite.h"
#include"DinosaurIdle.h"


namespace
{
	//画像が入れ替わるスピード
	constexpr int kGraphSpeed = 4;
	//画像の最大数
	constexpr int kGraphSize = 10;
	//画像の再生を止める
	constexpr int kStopGraph = 4;
	//攻撃硬直時間
	constexpr int kAttackStan = 10;

	
	constexpr int kAttackFlagOn = 3;//攻撃フラグがOnになるタイミング

	constexpr int kAttackFlagOff = 10;//攻撃フラグがOffになるタイミング
	
}

DinosaurAttackBite::~DinosaurAttackBite()
{
}

DinosaurStateBase* DinosaurAttackBite::Update(int padNum)
{
	m_attackFrame++;

	if (m_attackFrame == kAttackFlagOn)
	{
		m_attackFlag = true;
	}

	if (m_attackFrame == kAttackFlagOff)
	{
		m_attackFlag = false;
	}

	if (m_imagePosX < kStopGraph)
	{
		ChangeGraph(kGraphSpeed, kGraphSize, false);
	}
	else
	{
		m_imagePosX = kStopGraph;
		m_gapTime++;
	}

	if (m_gapTime > kAttackStan)
	{
		return new DinosaurIdle(m_vec);
	}


	return this;
}
