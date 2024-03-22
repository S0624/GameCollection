#include "SelectUI.h"
#include"game.h"
#include"DrawFunctions.h"
#include"DxLib.h"
#include"FontFunction.h"
#include "../Object/Stage/StageBase.h"
#include<cmath>

namespace
{
	int kBottomStandard = Game::kScreenHeight - 150; // 下の基準線（選択プレイヤーの位置を下で合わせる）
	int kBottomCenter = 0; // 下の基準線（選択プレイヤーの位置を下で合わせる）
	int kSelectFont = 0;// 上に表示するのに使用するフォント
	int kGuideFont = 0;// 下に表示するのに使用するフォント
	int kHiraganaFont = 0;// ひらがな用フォント
	int kEnglishFont = 0;// 英語フォント
	const char* kSelectText = "character select";// 上に表示する文字
	const char* kGuideText = " ボタンでけってい";// 下に表示する文字
	const char* kDinoText = "だいなそー";// 表示する文字
	const char* kElfText = "Elf";// 表示する文字
	const char* kKinText = "きんにくん";// 表示する文字
	const char* kWitchText = "Witch";// 表示する文字

	int kColor1P = 0xffffff;// 1Pが使用する色
	int kColor2P = 0xffffff;// 2Pが使用する色

	float kSinRate = 0.0f;// カーソルの回転に使用
}

SelectUI::SelectUI() :
	m_pStageBase(nullptr),
	m_frameHandle(0),
	m_buttonHandle(0),
	m_dinoHandle(0),
	m_elfHandle(0),
	m_kinnikuHandle(0),
	m_witchHandle(0),
	m_frameCount1(0),
	m_indexWidth1(0),
	m_indexHight1(0),
	m_frameCount2(0),
	m_indexWidth2(0),
	m_indexHight2(0),
	m_buttonAnimframe(0),
	m_animInterval(0),
	m_buttonIndexWidth(0),
	m_centerPos1P(0),
	m_centerPos2P(0),
	m_cursor1(0),
	m_cursor2(0),
	m_cursorFlag1(false),
	m_cursorFlag2(false),
	m_cursolHeight(0)
{
	m_pStageBase = nullptr;
}

SelectUI::~SelectUI()
{
	// メモリの開放
	delete m_pStageBase;
	// 画像のデリート処理
	my::MyDeleteGraph(m_frameHandle);
	my::MyDeleteGraph(m_buttonHandle);
	my::MyDeleteGraph(m_dinoHandle);
	my::MyDeleteGraph(m_elfHandle);
	my::MyDeleteGraph(m_kinnikuHandle);
	my::MyDeleteGraph(m_witchHandle);

	// フォントのデリーtp
	DeleteFontToHandle(kSelectFont);
	DeleteFontToHandle(kHiraganaFont);
	DeleteFontToHandle(kEnglishFont);
	DeleteFontToHandle(kGuideFont);
}

void SelectUI::Init(int StageNo)
{
	m_pStageBase = new StageBase(StageNo);
	m_pStageBase->Init();
	InitLoad();// 画像のロード
	InitFont();// フォントの初期化
	InitChar();// キャラクタの初期化処理
}

void SelectUI::Update()
{
	UpdateChar(m_cursor1, 1);// カーソルによってアップデート
	UpdateChar(m_cursor2, 2);// カーソルによってアップデート 
	UpdateAnimation();// アニメーション
	UpdateCursor();
}

void SelectUI::Draw()
{
	m_pStageBase->Draw();
	SetDrawBlendMode(DX_BLENDMODE_MULA, 70);			// 見やすいようにちょっと黒フィルターをかけてる（いらない気もするが）
	// ステージの描画
	DrawBox(0, 0,
		Game::kScreenWidth, Game::kScreenHeight,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawChar();// キャラの描画
	DrawLetter();// 文字の描画
	DrawCursor();// カーソルの描画処理
}

void SelectUI::InitLoad()
{
	// 画像のロード処理
	m_frameHandle = my::MyLoadGraph("Data/Image/UI/frame.png");// フレーム
	m_buttonHandle = my::MyLoadGraph("Data/Image/UI/button.png");// フレーム
	m_dinoHandle = my::MyLoadGraph("Data/Image/Player/kyouryuu/Enemy.png");// 恐竜
	m_elfHandle = my::MyLoadGraph("Data/Image/Player/Elf/Elf.png");// エルフ
	m_kinnikuHandle = my::MyLoadGraph("Data/Image/Player/Kinnikurou/Idle.png");// きんにくん
	m_witchHandle = my::MyLoadGraph("Data/Image/Player/Witch/Witch.png");// 魔女
}

void SelectUI::InitFont()
{
	font::MyFontPath("Data/Font/Valentina-Regular.ttf");
	kSelectFont = CreateFontToHandle("Valentina", 100, -1, -1);// 上の表示する文字に使用するフォン
	kEnglishFont = CreateFontToHandle("Valentina", 50, -1, -1);// 英語のキャラ用フォント
	font::MyFontPath("Data/Font/851letrogo_007.ttf");
	kGuideFont = CreateFontToHandle("851レトロゴ", 50, -1, -1);// 上の表示する文字に使用するフォン
	kHiraganaFont = CreateFontToHandle("851レトロゴ", 50, -1, -1);// ひらがなのキャラ用フォント
	kBottomCenter = (Game::kScreenWidth - GetDrawStringWidthToHandle(kGuideText, 16, kGuideFont)) / 2;// 下の文字の中心位置
}

void SelectUI::InitChar()
{
	// P1の初期化
	m_player1.m_imgWidth = 0;
	m_player1.m_imgHight = 0;
	m_player1.m_imgSize = 0;
	m_player1.m_posY = 0;
	m_player1.m_maxWidth = 0;
	m_player1.m_maxHight = 0;
	m_player1.m_animFrame = 0;
	m_player1.m_text = kDinoText;
	m_player1.m_font = kHiraganaFont;
	m_temp = m_player1;// ここでまとめて初期化
	m_player2 = m_player1;// ついでに2Pもまとめて初期化

	// 恐竜くんの初期化
	InitCharas(m_dino, 640, 222, 2, 9, 2, 5, kDinoText, kHiraganaFont);

	// エルフくんの初期化
	InitCharas(m_elf, 288, 128, 7, 12, 0, 5, kElfText, kEnglishFont);

	// きんにくんの初期化
	m_kinnniku.m_imgWidth = 18;
	m_kinnniku.m_imgHight = 23;
	m_kinnniku.m_imgSize = 10;
	float kinPos = kBottomStandard - (m_kinnniku.m_imgHight * m_kinnniku.m_imgSize / 2);
	m_kinnniku.m_posY = kinPos;
	m_kinnniku.m_maxHight = 0;
	m_kinnniku.m_maxWidth = 2;
	m_kinnniku.m_animFrame = 60;
	m_kinnniku.m_text = kKinText;
	m_kinnniku.m_font = kHiraganaFont;
	//InitCharas(m_kinnniku, 18, 23, 10, 0, 2, 60, kKinText, kHiraganaFont);

	// 魔女の初期化
	InitCharas(m_witch, 48, 48, 6, 1, 8, 15, kWitchText, kEnglishFont);

}

void SelectUI::UpdateAnimation()
{
	// 1Pのアニメーション
	m_frameCount1++;
	if (m_player1.m_animFrame <= m_frameCount1)
	{
		m_indexWidth1++;
		m_frameCount1 = 0;
	}
	if (m_player1.m_maxWidth <= m_indexWidth1)
	{
		m_indexHight1++;
		m_indexWidth1 = 0;
		m_frameCount1 = 0;
	}
	if (m_player1.m_maxHight <= m_indexHight1)
	{
		m_indexHight1 = 0;
	}
	// 2Pのアニメーション
	m_frameCount2++;
	if (m_player2.m_animFrame <= m_frameCount2)
	{
		m_indexWidth2++;
		m_frameCount2 = 0;
	}
	if (m_player2.m_maxWidth <= m_indexWidth2)
	{
		m_indexHight2++;
		m_indexWidth2 = 0;
		m_frameCount2 = 0;
	}
	if (m_player2.m_maxHight <= m_indexHight2)
	{
		m_indexHight2 = 0;
	}

	// buttonのアニメーション
	m_animInterval++;
	if (m_animInterval > 60 * 2)
	{
		m_buttonAnimframe++;
		if (m_buttonAnimframe > 5)
		{
			m_buttonIndexWidth++;
			m_buttonAnimframe = 0;
		}
		if (m_buttonIndexWidth > 4)
		{
			m_buttonIndexWidth = 0;
			m_animInterval = 0;
		}
	}
}

void SelectUI::UpdateChar(int cursor, int selectNum)
{
	m_centerPos1P = GetDrawStringWidthToHandle(m_player1.m_text, 10, m_player1.m_font) / 2;
	m_centerPos2P = GetDrawStringWidthToHandle(m_player2.m_text, 10, m_player2.m_font) / 2;
	// カーソルがいる位置で処理を変更する
	if (cursor == 0)
	{
		// 恐竜くん
		m_temp.m_imgWidth = m_dino.m_imgWidth;
		m_temp.m_imgHight = m_dino.m_imgHight;
		m_temp.m_imgSize = m_dino.m_imgSize;
		m_temp.m_posY = m_dino.m_posY;
		m_temp.m_maxWidth = m_dino.m_maxWidth;
		m_temp.m_maxHight = m_dino.m_maxHight;
		m_temp.m_animFrame = m_dino.m_animFrame;
		m_temp.m_handle = m_dinoHandle;
		m_temp.m_text = m_dino.m_text;
		m_temp.m_font = m_dino.m_font;
	}
	if (cursor == 1)
	{
		// エルフくん
		m_temp.m_imgWidth = m_elf.m_imgWidth;
		m_temp.m_imgHight = m_elf.m_imgHight;
		m_temp.m_imgSize = m_elf.m_imgSize;
		m_temp.m_posY = m_elf.m_posY;
		m_temp.m_maxWidth = m_elf.m_maxWidth;
		m_temp.m_maxHight = m_elf.m_maxHight;
		m_temp.m_animFrame = m_elf.m_animFrame;
		m_temp.m_handle = m_elfHandle;
		m_temp.m_text = m_elf.m_text;
		m_temp.m_font = m_elf.m_font;
	}
	if (cursor == 2)
	{
		// きんにくん
		m_temp.m_imgWidth = m_kinnniku.m_imgWidth;
		m_temp.m_imgHight = m_kinnniku.m_imgHight;
		m_temp.m_imgSize = m_kinnniku.m_imgSize;
		m_temp.m_posY = m_kinnniku.m_posY;
		m_temp.m_maxWidth = m_kinnniku.m_maxWidth;
		m_temp.m_maxHight = m_kinnniku.m_maxHight;
		m_temp.m_animFrame = m_kinnniku.m_animFrame;
		m_temp.m_handle = m_kinnikuHandle;
		m_temp.m_text = m_kinnniku.m_text;
		m_temp.m_font = m_kinnniku.m_font;
	}
	if (cursor == 3)
	{
		// 魔女
		m_temp.m_imgWidth = m_witch.m_imgWidth;
		m_temp.m_imgHight = m_witch.m_imgHight;
		m_temp.m_imgSize = m_witch.m_imgSize;
		m_temp.m_posY = m_witch.m_posY;
		m_temp.m_maxWidth = m_witch.m_maxWidth;
		m_temp.m_maxHight = m_witch.m_maxHight;
		m_temp.m_animFrame = m_witch.m_animFrame;
		m_temp.m_handle = m_witchHandle;
		m_temp.m_text = m_witch.m_text;
		m_temp.m_font = m_witch.m_font;
	}
	// 渡した数によってPADがどっちかを分岐させる
	if (selectNum == 1)
	{
		m_player1 = m_temp;
	}
	else
	{
		m_player2 = m_temp;
	}
	// 決定されていたら各プレイヤーの色にする
	// そうではなかったらデフォルトで白を渡す
	if (m_cursorFlag1)// 1P
	{
		kColor1P = 0xff0000;
	}
	else
	{
		kColor1P = 0xffffff;
	}
	if (m_cursorFlag2)// 2P
	{
		kColor2P = 0x0000ff;
	}
	else
	{
		kColor2P = 0xffffff;
	}
}

void SelectUI::UpdateCursor()
{
	// メモ
	// カーソルの移動処理
	// まずカーソルがどこにいるか受け取る
	// 次にカーソルが動いた場合適当にゆっくり動かす処理

	// カーソルの回転させるために++する
	kSinRate += 0.1f;
	m_cursolHeight = sinf(kSinRate) * 30.0f;	// 実際にはHeight/2
}

void SelectUI::DrawChar()
{
	// フレーム
	for (int i = 1; i <= 4; i++)
	{
		int pos = 200;
		my::MyDrawRectRotaGraph(
			static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(48) + pos * i,//プレイヤーの位置
			0, 0,// 画像の右上
			48, 48,
			4,
			DX_PI_F * 2,
			m_frameHandle,
			true,
			false);
	}
	// button
	my::MyDrawRectRotaGraph(
		static_cast<int>(kBottomCenter - 20), static_cast<int>(Game::kScreenHeight - 103),//プレイヤーの位置
		16 * (m_buttonIndexWidth + 1), 192,// 画像の右上
		16, 16,
		4.0f,
		DX_PI_F * 2,
		m_buttonHandle,
		true,
		false);

	// アイコン(恐竜くん)
	my::MyDrawRectRotaGraph(
		static_cast<int>(Game::kScreenWidth / 2 + 270), static_cast<int>(200 - 25),//プレイヤーの位置
		320, 0,// 画像の右上
		450, 180,
		1.5,
		DX_PI_F * 2,
		m_dinoHandle,
		true,
		false);
	// アイコン(Elfくん)
	my::MyDrawRectRotaGraph(
		static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(200 + 10),//プレイヤーの位置
		0, 0,// 画像の右上
		288, 100,
		6,
		DX_PI_F * 2,
		m_elfHandle,
		true,
		false);
	// アイコン(きんにくん)
	my::MyDrawRectRotaGraph(
		static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(600 + 50),//プレイヤーの位置
		0, 0,// 画像の右上
		18, 18,
		7,
		DX_PI_F * 2,
		m_kinnikuHandle,
		true,
		false);
	// アイコン(まじょ)
	my::MyDrawRectRotaGraph(
		static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(840),//プレイヤーの位置
		0, 0,// 画像の右上
		48, 30,
		5,
		DX_PI_F * 2,
		m_witchHandle,
		true,
		false);


	// 1Pが選択してるキャラ
	my::MyDrawRectRotaGraph(
		400, static_cast<int>(m_player1.m_posY),//プレイヤーの位置
		m_player1.m_imgWidth * m_indexWidth1, m_player1.m_imgHight * m_indexHight1,// 画像の右上
		m_player1.m_imgWidth, m_player1.m_imgHight,// 画像の切り取り
		m_player1.m_imgSize,// 画像の拡大率
		DX_PI_F * 2,// 回転
		m_player1.m_handle,// 画像
		true,// 反転
		false);// 透過

	// 2Pが選択してるキャラ
	my::MyDrawRectRotaGraph(
		Game::kScreenWidth - 400, static_cast<int>(m_player2.m_posY),//プレイヤーの位置
		m_player2.m_imgWidth * m_indexWidth2, m_player2.m_imgHight * m_indexHight2,// 画像の右上
		m_player2.m_imgWidth, m_player2.m_imgHight,// 画像の切り取り
		m_player2.m_imgSize,// 画像の拡大率
		DX_PI_F * 2,// 回転
		m_player2.m_handle,// 画像
		true,// 反転
		true);// 透過
}

void SelectUI::DrawLetter()
{
	// キャラクターセレクトの表示
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle(kSelectText, 16, kSelectFont)) / 2,
		50, kSelectText, 0xffffff, kSelectFont);
	// 指示文（guide分）の表示
	DrawStringToHandle(kBottomCenter,
		Game::kScreenHeight - 120, kGuideText, 0xffffff, kGuideFont);

	// 1Pの名前表示
	DrawStringToHandle(400 - m_centerPos1P,
		300, m_player1.m_text, kColor1P, m_player1.m_font);
	// 2Pの名前表示
	DrawStringToHandle(Game::kScreenWidth - 400 - m_centerPos2P,
		300, m_player2.m_text, kColor2P, m_player2.m_font);
}

void SelectUI::DrawCursor()
{
	int posY1P = 30 + 200 * (m_cursor1 + 1);
	//int posY = 48 + 200 * (m_cursor1 + 1);
	int posY2P = 30 + 200 * (m_cursor2 + 1);
	//if (cursorNext == i)

	DrawTriangle(860, posY1P + 30,
		830, posY1P + 30 - m_cursolHeight,
		830, posY1P + 30 + m_cursolHeight, 0xff0000, true);
	DrawTriangle(860, posY1P + 30,
		830, posY1P + 30 - m_cursolHeight,
		830, posY1P + 30 + m_cursolHeight, kColor1P, false);

	DrawTriangle(1070, posY2P + 30,
		1100, posY2P + 30 - m_cursolHeight,
		1100, posY2P + 30 + m_cursolHeight, 0x0000ff, true);
	DrawTriangle(1070, posY2P + 30,
		1100, posY2P + 30 - m_cursolHeight,
		1100, posY2P + 30 + m_cursolHeight, kColor2P, false);
}

void SelectUI::InitCharas(CharData& charaData, int imgWidth, int imgHight, float imgSize, int maxWidth, int maxHight, int animFrame, const char* text, int font)
{
	// 各キャラクターの初期化
	charaData.m_imgWidth = imgWidth;
	charaData.m_imgHight = imgHight;
	charaData.m_imgSize = imgSize;
	float charposY = kBottomStandard - (charaData.m_imgHight * charaData.m_imgSize / 2);
	charaData.m_posY = charposY;
	charaData.m_maxWidth = maxWidth;
	charaData.m_maxHight = maxHight;
	charaData.m_animFrame = animFrame;
	charaData.m_text = text;
	charaData.m_font = font;
}

