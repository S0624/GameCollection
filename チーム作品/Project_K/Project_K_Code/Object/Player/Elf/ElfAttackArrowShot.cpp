#include "ElfAttackArrowShot.h"

namespace// 仮のネームスペース
{
	constexpr int kAttack_X = 11;
	constexpr int kAttack_Y = 11;
}

ElfAttackArrowShot::ElfAttackArrowShot()
{
	m_isMove = true;
}

void ElfAttackArrowShot::Update()
{
	m_frameCount++;
	if (m_frameCount == 4)//3フレームに一回画像描画位置を変更する
	{
		m_frameCount = 0;
		if (m_imagePosX < 288 * kAttack_X)//画像が右に続いていたら右にずらす
		{
			m_imagePosX += 288;//X軸を右にずらす
		}
		else
		{
			m_imagePosX = 0;// 画像の描画させる位置を初期値に戻す
			m_isMove = false;// 攻撃終了
		}
	}
	m_imagePosY = 128 * kAttack_Y;// 画像の描画させる縦の位置

	m_attackDamage = 30;//攻撃量
}
