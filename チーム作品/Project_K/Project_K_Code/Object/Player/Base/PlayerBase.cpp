#include "PlayerBase.h"
#include "../../Shot/NullShot.h"
#include"../../../Util/game.h"

namespace
{
	constexpr float kAccX = 0.5f; //X軸のノックバック減少量
	constexpr float kAccY = 1.0f;//Y軸のノックバック減少量

	constexpr float kKnockBackX = 8.0f;//X軸のノックバック量
	constexpr float kKnockBackY = -5.0f;//Y軸のノックバック量
}

PlayerBase::PlayerBase()
{
	//ショットを初期化
	for (int i = 0; i < kShotMax; i++)
	{
		m_pShot[i] = new NullShot();
	}
}

//ノックバックセット
void PlayerBase::SetKnockBack(float toPlayer)//プレイヤー同士の位置
{
	// 敵プレイヤーが左側にいるとき
	if (toPlayer < 0.0f)
	{
		m_knockBack = { kKnockBackX ,kKnockBackY };
	}
	// 敵プレイヤーが右側にいるとき
	if (toPlayer >= 0.0f)
	{
		m_knockBack = { -kKnockBackX ,kKnockBackY };
	}
}

void PlayerBase::DebugDrawCollision()
{
	if (m_attackFlag)
	{
		DrawBox(static_cast<int> (m_pos.x) + m_attackSizeLeft,
			static_cast<int> (m_pos.y) + m_attackSizeTop,
			static_cast<int> (m_pos.x) + m_attackSizeRight,
			static_cast<int> (m_pos.y) + m_attackSizeBottom,
			0xff0000, false);
	}
	
}

//ノックバック処理
void PlayerBase::KnockBack()
{
	//m_onDamageFrameが0になるまで何もしない
	if (m_onDamageFrame > 0)
	{
		m_onDamageFrame-=2;
		damageMove();
	}
}

void PlayerBase::CharDefaultPos(bool& direction)
{
	if (m_padNum == 1)
	{
		m_pos.x = 500.0f;
		m_pos.y = 600.0f;
		direction = false;
	}
	else if (m_padNum == 2)
	{
		m_pos.x = 1400.0f;
		m_pos.y = 600.0f;
		direction = true;
	}
}

//攻撃を食らった時の動き
void PlayerBase::damageMove()
{
	m_pos += m_knockBack;

	m_knockBack.x = min(max(m_knockBack.x- kAccX, 0), m_knockBack.x + kAccX);
	m_knockBack.y += kAccY;
}

//プレイヤーの動きの制限
void PlayerBase::moveLimit()
{
	int playerSize = m_sizeRight - m_sizeLeft;
	if (m_pos.x < static_cast<float>(-abs(playerSize)))
	{
		m_pos.x = static_cast<float>(Game::kScreenWidth) + static_cast<float>(abs(playerSize));
	}

	if (m_pos.x > static_cast<float>(Game::kScreenWidth) + static_cast<float>(abs(playerSize)))
	{
		m_pos.x = static_cast<float>(-abs(playerSize)) ;
	}
}
