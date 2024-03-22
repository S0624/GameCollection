#include "SceneMapSelect.h"
#include "SceneCharacterSelect.h"
#include "SceneTitle.h"
#include "../Object/Stage/StageBase.h"
#include "../Util/Sound.h"
#include "../Util/DrawFunctions.h"

namespace
{
	// 枠線の縦横サイズ
	constexpr int kFrameSizeX = 500;
	constexpr int kFrameSizeY = 290;

	//**** グラフィック情報 ****//
	const char* kRandFile = "Data/Image/UI/StageSelect/RandStage.png";
	const char* kDinoFile = "Data/Image/UI/StageSelect/Dino.bmp";
	const char* kElfFile = "Data/Image/UI/StageSelect/Elf.bmp";
	const char* kMachoFile = "Data/Image/UI/StageSelect/Macho.bmp";
	const char* kWizardFile = "Data/Image/UI/StageSelect/Wizard.png";

	// フォント
	const char* kFont = "HGP行書体";
}

SceneMapSelect::SceneMapSelect() :
	// コンストラクタ初期化
	m_stageHandle(-1),
	m_bgHandle(-1),
	m_font(-1),
	m_mapNum(0)
{
	m_handle[0] = LoadGraph(kRandFile);		// ランダムステージ
	m_handle[1] = LoadGraph(kDinoFile);		// 恐竜ステージ
	m_handle[2] = LoadGraph(kElfFile);		// エルフステージ
	m_handle[3] = LoadGraph(kMachoFile);	// マッチョステージ
	m_handle[4] = LoadGraph(kWizardFile);	// 魔女ステージ

	// 使用フォント
	m_font = CreateFontToHandle(kFont, 140, -1, -1);
}

SceneMapSelect::~SceneMapSelect()
{
	// グラフィックハンドルの削除
	/*DeleteGraph(m_stageHandle);
	DeleteGraph(m_bgHandle);*/

	
	DeleteFontToHandle(m_font);
}

void SceneMapSelect::Init()
{
	// グラフィックハンドルのロード
	m_stageHandle = LoadGraph("Data/Image/UI/StageSelect/ManyStage.png");
	m_bgHandle = LoadGraph("Data/Image/UI/StageSelect/Bg.png");
	// BGM開始
	Sound::startBgm(Sound::SelectBgm, 200);
}

void SceneMapSelect::End()
{
	// BGMを止める
	Sound::stopBgm(Sound::SelectBgm);

	// ハンドルのデリート
	for (int i = 0; i < 5; i++)
	{
		my::MyDeleteGraph(m_handle[i]);
	}

	my::MyDeleteGraph(m_stageHandle);
	my::MyDeleteGraph(m_bgHandle);
}

SceneBase* SceneMapSelect::Update()
{
	// BGMループ
	Sound::loopBgm(Sound::SelectBgm);

	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();

		if (!IsFading() && m_isFadeOut)
		{
			if (m_mapNum == 0)
			{
				m_mapNum = GetRand(3) + 1;
			}

			return (new SceneCharacterSelect(m_mapNum));
		}
	}

	// 次のシーンへ
	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1, 1) || Pad::IsTrigger(PAD_INPUT_1, 2))
		{
			StartFadeOut();
		}
	}

	// カーソルの移動処理
	if (Pad::IsTrigger(PAD_INPUT_UP, 1) || Pad::IsTrigger(PAD_INPUT_UP, 2))
	{
		if (m_mapNum > 0)
		{
			m_mapNum--;
		}
		else
		{
			m_mapNum = 4;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN, 1) || Pad::IsTrigger(PAD_INPUT_DOWN, 2))
	{
		if (m_mapNum < 4)
		{
			m_mapNum++;
		}
		else
		{
			m_mapNum = 0;
		}

	}

	return this;
}

void SceneMapSelect::Draw()
{
	// デバッグ表示
	DrawString(0, 0, "MapSelect", Color::kWhite);

	// 紺色の背景描画
	DrawGraph(0, 0, m_bgHandle, true);

	// 『Select Stage』の下線描画
	DrawBox(30, 175, 765, 190, 0x00ffff, true);

	// テキスト描画
	DrawFormatStringToHandle(30, 75, 0x800000, m_font, "Select Stage");

	// カーソル位置のステージの拡大描画
	DrawExtendGraph(50, 300, 658, 642, m_handle[m_mapNum], true);

	// カーソル位置の枠線描画
	switch (m_mapNum)
	{
	case 0:
		DrawBox(855, 49, 855 + kFrameSizeX, 49 + kFrameSizeY, 0xffffff, true);
		break;
	case 1:
		DrawBox(855, 410, 855 + kFrameSizeX, 410 + kFrameSizeY, 0xffffff, true); 
		break;
	case 2:
		DrawBox(855, 737, 855 + kFrameSizeX, 737 + kFrameSizeY, 0xffffff, true); 
		break;
	case 3:
		DrawBox(877 + kFrameSizeX, 233, 877 + kFrameSizeX * 2, 233 + kFrameSizeY, 0xffffff, true);
		break;
	case 4:
		DrawBox(877 + kFrameSizeX, 574, 877 + kFrameSizeX * 2, 574 + kFrameSizeY, 0xffffff, true);
		break;
	default:
		break;
	}

	// 各ステージの縮小描画
	DrawGraph(0, 0, m_stageHandle, true);

	SceneBase::DrawFade();
}