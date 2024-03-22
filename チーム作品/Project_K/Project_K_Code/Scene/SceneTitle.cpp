#include "SceneTitle.h"
#include "SceneMapSelect.h"
#include "../LogoRotation.h"
#include "../Util/Sound.h"
#include "../UIAnimation.h"
#include "../ButtonNo.h"

SceneTitle::SceneTitle():
	m_pLogo(nullptr)
{
	// ロゴ回転用だが後回しなのでまだ出来ていない。
	m_pLogo = new LogoRotation;
	m_pUiAnim = new UIAnimation;
}

SceneTitle::~SceneTitle()
{
	delete m_pLogo;
	delete m_pUiAnim;
}

void SceneTitle::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::TitleBgm, 200);

	m_isFadeOut = IsFadingOut();
	m_pLogo->Init();

	m_pUiAnim->AddButton(Game::kScreenWidth/2, Game::kScreenHeight - 150, 10, 3, ButtonNo::A);

	//m_pUiAnim->AddButton(Game::kScreenWidth / 2, 100 + 100, 2, 3, ButtonNo::Dinosaur);
	//m_pUiAnim->AddButton(Game::kScreenWidth / 2, 100 + 200,       10, 3, ButtonNo::Elf);
	//m_pUiAnim->AddButton(Game::kScreenWidth / 2, 100 + 300, 10, 3, ButtonNo::Kinnikurou);
	//m_pUiAnim->AddButton(Game::kScreenWidth / 2, 100 + 400, 10, 3, ButtonNo::Witch);

	m_pUiAnim->Init();
}

void SceneTitle::End()
{
	// BGM 停止
	Sound::stopBgm(Sound::TitleBgm);
	m_pUiAnim->End();
}

SceneBase* SceneTitle::Update()
{
	Sound::loopBgm(Sound::TitleBgm);
	m_pLogo->Update();
	m_pUiAnim->Update();


	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMapSelect);
		}
	}

	// フェードインアウトしていない
	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1,1) || Pad::IsTrigger(PAD_INPUT_1, 2))
		{
			StartFadeOut();
		}
	}
	

	return this;
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);

	m_pLogo->Draw();
	m_pUiAnim->Draw();

	SceneBase::DrawFade();
}


