#include "SceneMain.h"
#include"../Object/Field.h"
#include"../Object/Player.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include "SceneSelect.h"
#include "SceneTitle.h"
#include"ScenePause.h"
#include"SceneManager.h"
#include"../Object/FieldInformation.h"
#include"../Object/MapChip.h"
#include"../GameManager.h"
#include"../Object/CreateEffect.h"
#include"../SoundManager.h"
#include"DxLib.h"

namespace {
	int kNextStage = 0;
}

//フェード処理
void SceneMain::FadeInUpdate(const InputState& input)
{
	//SetVolumeMusic(static_cast<int>(255 - 255.0f / 60.0f * static_cast<int>(60 - m_fadeTimer)));
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneMain::NormalUpdate;
		m_fadeValue = 0;
	}
}

//アップデート処理
void SceneMain::NormalUpdate(const InputState& input)
{
	m_pField->Update();		//フィールドクラスの更新処理
	m_pPlayer->Update(input);	//プレイヤークラスの更新処理

	//現在のステップ数
	if (m_stepNum != 0)
	{
		m_stepColor = 0xF0E68C;
	}
	if (m_stepNum > m_LimitNum * 0.8)
	{
		m_stepColor = 0xFF4500;
	}
	m_stepNum = m_pPlayer->MoveStep();

	if (!m_pField->MoveBox())
	{
		if (m_pField->GameClear())
		{
			m_pEffect->Update();
		}
		else if (m_stepNum >= m_LimitNum)
		{
			m_gameOverFlag = true;
		}
	}
	//クリアしてフェードが掛かり切ったらセレクトしてもらう
	if (m_fadeColor)
	{
		CursorUpdate(input);
	}
	//「ポーズ」ボタンが押されたらポーズを表示
	//ゲームクリアしていたら押せなくする
	else if (input.IsTrigger(InputType::pause))
	{
		
		SoundManager::GetInstance().Play(L"Pause1");
		StopSoundMem(m_gamePlayBgSound);
		m_manager.PushScene(new ScenePause(m_manager));
	}

	m_pauseNum = m_pPause->CursolUpdate();
	if (m_pauseNum == 2 || m_pauseNum == 3 || m_pauseNum == 4)
	{
		m_selectNum = m_pauseNum;
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
}

//フェード処理
void SceneMain::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
		// ステージに戻る
		if (m_selectNum == 3)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneSelect(m_manager));
			return;
		}
		// タイトルに戻る
		if (m_numCount == 3 || m_selectNum == 4)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneTitle(m_manager));
			return;
		}
		// 初期化（初めからを選択した場合の処理）
		if (m_numCount == 2 || m_selectNum == 2)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneMain(m_manager));
			return;
		}
		// 次へを押された場合の処理
		if (m_stageNum != 10)
		{
			if (m_numCount == 1)
			{
				kNextStage = 1;
				m_manager.ChangeScene(new SceneMain(m_manager));
				return;
			}
		}
	}
}

//ロード系の初期化
void SceneMain::InitLoad()
{
	//画像の読み込み
	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");
	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");
	// 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); 
	my::MyFontPath(L"../Font/komorebi-gothic.ttf");
	my::MyFontPath(L"../Font/erizifont.otf");
	// フォントの指定
	m_clearFont = CreateFontToHandle(L"851マカポップ", 200, -1, -1);
	m_guideFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 42, -1, -1);
	m_UIFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 32, -1, -1);
	m_scoreFont = CreateFontToHandle(L"えり字", 64, -1, -1);
	//マップの読み込み
	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");
	m_pMap->Load(L"../Date/room.fmf");
}

//サウンド系の初期化
void SceneMain::InitSound()
{
	m_gamePlayBgSound = LoadSoundMem(L"../Sound/BGM/GamePlayBg.mp3");
}

//背景表示の処理
void SceneMain::DrawBackground()
{
	//背景
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// 縦方向
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// 横方向
		{
			auto backChipId = mapData[0][static_cast<__int64>(chipY) * mW + chipX];
			my::MyDrawRectRotaGraph(chipX * 32, chipY * 32,
				(backChipId % 10) * 16,
				(backChipId / 8) * 16,
				16, 16,
				2.0f, 0,
				m_backHandle, true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_MULA, 50);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す
}

//ゲームクリアの処理
void SceneMain::DrawGameClear()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_setBlend);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//ポーズウィンドウセロファン
	m_setBlend++;

	if (m_setBlend < 100)
	{
		if (m_setBlend == 90)
		{
			SoundManager::GetInstance().Play(L"GameClear");
		}
		return;
	}
	if (m_setBlend > 100)
	{
		m_fadeColor = true;
		m_setBlend = 100;
	}

	DeleteSoundMem(m_gamePlayBgSound);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	m_pEffect->Draw();
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Clear", 11, m_clearFont)) / 2,
		100, L"Game Clear", 0x7fffff, m_clearFont);								//タイトルの表示

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);

	if (m_stageNum != 10)
	{
		DrawStringToHandle(widthPos + 50, heightPos + m_index, L"次へすすむ", 0x000000, m_guideFont);
	}
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 2, L"もう一度プレイ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 3, L"タイトルへ戻る", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + m_index * m_numCount, L"▶", 0x00a000, m_guideFont);
}

//ゲームオーバーの処理
void SceneMain::DrawGameOver()
{
	m_overPosY += m_gravity;
	if (m_overPosY > 20 || m_overPosY < -40)
	{
		m_gravity *= -1;
	}
	m_index = 50;
	if (m_numCount == 1)
	{
		m_minNum = 2;
		m_numCount = m_minNum;
	}
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_setBlend);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//ポーズウィンドウセロファン
	m_setBlend++;

	if (m_setBlend == 140)
	{
		SoundManager::GetInstance().Play(L"GameOver");
	}
	if (m_setBlend < 150)
	{
		return;
	}
	m_fadeColor = true;
	m_setBlend = 150;

	DeleteSoundMem(m_gamePlayBgSound);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Over...", 11, m_clearFont)) / 2,
		100 + m_overPosY, L"Game Over...", 0xf62e36, m_clearFont);								//タイトルの表示

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);

	DrawStringToHandle(widthPos + 50, heightPos + m_index * 2, L"もう一度プレイ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 3, L"タイトルへ戻る", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + m_index * m_numCount, L"▶", 0x00a000, m_guideFont);
}

void SceneMain::DrawUI()
{
	my::MyDrawRectRotaGraph(1200, 300,			//表示座標
		224, 576,			//切り取り左上
		16, 16,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_buttonHandle, true);
	my::MyDrawRectRotaGraph(1200, 340,			//表示座標
		224, 495,			//切り取り左上
		16, 16,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_buttonHandle, true);
	DrawStringToHandle(1200 + 25, 300 - 20, L"...Pause", 0x000000, m_UIFont);
	DrawStringToHandle(1200 + 25, 340 - 20, L"...MoveBack", 0x000000, m_UIFont);
	DrawScore();
}

//右上のスコアを表示させる処理
void SceneMain::DrawScore()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 200);		//黒くする
	//仮の数値
	DrawBox(Game::kScreenWindth - 450, 100, Game::kScreenWindth - 100, 250, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100,
		0xffffff, m_scoreFont, L"STAGE:%d", m_stageNum);
	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100 + 48,
		m_stepColor, m_scoreFont, L"STEP :%d",m_stepNum);
	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100 + 96,
		0xffffff, m_scoreFont, L"LIMIT:%d", m_LimitNum);
}

//コンストラクタ
SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;
	m_pMap = new MapChip;
	m_pEffect = std::make_shared<CreateEffect>();

	m_stageNum = m_pSelect->SelectNum(kNextStage);
	kNextStage = 0;
	//初期化
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(m_stageNum);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();
	//ステージのリミット
	m_LimitNum = m_pInformation->StepLimit();

	if (m_stageNum == 10)
	{
		m_index = 50;
	}

	if (m_numCount == 0)
	{
		if (m_stageNum != 10)
		{
			m_minNum = 1;
			m_numCount = m_minNum;
		}
		else
		{
			m_minNum = 2;
			m_numCount = m_minNum;
		}
	}

	InitLoad();
	InitSound();
}

//デストラクタ
SceneMain::~SceneMain()
{
	delete m_pField;		//メモリの削除
	delete m_pPlayer;		//メモリの削除
	delete m_pInformation;	//メモリの削除
	delete m_pSelect;		//メモリの削除
	delete m_pMap;			//メモリの削除

	//画像の削除
	DeleteGraph(m_handle);
	DeleteGraph(m_backHandle);
	//フォントの削除
	DeleteFontToHandle(m_clearFont);
	DeleteFontToHandle(m_guideFont);
	//サウンドの削除
	DeleteSoundMem(m_gamePlayBgSound);
	SoundManager::GetInstance().StopBGMAndSE();
}

//アップデート処理
void SceneMain::Update(const InputState& input)
{
	PlaySoundMem(m_gamePlayBgSound, DX_PLAYTYPE_LOOP, false);
	ChangeVolumeSoundMem(160 - static_cast<int>(m_fadeValue), m_gamePlayBgSound);
	(this->*m_updateFunc)(input);
}

//ゲームクリアしたときのCursorを動かす処理
void SceneMain::CursorUpdate(const InputState& input)
{
	int count = m_numCount;
	if (input.IsTrigger(InputType::down))
	{
		++m_numCount;
	}
	else if (input.IsTrigger(InputType::up))
	{
		--m_numCount;
	}
	if (m_numCount < m_minNum)
	{
		m_numCount = 3;
	}
	if (m_numCount > 3)
	{
		m_numCount = m_minNum;
	}
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		SoundManager::GetInstance().Play(L"SE1");
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
	if (m_numCount != count)
	{
		SoundManager::GetInstance().Play(L"SE2");
	}
}

//描画処理
void SceneMain::Draw()
{
	//背景とUIの表示
	DrawBackground();
	DrawUI();
	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理
	if (m_pField->GameClear())
	{
		DrawGameClear();
	}
	if (m_gameOverFlag)
	{
		DrawGameOver();
	}
	//普通の描画
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}