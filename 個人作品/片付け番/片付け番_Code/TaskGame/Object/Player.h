#pragma once
#include"../UI/Vec2.h"
#include<stack>

//　プロトタイプ宣言
class Field;
class InputState;
class Player
{
private:
	//fieldクラス
	Field* m_pField;

	//プレイヤーの位置
	Vec2 m_pos;
	//プレイヤーの画像をずらす
	int m_handlePos;
	//プレイヤーの画像
	int m_handle;
	//プレイヤーの画像の表示を変更する変数
	int m_imgidx;

	//キーボードを押された時に移動に制限をかける
	int m_moveDown;			//下
	int m_moveUp;			//上
	int m_moveLeft;			//左
	int m_moveRight;		//右
	int m_lastMove;			//最後に押されたキーを覚えておく

	int m_animationNumber;		//アニメーションの番号
	int m_animetionFraem;		//アニメーションを変えるインターバル

	//歩いた歩数（お試し）
	int m_stepCount;

	float m_playerMoveSpeed;	//プレイヤーが動くスピード	
	Vec2 m_playerNextPos;		//プレイヤーが次に動く場所
	bool m_animeFlag;			//アニメーションのフラグ

	int m_playerMoveNum;		//プレイヤーがどの向きに動くか

	int m_addition = 1;
	float m_posX = 800;
	float m_posY = 500;

	std::stack<Vec2>m_tempPos;
	std::stack<int>m_tempDirection;
private:
	//プレイヤーが動くために必要な情報を持つ関数
	void MoveFrame(Vec2 vel);
	//プレイヤーが動く処理
	void MoveFrame();
	//プレイヤーの移動処理
	void UpdatePlayer(const InputState& input);
	//下に動けるかどうかの判定処理
	bool IsMoveDown()const;
	//上に動けるかどうかの判定処理
	bool IsMoveUp()const;
	//左に動けるかどうかの判定処理
	bool IsMoveLeft()const;
	//右に動けるかどうかの判定処理
	bool IsMoveRight()const;

	//アニメーションを行う処理
	const void AnimetionPlayer(bool animeFlag);


public:
	Player();
	~Player();

	//プレイヤーの初期位置を受け取る
	void PosInit(int x, int y);

	//更新処理
	void Update(const InputState& input);
	// 使用するフィールドのデータを設定する
	void SetField(Field* pField) { m_pField = pField; }

	//次に動く場所が動けるかをチェックする処理
	bool IsMoveNextPos(int x, int y)const;

	//タイトルで表示するプレイヤーのUpdate
	void TitleUpdate();
	//描画処理
	void Draw()const;

	//動いた手数を返す
	int MoveStep()const { return m_stepCount; }
};

