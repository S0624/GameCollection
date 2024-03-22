#include "CharaChoice.h"
#include"../Util/Pad.h"

CharaChoice::CharaChoice() :
	m_charaNumber1(0),
	m_charaNumber2(0),
	m_decision1(false),
	m_decision2(false)
{
}

CharaChoice::~CharaChoice()
{
}

void CharaChoice::Init()
{

}

void CharaChoice::Update()
{
	updateChara1(); //パッド1のアップデート
	updateChara2(); //パッド2のアップデート
}

void CharaChoice::Draw()
{
	if (m_decision1) //キャラクターが決定されたとき赤文字で表示
	{
		DrawDecision1P(0xff0000);
	}
	else //決定されてないとき白文字で表示
	{
		DrawDecision1P(0xffffff);
	}

	if (m_decision2)//キャラクターが決定されたとき赤文字で表示
	{
		DrawDecision2P(0xff0000);
	}
	else //決定されてないとき白文字で表示
	{
		DrawDecision2P(0xffffff);
	}
}


void CharaChoice::updateChara1()
{
	//キャラクターが決定されていてかつ2ボタンを押された場合
	UpdateChara(1, m_charaNumber1, m_decision1);

}

void CharaChoice::updateChara2()
{
	//キャラクターが決定されていてかつ2ボタンを押された場合
	UpdateChara(2, m_charaNumber2, m_decision2);
}

void CharaChoice::UpdateChara(int padNum, int& charaNum, bool& decision)
{
	//キャラクターが決定されていてかつ2ボタンを押された場合
	if (Pad::IsTrigger(PAD_INPUT_1, padNum) && decision)
	{
		decision = false;
		return;
	}

	if (decision) return; //キャラクターが決定されていたら処理をしない

	if (Pad::IsTrigger(PAD_INPUT_1, padNum) && !decision)
	{
		decision = true;
		return;
	}
	if (Pad::IsTrigger(PAD_INPUT_DOWN, padNum))
	{
		if (charaNum >= 3)
		{
			charaNum = 0;
			return;
		}
		charaNum++;
	}

	if (Pad::IsTrigger(PAD_INPUT_UP, padNum))
	{
		if (charaNum <= 0)
		{
			charaNum = 3;
			return;
		}
		charaNum--;
	}
}

void CharaChoice::DrawDecision1P(int color)
{
	//DrawFormatString(300, 400, color,
	//	"%d", m_charaNumber1);
}

void CharaChoice::DrawDecision2P(int color)
{
	//DrawFormatString(600, 400, color,
	//	"%d", m_charaNumber2);
}