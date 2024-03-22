#include "SceneSelect.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
#include"../SoundManager.h"
#include<DxLib.h>

namespace
{
	int kSelectNum = 1;
	constexpr int kMaxStage = 10;
}

//フェード処理
void SceneSelect::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneSelect::NormalUpdate;
		m_fadeValue = 0;
	}
}

//アップデート処理
void SceneSelect::NormalUpdate(const InputState& input)
{
	frame++;
	if (frame > 3)
	{
		m_selectNumIndex += moveindex;
		frame = 0;

		if (m_selectNumIndex < -10 || m_selectNumIndex > -1)
		{
			moveindex *= -1;
		}
	}
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

	//「前へ」ボタンが押されたらタイトルへ
	if (input.IsTrigger(InputType::back))
	{
		//m_manager.ChangeScene(new SceneTitle(m_manager));
	}
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		SoundManager::GetInstance().Play(L"SE1");
		m_updateFunc = &SceneSelect::FadeOutUpdate;
	}
	MoveCursor(input);
	Animation();
}

//フェード処理
void SceneSelect::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {

		m_manager.ChangeScene(new SceneMain(m_manager));
		return;
	}
}

//コンストラクタ
SceneSelect::SceneSelect(SceneManager& manager) :
	SceneBase(manager),
	m_updateFunc(&SceneSelect::FadeInUpdate),
	m_handle(0),
	m_backHandle(0),
	m_BgSound(0),
	m_selectFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1),
	m_fontSize(128)
{
	m_pMap = new MapChip;

	m_handle = my::MyLoadGraph(L"../Date/select.png");		//画像の読み込み

	m_BgSound = LoadSoundMem(L"../Sound/BGM/SelectBg.mp3");

	my::MyFontPath(L"../Font/erizifont.otf"); // 読み込むフォントファイルのパス
	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");

	m_selectFont = CreateFontToHandle(L"えり字", m_fontSize, -1, -1);
	m_guideFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 42, -1, -1);

	m_strTitle = static_cast<int>(strlen("ステージセレクト"));
	m_strEx = static_cast<int>(strlen("Aボタンを押してください"));
	m_strNum = static_cast<int>(strlen("%d"));

	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");
	m_pMap->Load(L"../Date/room.fmf");

	m_boxHandle = my::MyLoadGraph(L"../Date/box.png");		//画像の読み込み

	PlaySoundMem(m_BgSound, DX_PLAYTYPE_LOOP);
}

//デストラクタ
SceneSelect::~SceneSelect()
{
	delete m_pMap;
	DeleteGraph(m_handle);
	DeleteGraph(m_backHandle);
	DeleteSoundMem(m_BgSound);
	DeleteFontToHandle(m_selectFont);
	DeleteFontToHandle(m_guideFont);
}

//アップデート処理
void SceneSelect::Update(const InputState& input)
{
	//ボリュームの設定
	ChangeVolumeSoundMem(255 - static_cast<int>(m_fadeValue), m_BgSound);
	(this->*m_updateFunc)(input);
}

//描画処理
void SceneSelect::Draw()
{
	//背景
	DrawBackground();
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"ステージセレクト", m_strTitle, m_guideFont)) / 2,
		200, L"ステージセレクト", 0x000000, m_guideFont);								//タイトルの表示

	int posX = (Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Aボタンを押してください", m_strEx, m_guideFont)) / 2;
	int posY = Game::kScreenHeight - 100;
	int animeNum = (m_displayCount / 5) + 1;

	my::MyDrawRectRotaGraph(posX - 10, posY + 20,			//表示座標
		32 + (16 * animeNum), 16 + (16 * 2),			//切り取り左上
		16, 16,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_buttonHandle, true);
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"ボタンを押してください", m_strEx, m_guideFont)) / 2,
		posY, L"ボタンを押してください", 0x000000, m_guideFont);	//ガイドの表示

	DrawSelectNum();

	my::MyDrawRectRotaGraph(200,
		Game::kScreenHeight - 32,			//表示座標
		32 * m_animeNum, 32 * 3,			//切り取り左上
		32, 32,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_handle, true);


	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//背景の描画処理
void SceneSelect::DrawBackground()
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

void SceneSelect::DrawSelectNum()
{
	int X = 0;		//何番目の数字か
	int Y = 0;		//何番目の数字か
	int index = m_fontSize + 20;		//文字をずらす
	int posX = ((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"%d", m_strNum, m_selectFont)) / 2)
		- (index * 2);

	int posY = (Game::kScreenHeight / 2) - (index * 2);

	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);		//黒くする
	
	DrawBox(posX - 5,
		posY + index - 5,
		index + posX + index * 4 - 5,
		index + posY + index * 2 - 5, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	for (int i = 0; i < kMaxStage; i++)
	{
		int indexUp = 0;
		int color = 0xffffff;

		X = i % 5;	//改行したときに文字がずれないように割った余りをXに代入する

		//五個ずつで改行する
		if (i % 5 == 0)
		{
			Y++;
		}
		if (i + 1 == kSelectNum)
		{
			indexUp = m_selectNumIndex;
			color = 0xff0000;
		}
		int posNumX = posX + index * X;
		//仮実装で1～9に0を付けて表示する処理
		if (i == kMaxStage - 1)
		{
			DrawFormatStringToHandle(posNumX,
				10 + (posY + index * Y) + indexUp, color, m_selectFont, L"%d", i + 1);	//選択中のステージの表示
		}
		else
		{
			DrawFormatStringToHandle(posNumX,
				10+(posY + index * Y) + indexUp, color, m_selectFont, L"0%d", i + 1);	//選択中のステージの表示
		}
		DrawBox(posX + index * X - 5,
			posY + index * Y - 5,
			index + posX + index * X - 5,
			index + posY + index * Y - 5, 0x00a000, false);
	}
}

int SceneSelect::SelectNum(int num)
{
	kSelectNum = kSelectNum + num;
	int selectNum = 0;
	selectNum = kSelectNum;
	return selectNum;
}

//キーを押されたら移動させる処理
void SceneSelect::MoveCursor(const InputState& input)
{
	int num = kSelectNum;
	if (input.IsTrigger(InputType::right))
	{
		++kSelectNum;
	}
	else if (input.IsTrigger(InputType::left))
	{
		--kSelectNum;
	}
	else if (input.IsTrigger(InputType::up))
	{
		kSelectNum -= 5;
		if (kSelectNum < 1)
		{
			kSelectNum += 10;
		}
		if (kSelectNum > kMaxStage)
		{
			kSelectNum *= -1;
		}
	}
	else if (input.IsTrigger(InputType::down))
	{
		kSelectNum += 5;
		if (kSelectNum < 1)
		{
			kSelectNum += 5;
		}
		if (kSelectNum > kMaxStage)
		{
			kSelectNum -= 10;
		}
	}

	if (kSelectNum < 1)
	{
		kSelectNum = kMaxStage;
	}
	if (kSelectNum > kMaxStage)
	{
		kSelectNum = 1;
	}

	if (num != kSelectNum)
	{
		SoundManager::GetInstance().Play(L"SE2");
	}

}

//下にいる奴のアニメーション処理
void SceneSelect::Animation()
{
	m_freamStop++;
	if (m_freamStop >= 60)
	{
		m_freamAnime++;
		if (m_freamAnime >= 10)
		{
			m_animeNum++;
			m_freamAnime = 0;
		}
		if (m_animeNum > 3)
		{
			m_animeNum = 0;
			m_freamStop = 0;
		}
	}
}
