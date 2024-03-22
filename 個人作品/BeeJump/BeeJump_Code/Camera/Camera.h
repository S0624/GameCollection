#pragma once
#include "../Common.h"

class Player;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();							// コンストラクタ
	~Camera();							// デストラクタ

	void Update(const Player& player);	// 更新

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return m_pos; }

private:
	VECTOR	m_pos;			// ポジション


};
