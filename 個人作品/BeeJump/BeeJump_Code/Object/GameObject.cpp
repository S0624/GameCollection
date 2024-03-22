#include "GameObject.h"
#include"../Util/Model.h"
#include <cassert>

namespace
{
	// スクロール量
	//constexpr float kMoveScroll = -1.5f;
	constexpr float kMoveScroll = -1.0f;
	//float kAddScroll = 0.0f;
	
	// 当たり判定の大きさ
	constexpr float kColRadius = 6.0f;

	// プレイヤーの位置を受け取る
	VECTOR kPlayerPos = {0,0,0};
	// プレイヤーの当たり判定の大きさを受け取る
	float kPlayerRad = 0;
}

/// <summary>
/// コンストラクタ
/// </summary>
GameObject::GameObject(const char* modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),// ゲームオブジェクトのハンドル
	m_objectNum(objNum),// オブジェクトの番号
	m_speed(3.0f),// スクロールのスピード
	m_scale(0.05f),	// スケール
	m_blockX(blockX),// オブジェクトの位置を受け取る
	m_blockY(blockY),// オブジェクトの位置を受け取る
	m_isExist(false),//	描画していい範囲かどうか
	m_drawRange(false)//  オブジェクトの使用している番号
{
	// ハンドルを受け取る
	m_modelHandle = MV1LoadModel(modelhnadle);
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(modelhnadle);
	// 当たり判定の有効化
	m_pModel->setUseCollision(true, true);

	// 位置の初期化
	m_pos = VAdd(VGet(250.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	// 回転の設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

GameObject::GameObject(int modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),// ゲームオブジェクトのハンドル
	m_objectNum(objNum),// オブジェクトの番号
	m_speed(3.0f),// スクロールのスピード
	m_scale(0.05f),	// スケール
	m_blockX(blockX),// オブジェクトの位置を受け取る
	m_blockY(blockY),// オブジェクトの位置を受け取る
	m_isExist(false),//	描画していい範囲かどうか
	m_drawRange(false)//  オブジェクトの使用している番号
{
	// ハンドルを受け取る
	//m_modelHandle = MV1LoadModel(modelhnadle);
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(modelhnadle);
	// 当たり判定の有効化
	m_pModel->setUseCollision(true, true);

	// 位置の初期化
	m_pos = VAdd(VGet(250.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	// 回転の設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
	// モデルのアンロード
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void GameObject::Update()
{
	// スクロール処理
	m_pos.x += kMoveScroll;

	// 回転の設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
	// 更新処理
	m_pModel->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameObject::Draw()
{

	// 存在していなかったら描画しない
	if (IsDrawFlag())
	{
		// ３Dモデルのポジション設定
		m_pModel->SetPos(m_pos);
		// 描画処理
		m_pModel->Draw();
	}

}

/// <summary>
/// 範囲外だったら存在を消す
/// </summary>
/// <returns>m_isExist</returns>
bool GameObject::IsExist()
{
	// オブジェクトの位置が画面外に行ったら
	if (m_pos.x < 0)	{m_isExist = false;}
	else				{ m_isExist = true; }
	// 現在の存在情報を返す
	return m_isExist;
}

bool GameObject::IsDrawFlag()
{
	if (m_pos.x > 0 && m_pos.x < 250)
	{
		// それ以外は存在する
		m_drawRange = true;
	}
	else
	{
		// 存在を消す
		m_drawRange = false;
	}
	return m_drawRange;
}

/// <summary>
/// モデルハンドルの取得
/// </summary>
/// <returns>m_pModel->GetModelHandle()</returns>
int GameObject::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}

/// <summary>
/// 当たり判定の取得
/// </summary>
/// <returns>m_pModel->GetColFrameIndex()</returns>
int GameObject::GetCollisionFrameIndex() const
{
	return m_pModel->GetColFrameIndex();
}