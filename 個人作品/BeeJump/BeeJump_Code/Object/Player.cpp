#include "Player.h"
#include"../Util/Model.h"
#include <cassert>
namespace
{
	// モデルのファイル名
	const char* const kFileName = "Data/Model/Bee.mv1";
	// 重力
	constexpr float kGravity = -0.15f;
	// ジャンプ力
	constexpr float kJumpPower = 2.5f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(): 
	m_modelHandle(-1),// モデルハンドル
	m_colradius(5.0f),// 当たり判定に使用する半径の大きさ
	m_dropPos(-10.0f),// 箱の位置によって落ちる場所を変える	
	m_speed(3.0f),// スピードの変更
	m_scale(0.07f),	// スケール
	m_jumpAcc(0),// ジャンプ
	m_attachIndex(0),// 総時間取得するアニメーションのアタッチ番号
	m_totalTime(0),// アニメーションの総再生時間
	m_animTime(0),// 現在のアニメーションの再生時間
	m_attachAnimNum(2)// 再生したいアニメーションの番号

{
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->SetAnimation(m_attachAnimNum, true, true);

	// 位置、ベロシティ、回転の初期化
	m_pos = VGet(60, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 0);

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
Player::~Player()
{
	// モデルの削除
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// 更新処理
	m_pModel->Update();

	// ジャンプ処理
	bool isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < -10.0f || m_pos.y < m_dropPos)
	{
		m_pos.y = m_dropPos;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}
	if (m_pos.y > 110.0f)
	{
		m_pos.y = 110.0f;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}

	if (( !IsExistPlayer() && !m_gameSituation) && Pad::IsTrigger(PAD_INPUT_1))
	{
		Sound::PlaySE(Sound::Jump);
		m_jumpAcc = kJumpPower;
	}

	if (IsExistPlayer())
	{
		m_attachAnimNum = 1;
		m_animTime = 0.0f;
		m_pModel->ChangeAnimation(m_attachAnimNum, false, true, 4);
	}


	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	// ポジションを更新.
	m_velocity = VScale(m_dir, m_speed);
	m_pos = VAdd(m_pos, m_velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}


	// 3Dモデルのスケール決定
	m_pModel->SetPos(m_pos);
	// ３Dモデルのポジション設定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	m_pModel->Draw();
}