#include "SceneDebug.h"
#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneMain.h"
#include"SceneResult.h"
#include"../Object/BackGround.h"
SceneDebug::SceneDebug() :
	m_cursolNum(0),
	m_max(6)
{
	// BGM 再生
	Sound::StartBGM(Sound::TitleBGM, 255);
}

SceneDebug::~SceneDebug()
{
	// BGM 停止
	Sound::StopBGM(Sound::TitleBGM);
}

void SceneDebug::Init()
{
	// フェード関係の初期化
	m_isFadeOut = IsFadingOut();

}

void SceneDebug::End()
{

}

SceneBase* SceneDebug::Update()
{
	Sound::LoopBGM(Sound::TitleBGM);
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// デバック用にどこのシーンに飛ぶかを指定する
			if (m_cursolNum == 0)
			{
				return (new SceneTitle);
			}
			else if (m_cursolNum == 1)
			{
				return (new SceneSelect);
			}
			else if (m_cursolNum == 2)
			{
				return (new SceneMain(0));
			}
			else if (m_cursolNum == 3)
			{
				return (new SceneMain(1));
			}
			else if (m_cursolNum == 4)
			{
				return (new SceneMain(2));
			}
			else if (m_cursolNum == 5)
			{
				return (new SceneMain(3));
			}
			else if (m_cursolNum == 6)
			{
				return (new SceneResult(0));
			}
			else
			{
				//DxLib_End();                // ＤＸライブラリ使用の終了処理
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
			StartFadeOut();
		}

		// cursor処理
		if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			Sound::PlaySE(Sound::Cursor);
			m_cursolNum--;
		}
		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			Sound::PlaySE(Sound::Cursor);
			m_cursolNum++;
		}
	}
	// 範囲外の数字に行かないようにする
	if (m_cursolNum > m_max)
	{
		m_cursolNum = 0;
	}
	else if (m_cursolNum < 0)
	{
		m_cursolNum = m_max;
	}

	return this;
}

void SceneDebug::Draw()
{
	DrawString(50,100,"タイトル\n\nセレクト\n\nEasy\n\nNormal\n\nHard\n\nEnd\n\nresult",0xffffff);
	DrawBox(15, 90 + (40 * m_cursolNum), 40, 115 + (40 * m_cursolNum), 0xff0000, true);

	// フェードの表示
	SceneBase::DrawFade();
}