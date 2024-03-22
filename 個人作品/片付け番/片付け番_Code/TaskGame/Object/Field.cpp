#include"DxLib.h"
#include "Field.h"
#include"FieldInformation.h"
#include<cassert>
#include"../UI/game.h"
#include"../GameManager.h"

namespace
{
	FieldInformation m_Information;
	constexpr int kIndexSize = 25;
}

//フィールドクラスのコンストラクタ
Field::Field() :
	m_handle(0),
	m_groundHandle(0),
	m_boxHandle(0),
	m_wallHandle(0),
	m_pinHandle(0),
	m_storageNum(0),
	m_drawFlag(false),
	m_boxMoveSpeed(0),
	m_pos(0, 0),
	m_boxNextPos(0, 0),
	m_boxType(0)
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

	m_groundHandle = my::MyLoadGraph(L"../Date/floor.png");		//画像の読み込み
	m_wallHandle = my::MyLoadGraph(L"../Date/wall.png");		//画像の読み込み
	m_pinHandle = my::MyLoadGraph(L"../Date/pin.png");		//画像の読み込み
	m_boxHandle = my::MyLoadGraph(L"../Date/box.png");		//画像の読み込み
}

//フィールドクラスのデストラクタ
Field::~Field()
{
	DeleteGraph(m_groundHandle);
	DeleteGraph(m_wallHandle);
	DeleteGraph(m_pinHandle);
	DeleteGraph(m_boxHandle);
}

//フィールドクラスの更新処理
void Field::Update()
{
	//箱の移動処理
	MoveFrame();

	int remaining = 0;
	for (int y = 0; y < kFieldY; y++)		//fieldにある置き場所のカウント
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == storage)
			{
				remaining++;
			}
		}
	}
	m_storageNum = remaining;
}

//フィールドクラスの描画処理
void Field::Draw()
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			DrawField(x,y);
		}
	}

	//フラグが立っていたら箱を表示させる
	if (m_drawFlag == true)
	{
		int index = 0;
		if (m_boxType == box)
		{
			index = 0;
		}
		else
		{
			index = 16;
		}
		my::MyDrawRectRotaGraph(static_cast<int>(m_pos.x) + kWidth + (kIndexSize),
			static_cast<int>(m_pos.y) + kHeight + (kIndexSize),			//表示座標
			index, 0,							//切り取り左上
			16, 21,							//幅、高さ
			2.5f, 0.0f,						//拡大率、回転角度
			m_boxHandle, true);
	}
}

void Field::DrawField(int x, int y)
{
	int posX = kSize * x;
	int posY = kSize * y;
	m_handle = 0;
	if (m_field[y][x] != empty)
	{
		my::MyDrawRectRotaGraph(posX + kWidth + (kIndexSize),
			posY + kHeight + (kIndexSize),			//表示座標
			0, 0,						//切り取り左上
			16, 16,							//幅、高さ
			3.0f, 0.0f,						//拡大率、回転角度
			m_groundHandle, true);
	}
	if (m_field[y][x] == wall)
	{
		m_indexSize = 16;
		m_index = 3.0;
		m_shift = 0;
		m_handle = m_wallHandle;
	}
	if (m_field[y][x] == storage)
	{
		m_indexSize = 16;
		m_index = 2.5;
		m_shift = 0;
		m_handle = m_pinHandle;
	}
	if (m_field[y][x] == box)
	{
		m_indexSize = 21;
		m_index = 2.5;
		m_shift = 0;
		m_handle = m_boxHandle;
	}
	if (m_field[y][x] == input)
	{
		m_indexSize = 21;
		m_index = 2.5;
		m_shift = 16;
		m_handle = m_boxHandle;
	}
	if (m_field[y][x] == nextPos)
	{
		m_indexSize = 16;
		m_index = 2.5;
		m_shift = 0;
		m_handle = m_pinHandle;
	}
	my::MyDrawRectRotaGraph(posX + kWidth + (kIndexSize),
		posY + kHeight + (kIndexSize),			//表示座標
		m_shift, 0,						//切り取り左上
		16, m_indexSize,							//幅、高さ
		m_index, 0.0f,						//拡大率、回転角度
		m_handle, true);
}

//フィールドの中身を見て動けるかを返す処理
bool Field::IsMovable(int posX, int posY, int x, int y)
{
	assert((x >= 0) || (x <= kFieldX - 1));		//アサート
	assert((y >= 0) || (y <= kFieldY - 1));		//範囲外だと処理を止める
	if (m_field[posY][posX] == empty)	return true;		//何もないとその先に行けなくする
	if (m_field[posY][posX] == wall)	return true;		//壁だとその先に行けなくする

	m_moveBox = true;
	if (m_field[posY][posX] == box)						//箱を押したときの処理
	{
		if (m_field[posY + y][posX + x] == ground)	//箱を押してその先に何もない時の処理
		{
			tempFieldInput();
			m_drawFlag = true;
			m_field[posY][posX] = ground;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = ground;			//次に箱が来る場所の確保
			MoveFrame(posX, posY, x, y, box);

			return false;
		}
		if (m_field[posY + y][posX + x] == storage)	//箱を押してその先が置き場所だった場合の処理
		{
			tempFieldInput();
			m_drawFlag = true;
			m_field[posY][posX] = ground;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = nextPos;			//次に箱が来る場所の確保
			MoveFrame(posX, posY, x, y, input);
			return false;
		}
		return true;							//それ以外はtrueを返す
	}

	if (m_field[posY][posX] == input)						//置かれている箱を動かすときの処理
	{
		if (m_field[posY + y][posX + x] == ground)
		{
			tempFieldInput();
			m_drawFlag = true;
			m_field[posY][posX] = storage;
			m_field[y + posY][x + posX] = ground;			//次に箱が来る場所の確保
			MoveFrame(posX, posY, x, y, box);
			return false;
		}
		if (m_field[posY + y][posX + x] == storage)
		{
			tempFieldInput();
			m_drawFlag = true;
			m_field[posY][posX] = storage;
			m_field[y + posY][x + posX] = nextPos;			//次に箱が来る場所の確保
			MoveFrame(posX, posY, x, y, input);
			return false;
		}
		return true;
	}
	tempFieldInput();
	return false;
}

//フィールドの中身を見て動けるかを返す処理
bool Field::IsMovablePos(int x, int y)
{
	if (m_field[y][x] == ground)	return false;		//地面だと移動できる
	if (m_field[y][x] == storage)	return false;		//置き場所だと移動できる
	return true;										//その先に行けなくする
}

//ゲームクリアかどうかを返す処理
bool Field::GameClear()const
{
	//置き場所がゼロになったら　trueを返す
	if (m_storageNum == 0) return true;
	return false;
}

//フィールドの情報を持ってくる関数
int Field::FieldInfo(int field[kFieldY][kFieldX])
{
	for (int i = 0; i < kFieldX; i++)		//fieldに数値を入れる
	{
		for (int j = 0; j < kFieldY; j++)
		{
			m_field[j][i] = field[j][i];
		}
	}
	return 0;
}

int Field::StepLimit(int step)
{
	m_step = step;
	return 0;
}

int Field::StepLimit()
{
	return m_step;
}

//箱を移動させるための情報を持つ関数
void Field::MoveFrame(int posX, int posY, int x, int y, int type)
{
	int vec = x + y;													//移動ベクトルがマイナスかプラスか調べる
	m_drawFlag = true;													//フラグをtrueにする
	m_pos.x = static_cast<float>(posX * kSize);							//箱の現在地を計算する
	m_pos.y = static_cast<float>(posY * kSize);							//箱の現在地を計算する
	m_boxMoveSpeed = static_cast <float>(3.0 * vec);					//移動スピードの設定
	m_boxNextPos.x = static_cast<float>(posX * kSize) + (x * kSize);	//箱の次の場所の計算
	m_boxNextPos.y = static_cast<float>(posY * kSize) + (y * kSize);	//箱の次の場所の計算
	m_boxType = type;													//箱のタイプ
}

//箱を移動させる処理
void Field::MoveFrame()
{
	//箱の場所
	int x = static_cast<int>(m_boxNextPos.x) / kSize;
	int y = static_cast<int>(m_boxNextPos.y) / kSize;
	// 毎フレーム緩やかに目標に近づく
	if (m_pos.y != m_boxNextPos.y)
	{
		m_pos.y += m_boxMoveSpeed;
		//	// 目標に合致したら止める
		if (m_boxMoveSpeed == 3.0)
		{
			if (m_pos.y >= m_boxNextPos.y)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.y = m_boxNextPos.y;
				m_drawFlag = false;
			}
		}
		else
		{
			if (m_pos.y <= m_boxNextPos.y)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.y = m_boxNextPos.y;
				m_drawFlag = false;
			}
		}
	}

	// 毎フレーム緩やかに目標に近づく
	if (m_pos.x != m_boxNextPos.x)
	{
		m_pos.x += m_boxMoveSpeed;
		//	// 目標に合致したら止める
		if (m_boxMoveSpeed == 3.0)
		{
			if (m_pos.x >= m_boxNextPos.x)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.x = m_boxNextPos.x;
				m_drawFlag = false;

			}
		}
		else
		{
			if (m_pos.x <= m_boxNextPos.x)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.x = m_boxNextPos.x;
				m_drawFlag = false;

			}
		}

	}
	m_moveBox = false;
}

bool Field::MoveBox() const
{
	if (m_moveBox == true)return true;
	return false;
}

//フィールドの一つ戻す実装
void Field::tempFieldInput()
{
	for (int i = 0; i < kFieldX; i++)		//fieldに数値を入れる
	{
		for (int j = 0; j < kFieldY; j++)
		{
			m_tempField[j][i].push(m_field[j][i]);
		}
	}
}

//フィールドの一つ戻す実装
void Field::tempFieldOut()
{
	for (int i = 0; i < kFieldX; i++)		//fieldに数値を入れる
	{
		for (int j = 0; j < kFieldY; j++)
		{
			m_field[j][i] = m_tempField[j][i].top();
			m_tempField[j][i].pop();
		}
	}
}
