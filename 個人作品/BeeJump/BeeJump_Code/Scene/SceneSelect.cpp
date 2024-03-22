#include "SceneSelect.h"
#include"../Common.h"
#include "SceneSelect.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"../Object/BackGround.h"

SceneSelect::SceneSelect() :
	m_selectHandle(0),
	m_optionHandle(0),
	m_guideHandle(0),
	m_frameDown(0),
	m_frameWidth(0),
	m_guidefont(0),
	m_test(-150),
	m_option(0),
	m_optinPush(false),
	m_optionCursorNum(0),
	m_cursorNum(0),
	m_max(3)
{
	m_pBack = new BackGround();
}

SceneSelect::~SceneSelect()
{
	// BGM 停止
	Sound::StopBGM(Sound::SelectBGM);
	delete(m_pBack);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_optionHandle);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameWidth);
	DeleteGraph(m_frameDown);
	DeleteFontToHandle(m_guidefont);
}

void SceneSelect::Init()
{
	// フェード関係の初期化
	m_isFadeOut = IsFadingOut();

	m_selectHandle = LoadGraph("Data/Img/Select1.png");
	m_optionHandle = LoadGraph("Data/Img/Option.png");
	m_guideHandle = LoadGraph("Data/Img/Guide.png");
	m_frameWidth = LoadGraph("Data/Img/SelectFrame1.png");
	m_frameDown = LoadGraph("Data/Img/SelectFrame2.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン
}

void SceneSelect::End()
{

}

SceneBase* SceneSelect::Update()
{
	m_pBack->Update(); // 背景の更新処理
	Sound::LoopBGM(Sound::SelectBGM);
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
#ifdef true
			return (new SceneMain(m_cursorNum));
#endif // true
			// シーン移行
			if (m_optinPush)
			{
				return (new SceneTitle);
			}
			else
			{
				return (new SceneMain(m_cursorNum));
			}
		}
	}

	// フェードインアウトしていなかったら
	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::PushButton);
			// HACK 力業 of 力業なので後で治す
			if (!m_option || !m_optinPush)
			{
				StartFadeOut();
			}
			if (m_option)
			{
				if(m_optinPush)
				{
					m_optinPush = false;
					m_test = -150;
				}
				else
				{
					m_optinPush = true;
				}
			}
		}
		if (Pad::IsTrigger(PAD_INPUT_2))
		{
			Sound::PlaySE(Sound::PushButton);
			if (!m_optinPush)
			{
				StartFadeOut();
				return (new SceneTitle);
			}
			else
			{
				m_optinPush = false;
				m_test = -150;
			}
		}
		UpdateCursol();
		// 範囲外の数値にならないように調整
		if (m_cursorNum > m_max)
		{
			m_cursorNum = 0;
		}
		if (m_cursorNum < 0)
		{
			m_cursorNum = m_max;
		}
	}

	return this;
}

void SceneSelect::Draw()
{
	m_pBack->Draw();	// 背景の表示

	// select画面の表示 
	DrawGraph(0, 0, m_selectHandle, true);

	// HACK テスト実装です
	DrawStringToHandle(190,
		330, "Easy", 0xffffff, m_guidefont);
	DrawStringToHandle(500,
		330, "Normal", 0xffffff, m_guidefont);
	DrawStringToHandle(880,
		330, "Hard", 0xffffff, m_guidefont);
	DrawStringToHandle(1180,
		330, "Endless", 0xffffff, m_guidefont);

	/*if (!m_option && m_cursorNum == 3)
	{
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("じゅんびちゅうだよ", 24, m_guidefont)) / 2,
			10, "じゅんびちゅうだよ", 0xff0000, m_guidefont);
	}*/

	//DrawBox(50 + 200 * (1 + m_cursorNum), 200, 50 + 200 * (1 + m_cursorNum) + 300, 200 + 500,0xff0000,false);
	
	//フラグによってフレームの画像を変える
	// フレームを変える
	if (!m_option)
	{
		DrawGraph(116 + (345 * m_cursorNum), 87, m_frameWidth, true);
	}
	else
	{
		DrawGraph(443, 658, m_frameDown, true);
	}
	OptionDraw();
	// フェードの表示
	SceneBase::DrawFade();
}

void SceneSelect::UpdateCursol()
{
	// カーソルの処理
	// 左
	if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		// 効果音を流す
		Sound::PlaySE(Sound::Cursor);
		// カーソルを変える
		m_cursorNum--;
	}
	// 右
	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// 効果音を流す
		Sound::PlaySE(Sound::Cursor);
		// カーソルを変える
		m_cursorNum++;
	}
	// 下
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		// 効果音を流す
		Sound::PlaySE(Sound::Cursor);
		// カーソルを変える
		CursolFlag();
		// オプションのカーソルの処理
		CursolOption(1);

	}
	// 上
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		// 効果音を流す
		Sound::PlaySE(Sound::Cursor);
		// カーソルを変える
		CursolFlag();
		// オプションのカーソルの処理
		CursolOption(-1);
	}
}

void SceneSelect::CursolFlag()
{
	// cursorの位置がoptionにあったらフラグを変える
	if (!m_optinPush)
	{
		if (m_option)
		{
			m_option = false;
		}
		else
		{
			m_option = true;
		}
	}
}

void SceneSelect::CursolOption(int cursol)
{
	// カーソルを選択されていたら
	if (m_optinPush)
	{
		// カーソルを動かす
		m_optionCursorNum += cursol;
	}
	// 範囲外に行かないように範囲を設定
	if (m_optionCursorNum < 0)
	{
		m_optionCursorNum = 3;
	}
	else if (m_optionCursorNum > 3)
	{
		m_optionCursorNum = 0;
	}
}

void SceneSelect::OptionDraw()
{

#ifdef  true // 実装したかったけどいったん非表示
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("Option", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 170, "Option", 0xffffff, m_guidefont);
#endif
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("Title", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 170, "Title", 0xffffff, m_guidefont);
	// optionの表示
#ifdef  true // 実装したかったけどいったん非表示
	if (m_optinPush)
	{

		// HACK なおしたい
		m_test += 30;
		if (m_test > 450)
		{
			m_test = 450;
		}

		SetDrawBlendMode(DX_BLENDMODE_MULA, 70);			// 見やすいようにちょっと黒フィルターをかける
		DrawBox(0, 0,
			Game::kScreenWidth, Game::kScreenHeight,
			0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

		DrawRectRotaGraph(Game::kScreenWidth / 2, m_test,
			0, 0,
			838, 486,
			1.0f, 0.0f,
			m_optionHandle, true,
			false, false);
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("そうさ\nおと\n(.A.)\nもどる", 24, m_guidefont)) / 2,
			m_test - 150, "そうさ\nおと\n(.A.)\nもどる", 0xffffff, m_guidefont);

		SelectOptionDraw();

		DrawFormatString(0, 0, 0xffffff, "%d", m_optionCursorNum);
	}
#endif
}

void SceneSelect::SelectOptionDraw()
{
	//m_optionCursorNum = 0;
	// 番号によって表示を変える
	if (m_optionCursorNum == 0)
	{
		/*DrawRectRotaGraph(Game::kScreenWidth / 2, m_test,
			0, 0,
			838, 486,
			1.0f, 0.0f,
			m_guideHandle, true,
			false, false);*/
	}
}
