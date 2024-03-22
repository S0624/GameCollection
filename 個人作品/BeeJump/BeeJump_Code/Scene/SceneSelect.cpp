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
	// BGM ��~
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
	// �t�F�[�h�֌W�̏�����
	m_isFadeOut = IsFadingOut();

	m_selectHandle = LoadGraph("Data/Img/Select1.png");
	m_optionHandle = LoadGraph("Data/Img/Option.png");
	m_guideHandle = LoadGraph("Data/Img/Guide.png");
	m_frameWidth = LoadGraph("Data/Img/SelectFrame1.png");
	m_frameDown = LoadGraph("Data/Img/SelectFrame2.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
}

void SceneSelect::End()
{

}

SceneBase* SceneSelect::Update()
{
	m_pBack->Update(); // �w�i�̍X�V����
	Sound::LoopBGM(Sound::SelectBGM);
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
#ifdef true
			return (new SceneMain(m_cursorNum));
#endif // true
			// �V�[���ڍs
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

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::PushButton);
			// HACK �͋� of �͋ƂȂ̂Ō�Ŏ���
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
		// �͈͊O�̐��l�ɂȂ�Ȃ��悤�ɒ���
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
	m_pBack->Draw();	// �w�i�̕\��

	// select��ʂ̕\�� 
	DrawGraph(0, 0, m_selectHandle, true);

	// HACK �e�X�g�����ł�
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
			GetDrawStringWidthToHandle("�����т��イ����", 24, m_guidefont)) / 2,
			10, "�����т��イ����", 0xff0000, m_guidefont);
	}*/

	//DrawBox(50 + 200 * (1 + m_cursorNum), 200, 50 + 200 * (1 + m_cursorNum) + 300, 200 + 500,0xff0000,false);
	
	//�t���O�ɂ���ăt���[���̉摜��ς���
	// �t���[����ς���
	if (!m_option)
	{
		DrawGraph(116 + (345 * m_cursorNum), 87, m_frameWidth, true);
	}
	else
	{
		DrawGraph(443, 658, m_frameDown, true);
	}
	OptionDraw();
	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}

void SceneSelect::UpdateCursol()
{
	// �J�[�\���̏���
	// ��
	if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		// ���ʉ��𗬂�
		Sound::PlaySE(Sound::Cursor);
		// �J�[�\����ς���
		m_cursorNum--;
	}
	// �E
	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// ���ʉ��𗬂�
		Sound::PlaySE(Sound::Cursor);
		// �J�[�\����ς���
		m_cursorNum++;
	}
	// ��
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		// ���ʉ��𗬂�
		Sound::PlaySE(Sound::Cursor);
		// �J�[�\����ς���
		CursolFlag();
		// �I�v�V�����̃J�[�\���̏���
		CursolOption(1);

	}
	// ��
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		// ���ʉ��𗬂�
		Sound::PlaySE(Sound::Cursor);
		// �J�[�\����ς���
		CursolFlag();
		// �I�v�V�����̃J�[�\���̏���
		CursolOption(-1);
	}
}

void SceneSelect::CursolFlag()
{
	// cursor�̈ʒu��option�ɂ�������t���O��ς���
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
	// �J�[�\����I������Ă�����
	if (m_optinPush)
	{
		// �J�[�\���𓮂���
		m_optionCursorNum += cursol;
	}
	// �͈͊O�ɍs���Ȃ��悤�ɔ͈͂�ݒ�
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

#ifdef  true // �����������������ǂ��������\��
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("Option", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 170, "Option", 0xffffff, m_guidefont);
#endif
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("Title", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 170, "Title", 0xffffff, m_guidefont);
	// option�̕\��
#ifdef  true // �����������������ǂ��������\��
	if (m_optinPush)
	{

		// HACK �Ȃ�������
		m_test += 30;
		if (m_test > 450)
		{
			m_test = 450;
		}

		SetDrawBlendMode(DX_BLENDMODE_MULA, 70);			// ���₷���悤�ɂ�����ƍ��t�B���^�[��������
		DrawBox(0, 0,
			Game::kScreenWidth, Game::kScreenHeight,
			0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�

		DrawRectRotaGraph(Game::kScreenWidth / 2, m_test,
			0, 0,
			838, 486,
			1.0f, 0.0f,
			m_optionHandle, true,
			false, false);
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("������\n����\n(.A.)\n���ǂ�", 24, m_guidefont)) / 2,
			m_test - 150, "������\n����\n(.A.)\n���ǂ�", 0xffffff, m_guidefont);

		SelectOptionDraw();

		DrawFormatString(0, 0, 0xffffff, "%d", m_optionCursorNum);
	}
#endif
}

void SceneSelect::SelectOptionDraw()
{
	//m_optionCursorNum = 0;
	// �ԍ��ɂ���ĕ\����ς���
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
