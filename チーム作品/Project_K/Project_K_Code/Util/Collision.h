#pragma once

class PlayerBase;

class Collision
{
public:
	Collision(PlayerBase* Player1, PlayerBase* Player2);
	virtual ~Collision();

	bool IsColl1();		//プレイヤー1の攻撃がプレイヤー2に当たったか

	bool IsColl2();		//プレイヤー2の攻撃がプレイヤー1に当たったか

	bool ShotColl1();	//プレイヤー1のショットがプレイヤー2に当たったか

	bool ShotColl2();	//プレイヤー2のショットがプレイヤー1に当たったか

	bool AttackColl();	//プレイヤーの攻撃同士が当たった時

private:
	PlayerBase* m_Player[2];
};

