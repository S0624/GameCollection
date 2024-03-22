#include "SceneCharacterSelect.h"
#include "SceneMain.h"
#include "SceneMapSelect.h"
#include "../Util/Pad.h"
#include "../System/CharaChoice.h"
#include "../Object/Player/Dinosaur/Dinosaur.h"
#include "../Object/Player/Elf/Elf.h"
#include "../Object/Player/Kinnikurou/Kinnikurou.h"
#include "../Object/Player/Witch/Witch.h"
#include "../Util/SelectUI.h"
#include "../Util/Sound.h"

SceneCharacterSelect::SceneCharacterSelect(int StageNo) :
	m_stageNo(StageNo)
{
	m_Player[0] = nullptr;
	m_Player[1] = nullptr;
	m_CharaChoice = new CharaChoice;
	m_pUi = new SelectUI;
}

SceneCharacterSelect::~SceneCharacterSelect()
{
	delete m_CharaChoice;
	delete m_pUi;
}

void SceneCharacterSelect::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::SelectBgm, 200);

	m_pUi->Init(m_stageNo);
}

void SceneCharacterSelect::End()
{
	// BGM 停止
	Sound::stopBgm(Sound::SelectBgm);
}

SceneBase* SceneCharacterSelect::Update()
{
	// BGM ループ
	Sound::loopBgm(Sound::SelectBgm);
	m_CharaChoice->Update();
	m_pUi->Update();
	m_pUi->SetCursor(m_CharaChoice->GetChackChara1(), m_CharaChoice->GetChackChara2());
	m_pUi->SetCursorFlag(m_CharaChoice->GetDecision1(), m_CharaChoice->GetDecision2());

	if (m_CharaChoice->GetDecision1() && m_CharaChoice->GetDecision2() && !m_isBackScene)
	{
		if (m_CharaChoice->GetChackChara1() == 0) m_Player[0] = new Dinosaur;
		if (m_CharaChoice->GetChackChara1() == 1) m_Player[0] = new Elf;
		if (m_CharaChoice->GetChackChara1() == 2) m_Player[0] = new Kinnikurou;
		if (m_CharaChoice->GetChackChara1() == 3) m_Player[0] = new Witch;

		if (m_CharaChoice->GetChackChara2() == 0) m_Player[1] = new Dinosaur;
		if (m_CharaChoice->GetChackChara2() == 1) m_Player[1] = new Elf;
		if (m_CharaChoice->GetChackChara2() == 2) m_Player[1] = new Kinnikurou;
		if (m_CharaChoice->GetChackChara2() == 3) m_Player[1] = new Witch;

		return(new SceneMain(m_Player[0], m_Player[1], m_stageNo));// 1ステージ切り替え
	}

	if (Pad::IsTrigger(PAD_INPUT_2, 1) || Pad::IsTrigger(PAD_INPUT_2, 2))
	{
		m_isBackScene = true;
		return (new SceneMapSelect());
	}

	return this;
}

void SceneCharacterSelect::Draw()
{
	m_pUi->Draw();
	m_CharaChoice->Draw();

	//SceneBase::DrawFade();
}
