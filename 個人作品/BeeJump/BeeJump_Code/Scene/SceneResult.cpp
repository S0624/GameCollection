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
/// �R���X�g���N�^
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
	// �������֌W
	m_pBack = new BackGround();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneResult::~SceneResult()
{
	// BGM ��~
	Sound::StopBGM(Sound::ResultBGM);
	// �폜
	delete(m_pBack);

	DeleteGraph(m_scoreHandle);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);

	DeleteFontToHandle(m_gamefont);
	DeleteFontToHandle(m_guidefont);
}
/// <summary>
/// ����������
/// </summary>
void SceneResult::Init()
{
	m_isFadeOut = IsFadingOut();//�t�F�[�h�̏�����

	// �摜�̓ǂݍ���
	m_scoreHandle = LoadGraph("Data/Img/ResultPlate.png");
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_gamefont = CreateFontToHandle("yosugara ver12", 100, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
}
/// <summary>
/// �G���h����
/// </summary>
void SceneResult::End()
{

}

SceneBase* SceneResult::Update()
{
	Sound::LoopBGM(Sound::ResultBGM);
	m_pBack->Update(); // �w�i�̍X�V����
	// �t�@�C���̓ǂݍ��݂�����
	FileRead();

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// ���l�����X�R�A���ۑ�����Ă���X�R�A���傫��������ύX����
			if (m_nowScore > m_maxScore)
			{
				FileGenerate();
			}
			// resultScene�ɔ��
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

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�
	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::PushButton);
			// �t�F�[�h���J�n����
			StartFadeOut();
		}
		// cursor����
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
	// �͈͊O�̐����ɍs���Ȃ��悤�ɂ���
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
	m_pBack->Draw();	// �w�i�̕\��

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);			// �u�����h���[�h���������ăX�R�A�̃p�l���𔼓����ɂ���
	// �X�R�A�ł̕\��
	DrawRectRotaGraph(Game::kScreenWidth / 2, 230, 
		0,0,
		1000,1000,
		1.0f,0.0f,
		m_scoreHandle, true);
	// �X�R�A�̕\��
	DrawStringToHandle(450,100, "Score", 0x000000,m_guidefont);
	DrawStringToHandle(450, 250, "HightScore", 0x000000,m_guidefont);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 100,
		100, 0x000000, m_gamefont, "%d", m_nowScore);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 100,
		250, 0x000000, m_gamefont, "%d", m_maxScore);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�

	// �����̃{�^���̕\��
	DrawGuide();

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}

void SceneResult::DrawGuide()
{
	// �����̉摜�̕\��
	if (m_selectNum != 3)
	{
		DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - 230,
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_guideHandle, true,
			false, false);
		// �I���t���[���̉摜�̕\��
		DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_frameHandle, true,
			false, false);

		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("���g���C ", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 370, "���g���C ", 0xffffff, m_guidefont);
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("�X�e�[�W�Z���N�g ", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 160, "�X�e�[�W�Z���N�g ", 0xffffff, m_guidefont);
	}
}
// �t�@�C���̐���
void SceneResult::FileGenerate()
{
	std::ofstream writingFile;
	// ��������t�@�C����
	std::string filename = "Data/ScoreData.txt";
	writingFile.open(filename, std::ios::out);
	// ���l�����X�R�A����������
	writingFile << m_nowScore << std::endl;
	// �t�@�C�������
	writingFile.close();
}
// �t�@�C���̓ǂݍ���
void SceneResult::FileRead()
{
	std::ifstream readingFile;
	// �t�@�C����
	std::string filename = "Data/ScoreData.txt";
	readingFile.open(filename, std::ios::in);
	std::string readingLineBuffer;
	while (std::getline(readingFile, readingLineBuffer)) {
		// string�^��int�^��
		m_maxScore = atoi(readingLineBuffer.c_str());
	}
}
