#include "Map.h"
#include "Stage.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"
#include"../Util/CurrentPlayerMap.h"

namespace
{
	// モデルのハンドル
	const char* const kFieldHandle = "Data/Model/Block.mv1";	// フィールド用のモデル
	const char* const kFlagHandle = "Data/Model/Flag.mv1";		// 旗用のモデル
	// 当たり判定として使用するフレームの名前
	const char* const kCollisionFrameNamu = "BoxCol";
	// プレイヤーの位置を受け取る
	VECTOR kPlayerPos = { 0,0,0 };
	// プレイヤーの当たり判定の大きさを受け取る
	float kPlayerRad = 0;
}

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map(int selectNum) :
	m_pCurrentMap(nullptr),
	m_selectNum(selectNum),
	m_dataColNum(0),
	m_dataRowNum(0),
	m_collisionradius(0),
	m_max(1),
	m_maxRand(3),
	m_gameClearFlag(false),
	m_objectPosX(0)
{	
	m_currentData.clear();
	// マップのロード
	m_pStage = new Stage;

	m_mapLoad[Easy] = "Data/Map/Easy.fmf" ;
	m_mapLoad[Normal] =  "Data/Map/Normal.fmf";
	m_mapLoad[Hard] = "Data/Map/Hard.fmf" ;
	m_mapLoad[Endless] =  "Data/Map/Normal.fmf" ;
	
	if (m_selectNum != Endless)
	{
		m_pStage->Load(m_mapLoad[m_selectNum]);
	}
	else if (m_selectNum == Endless)
	{
		SelectEndless();
	}
	// もしそれ以外の数字が選ばれた場合、とりあえずEasyをロードする
	else
	{
		m_pStage->Load(m_mapLoad[Easy]);
	}
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	m_mapLoad.clear();
	delete(m_pStage);
	delete(m_pCurrentMap);
	m_pObject.clear();
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	// currentDataに外部ファイルを代入
	m_currentData.clear();
	std::vector<int> newColData;

	m_pStage->GetMapSize(m_dataRowNum, m_dataColNum);
	const auto mapData = m_pStage->GetMapData();
	for (int i = m_dataColNum - 1; i >= 0; i--)
	{
		newColData.clear();
		for (int j = 0; j < m_dataRowNum; j++)
		{
			newColData.push_back(m_pStage->GetChipId(0, j, i));
		}
		m_currentData.push_back(newColData);
	}
	// モデルの読み込み処理
	// 複数個コピーして使用するため最初に一つだけ読み込む
	m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, 0, 0));
	m_pObject.back()->Init();
	int fieldHandle = m_pObject.back()->GetModelHandle();
	for (int i = 0; i < m_dataColNum; i++)
	{
		for (int j = 0; j < m_dataRowNum; j++)
		{
			if (m_currentData[i][j] == Field)
			{
				// 同じものはコピーして使う
				// ブロックの初期化処理
				m_pObject.push_back(std::make_shared<GameObject>(fieldHandle, Field, j, i));
				//m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, j, i));
				m_pObject.back()->Init();
			}
			if (m_currentData[i][j] == Flag)
			{
				// ３Ｄモデルの読み込み
				// フラグの初期化処理
				m_pObject.push_back(std::make_shared<GameObject>(kFlagHandle, Flag, j, i));
				m_pObject.back()->Init();
			}

			// オブジェクトの横の最大値を取得するための処理
			// 今の数値より大きかったら数値を代入する
			if (m_objectPosX < m_pObject.back()->GetPosX())
			{
				m_objectPosX = m_pObject.back()->GetPosX();
			}
		}
	}
	// エンドレスじゃなかったらミニマップを表示させる
	if (m_selectNum != Endless)
	{
		m_pCurrentMap = new CurrentPlayerMap(m_objectPosX);
	}
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 更新処理
	for (const auto& obj : m_pObject)
	{
		obj->Update();
		// 当たり判定の情報
		MV1SetupCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex());
	}

	// 不必要なオブジェクトの削除処理
	for (int i = 0; i < m_pObject.size() - 1; i++)
	{
		if (!m_pObject[i]->IsExist())
		{
			// 存在していなかったら要素を削除
			m_pObject.erase(m_pObject.begin() + i);
			// 領域をコンテナのサイズまで切り詰める
			m_pObject.shrink_to_fit();
		}
	}
	// 旗が画面外に言ったらゲームクリア判定にする
	if (m_pObject.size() <= m_max)
	{
		m_gameClearFlag = true;
	}
	// endlessの処理
	if (m_selectNum == Endless && m_pObject[m_pObject.size() - 1]->IsDrawFlag())
	{
		SelectEndless();
	}
	// もしクラスの中身が空じゃなかったら処理をする
	if (m_pCurrentMap)
	{
		m_pCurrentMap->Update();
	}
	//printfDx("%d\n", m_pObject.size());
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	// 描画処理
	for (const auto& obj : m_pObject)
	{
		obj->Draw();
	}
	// もしクラスの中身が空じゃなかったら処理をする
	if (m_pCurrentMap)
	{
		m_pCurrentMap->Draw();
	}
}

void Map::SelectEndless()
{
	int random = GetRand(m_maxRand);
	//printfDx("%d\n", random);
	switch (random)
	{
	case 0:
		m_pStage->Load("Data/Map/Random1.fmf");
		break;
	case 1:
		m_pStage->Load("Data/Map/Random2.fmf");
		break;
	case 2:
		m_pStage->Load("Data/Map/Random3.fmf");
		break;
	case 3:
		m_pStage->Load("Data/Map/Random4.fmf");
		break;
	default:
		m_pStage->Load("Data/Map/Random1.fmf");
		break;
	}
	Load();
}

void Map::CollisionDetection(Player* player)
{
	// プレイヤーの位置、当たり判定の範囲を渡す
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// DxLibの関数を利用して当たり判定をとる
	MV1_COLL_RESULT_POLY_DIM result;// 当たりデータ

	for (const auto& obj : m_pObject)
	{
		result = MV1CollCheck_Capsule(obj->GetModelHandle(), obj->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (obj->GameObjectNum() == Field)
		{
			if (!m_gameClearFlag)
			{
				if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
				{
					player->IsExistPlayer(true);
					player->PlayerDropPoint(static_cast<int>(result.Dim[1].Position[1].y));
				}
			}
		}
		else if (obj->GameObjectNum() == Flag)
		{
			if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
			{
				m_gameClearFlag = true;
			}
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}
}