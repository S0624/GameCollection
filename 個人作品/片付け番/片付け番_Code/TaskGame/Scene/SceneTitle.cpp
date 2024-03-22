#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../Object/Player.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
#include"../SoundManager.h"
#include<DxLib.h>

//フェード処理
void SceneTitle::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_fadeValue = 0;
	}
}
//更新処理
void SceneTitle::NormalUpdate(const InputState& input)
{
	m_pPlayer->TitleUpdate();
	//アニメーションの処理（ボタン）
	m_animation++;
	if (m_animation > 60)
	{
		m_displayCount++;
		if (m_displayCount >= 5 * 4)
		{
			m_animation = 0;
			m_displayCount = 0;
		}
	}
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		m_updateFunc = &SceneTitle::FadeOutUpdate;
		SoundManager::GetInstance().Play(L"SE1");
	}
}
//フェード処理
void SceneTitle::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval)
	{
		m_manager.ChangeScene(new SceneSelect(m_manager));
		return;
	}
}
//コンストラクタ
SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager),
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_backHandle(0),
	m_roomHandle(0),
	m_BgSound(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	m_pPlayer = new Player;
	my::MyFontPath(L"../Font/851MkPOP_101.ttf");	// 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス
	m_BgSound = LoadSoundMem(L"../Sound/BGM/TitleBg.mp3"); //サウンドの読み込み
	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");	 //背景の読み込み
	m_roomHandle = my::MyLoadGraph(L"../Date/texture.png");	 //背景の読み込み
	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");	//UIの画像の読み込み
	m_titleHandle = my::MyLoadGraph(L"../Date/Title.png");		//タイトル画像の読み込み
	m_guideFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 42, -1, -1);	//フォントの読み込み
	m_strTitle = static_cast<int>(strlen("片付け番"));				//文字列の長さの読み込み
	m_strEx = static_cast<int>(strlen("Aボタンを押してください"));	//文字列の長さの読み込み
	m_strNum = static_cast<int>(strlen("%d"));						//文字列の長さの読み込み
	m_pMap->Load(L"../Date/room.fmf");								//背景データの読み込み
	SoundManager::GetInstance().PlayMusic(m_BgSound);				//SEの読み込み
}
//デストラクタ
SceneTitle::~SceneTitle()
{
	delete m_pMap;						//メモリの削除
	delete m_pPlayer;					//メモリの削除
	DeleteGraph(m_backHandle);			//画像の削除
	DeleteGraph(m_roomHandle);			//画像の削除
	DeleteSoundMem(m_BgSound);			//音の削除
	DeleteFontToHandle(m_TitleFont);	//フォントの削除
	DeleteFontToHandle(m_guideFont);	//フォントの削除
}
//更新処理
void SceneTitle::Update(const InputState& input)
{
	ChangeVolumeSoundMem(255 - static_cast<int>(m_fadeValue), m_BgSound);	//フェードに合わせて音もフェードする
	(this->*m_updateFunc)(input);
}
//描画処理
void SceneTitle::Draw()
{
	int posX = (Game::kScreenWindth -
			GetDrawStringWidthToHandle(L"Aボタンを押してください", m_strEx, m_guideFont)) / 2;
	int posY = Game::kScreenHeight - 200;
	int animeNum = (m_displayCount / 5) + 1;
	//背景
	DrawBackground();
	m_pPlayer->Draw();
	//タイトルの表示
	DrawRotaGraph((Game::kScreenWindth  / 2), 300,
		0.5f,0,
		m_titleHandle, true);
	//ボタンの処理（アニメーションの追加）
	my::MyDrawRectRotaGraph(posX - 5, posY + 25,			//表示座標
		32 + (16 * animeNum), 16 + (16 * 2),			//切り取り左上
		16, 16,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_buttonHandle, true);
	DrawStringToHandle(posX + 5, posY, L" ボタンを押してください", 0xffffff, m_guideFont);	//ガイドの表示
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
//背景描画
void SceneTitle::DrawBackground()
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
			auto roomchipId = mapData[1][static_cast<__int64>(chipY) * mW + chipX];
			if (roomchipId == 0 || roomchipId == 2)
			{
				my::MyDrawRectRotaGraph((chipX * 32) - 650, chipY * 32 - 125,
					(roomchipId % 12) * 16,
					(roomchipId / 8) * 16,
					16, 16,
					2.0f, 0,
					m_roomHandle, true);
			}
		}
	}
}
