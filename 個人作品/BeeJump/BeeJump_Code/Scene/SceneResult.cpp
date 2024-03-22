#include "SceneResult.h"
#include"../Common.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneSelect.h"
#include"../Object/BackGround.h"
#include <string>
#include <fstream>
#include <sstream>

/// <summary>
/// コンストラクタ
/// </summary>
SceneResult::SceneResult(int score) :
	m_scoreHandle(0),
	m_guideHandle(0),
	m_frameHandle(0),
	m_selectNum(0),
	m_gamefont(0),
	m_guidefont(0),
	m_seFlag(false),
	m_cursolNum(0),
	m_maxScore(0),
	m_nowScore(score)
{
	// 初期化関係
	m_pBack = new BackGround();
}
/// <summary>
/// デストラクタ
/// </summary>
SceneResult::~SceneResult()
{
	// BGM 停止
	Sound::StopBGM(Sound::ResultBGM);
	// 削除
	delete(m_pBack);

	DeleteGraph(m_scoreHandle);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);

	DeleteFontToHandle(m_gamefont);
	DeleteFontToHandle(m_guidefont);
}
/// <summary>
/// 初期化処理
/// </summary>
void SceneResult::Init()
{
	m_isFadeOut = IsFadingOut();//フェードの初期化

	// 画像の読み込み
	m_scoreHandle = LoadGraph("Data/Img/ResultPlate.png");
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_gamefont = CreateFontToHandle("yosugara ver12", 100, -1, -1);// 上の表示する文字に使用するフォン
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン
}
/// <summary>
/// エンド処理
/// </summary>
void SceneResult::End()
{

}

SceneBase* SceneResult::Update()
{
	Sound::LoopBGM(Sound::ResultBGM);
	m_pBack->Update(); // 背景の更新処理
	// ファイルの読み込みをする
	FileRead();

	// フェードインアウトしていなかったら
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// 今獲ったスコアが保存されているスコアより大きかったら変更する
			if (m_nowScore > m_maxScore)
			{
				FileGenerate();
			}
			// resultSceneに飛ぶ
			if (m_cursolNum == 0)
			{
				return (new SceneMain(Endless));
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
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::PushButton);
			// フェードを開始する
			StartFadeOut();
		}
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

void SceneResult::Draw()
{
	m_pBack->Draw();	// 背景の表示

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);			// ブレンドモードをいじってスコアのパネルを半透明にする
	// スコア版の表示
	DrawRectRotaGraph(Game::kScreenWidth / 2, 230, 
		0,0,
		1000,1000,
		1.0f,0.0f,
		m_scoreHandle, true);
	// スコアの表示
	DrawStringToHandle(450,100, "Score", 0x000000,m_guidefont);
	DrawStringToHandle(450, 250, "HightScore", 0x000000,m_guidefont);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 100,
		100, 0x000000, m_gamefont, "%d", m_nowScore);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 100,
		250, 0x000000, m_gamefont, "%d", m_maxScore);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	// 説明のボタンの表示
	DrawGuide();

	// フェードの表示
	SceneBase::DrawFade();
}

void SceneResult::DrawGuide()
{
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
}
// ファイルの生成
void SceneResult::FileGenerate()
{
	std::ofstream writingFile;
	// 生成するファイル名
	std::string filename = "Data/ScoreData.txt";
	writingFile.open(filename, std::ios::out);
	// 今獲ったスコアを書き込む
	writingFile << m_nowScore << std::endl;
	// ファイルを閉じる
	writingFile.close();
}
// ファイルの読み込み
void SceneResult::FileRead()
{
	std::ifstream readingFile;
	// ファイル名
	std::string filename = "Data/ScoreData.txt";
	readingFile.open(filename, std::ios::in);
	std::string readingLineBuffer;
	while (std::getline(readingFile, readingLineBuffer)) {
		// string型をint型へ
		m_maxScore = atoi(readingLineBuffer.c_str());
	}
}
