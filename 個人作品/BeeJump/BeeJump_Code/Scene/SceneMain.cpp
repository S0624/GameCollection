#include"../Common.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneSelect.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"
#include "../Util/Effect.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneMain::SceneMain(int selectNum) :
	m_teimer(60 * 2),
	m_scoreHandle(0),
	m_guideHandle(0),
	m_frameHandle(0),
	m_selectNum(selectNum),
	m_gamefont(0),
	m_guidefont(0),
	m_seFlag(false),
	m_cursolNum(0),
	m_gameHandle(0),
	m_scoreCount(0),
	m_makeScreen(0),
	m_shadowMap(0)
{
	// 初期化関係
	m_pCamera = new Camera();
	m_pPlayer = new Player();
	m_pMap = new Map(m_selectNum);
	m_pBack = new BackGround();

	m_pEffect = new Effect;
}
/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
	// BGM 停止
	Sound::StopBGM(Sound::MainBGM);
	Sound::StopBGM(Sound::GameClear);
	Sound::StopBGM(Sound::GameOver);
	// 削除
	delete(m_pPlayer);
	delete(m_pMap);
	delete(m_pBack);
	delete(m_pCamera);
	//delete(m_pEffect);

	DeleteGraph(m_scoreHandle);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_gameHandle);

	DeleteFontToHandle(m_gamefont);
	DeleteFontToHandle(m_guidefont);

	//// シャドウマップの削除
	//DeleteShadowMap(m_shadowMap);
}
/// <summary>
/// 初期化処理
/// </summary>
void SceneMain::Init()
{
	m_isFadeOut = IsFadingOut();//フェードの初期化
	m_pMap->Load();// マップのロード

	// 画像の読み込み
	m_scoreHandle = LoadGraph("Data/Img/ScorePlate.png");
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");
	m_gameHandle = LoadGraph("Data/Img/GameEndImg.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_gamefont = CreateFontToHandle("yosugara ver12", 100, -1, -1);// 上の表示する文字に使用するフォン
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン

	m_pEffect->Init();

	//// シャドウマップの生成
	//m_shadowMap = MakeShadowMap(1024, 1024);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}
/// <summary>
/// エンド処理
/// </summary>
void SceneMain::End()
{
	// 今のところ処理なし
}
/// <summary>
/// 更新処理
/// </summary>
SceneBase* SceneMain::Update()
{	
	Sound::LoopBGM(Sound::MainBGM);
	m_pCamera->Update(*m_pPlayer);// カメラの更新処理
	m_pEffect->Update();
	m_pPlayer->Update(); // プレイヤーの更新処理
	// OPTIMIZE ゲームの状態を受け取っている
	m_pPlayer->GameClearFlag(m_pMap->GameClearFlag());	// ゲームの状態を受け取る
		// プレイヤーが死んでいなかった時に更新処理を行う
	if (!m_pPlayer->IsExistPlayer())
	{
		m_pBack->Update(); // 背景の更新処理
		// タイマーの表示が終わったら
		if (Timer())
		{
			m_scoreCount++;
			m_pMap->Update(); // マップの更新処理
			m_pMap->CollisionDetection(m_pPlayer); // 当たり判定の処理
		}
	}
	else
	{
		// BGM 停止
		Sound::StopBGM(Sound::MainBGM);
		if (!m_seFlag)
		{
			Sound::PlaySE(Sound::GameOver);
			m_seFlag = true;
		}
	}
	if (m_pMap->GameClearFlag() == true)
	{
		// BGM 停止
		Sound::StopBGM(Sound::MainBGM);
		// ループ位置を音の先頭から2秒後にセットする
		Sound::SetLoopBGM(2200,Sound::GameClear);
	}

	// フェードインアウトしていなかったら
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// resultSceneに飛ぶ
			if (m_selectNum == Endless)
			{
				// 移行する際にスコアを渡す
				return (new SceneResult(m_scoreCount));
			}
			if (m_cursolNum == 0)
			{
				return (new SceneMain(m_selectNum));
			}
			else
			{
				return (new SceneSelect);
			}
		}
	}

	// フェードインアウトしていない
	if (!IsFading())
	{
		m_teimer--;
		// フェードアウト開始
		if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
		{
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				Sound::PlaySE(Sound::PushButton);
				// フェードを開始する
				StartFadeOut();
			}
			// エンドレスの場合は強制的にリザルトに移行させるのでこの処理をしない
			if (m_selectNum != Endless)
			{
				// cursor処理
				if (Pad::IsTrigger(PAD_INPUT_UP))
				{
					Sound::PlaySE(Sound::Cursor);
					m_cursolNum++;
				}
				if (Pad::IsTrigger(PAD_INPUT_DOWN))
				{
					Sound::PlaySE(Sound::Cursor);
					m_cursolNum--;
				}
			}
		}
	}
	// 範囲外の数字に行かないようにする
	if (m_cursolNum > 1)
	{
		m_cursolNum = 0;
	}
	else if (m_cursolNum < 0)
	{
		m_cursolNum = 1;
	}

	return this;
}
/// <summary>
/// 描画処理
/// </summary>
void SceneMain::Draw()
{
	//// シャドウマップへの書き込み
	//ShadowMap_DrawSetup(m_shadowMap);
	//// シャドウマップを使用してモデルの描画を行う
	//ShadowMap_DrawEnd();
	//SetUseShadowMap(0, m_shadowMap);

	m_pBack->Draw();	// 背景の表示
	m_pMap->Draw();		// ステージの表示
	m_pPlayer->Draw();	// プレイヤーの表示
	// エフェクトの実装
	//SetDrawScreen(m_makeScreen);
	m_pEffect->Draw();
	//SetDrawScreen(DX_SCREEN_BACK);			//通常描画に戻す
	//DrawGraph(0, 0, m_makeScreen, true);

	// エンドレスの場合のみスコアを表示する
	if (m_selectNum == Endless)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);			// ブレンドモードをいじってスコアのパネルを半透明にする
		// スコア版の表示
		DrawGraph(25, 25, m_scoreHandle, true);
		// スコアの表示
		DrawFormatStringToHandle(100,
			60, 0x000000, m_gamefont, "%d", m_scoreCount);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す
	}

	// クリアとゲームオーバーを出す
	if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
	{
		DrawGuide();
	}
	// タイマー
	if (!Timer())
	{
		// TODO あとで画像化する
		DrawFormatStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("%d", 16, m_gamefont)) / 2,
			Game::kScreenHeight / 2, 0xff0000, m_gamefont, "%d", m_teimer / 60 + 1);
	}

	// フェードの表示
	SceneBase::DrawFade();
}

bool SceneMain::Timer()
{
	// 残り時間によりフラグを返す
	bool timeFlag = false;
	if (m_teimer <= 0)
	{
		m_teimer = 0;
		timeFlag = true;
	}

	return timeFlag;
}

void SceneMain::DrawGuide()
{
	// 切り取る大きさ(乗算する用の変数)
	int imgY = 0;
	// 説明の画像の表示
	if (m_selectNum != 3)
	{
		DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - 230,
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_guideHandle, true,
			false, false);
		// 選択フレームの画像の表示
		DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_frameHandle, true,
			false, false);

		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("リトライ ", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 370, "リトライ ", 0xffffff, m_guidefont);
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("ステージセレクト ", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 160, "ステージセレクト ", 0xffffff, m_guidefont);
	}
	
	// ゲームクリア、ゲームオーバーを描画する
	if (m_pMap->GameClearFlag())
	{
		imgY = 0;
	}
	// TODO あとで画像化する
	else
	{
		imgY = 1;		
	}

	// ゲームクリア、ゲームオーバーの画像を出す
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - (Game::kScreenHeight  - 300),
		0, 144 * imgY,
		897, 144,
		1.0f, 0.0f,
		m_gameHandle, true,
		false, false);
}
