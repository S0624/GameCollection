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
	// BGM �Đ�
	Sound::StartBGM(Sound::TitleBGM, 255);
}

SceneDebug::~SceneDebug()
{
	// BGM ��~
	Sound::StopBGM(Sound::TitleBGM);
}

void SceneDebug::Init()
{
	// �t�F�[�h�֌W�̏�����
	m_isFadeOut = IsFadingOut();

}

void SceneDebug::End()
{

}

SceneBase* SceneDebug::Update()
{
	Sound::LoopBGM(Sound::TitleBGM);
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// �f�o�b�N�p�ɂǂ��̃V�[���ɔ�Ԃ����w�肷��
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
				//DxLib_End();                // �c�w���C�u�����g�p�̏I������
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
			StartFadeOut();
		}

		// cursor����
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
	// �͈͊O�̐����ɍs���Ȃ��悤�ɂ���
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
	DrawString(50,100,"�^�C�g��\n\n�Z���N�g\n\nEasy\n\nNormal\n\nHard\n\nEnd\n\nresult",0xffffff);
	DrawBox(15, 90 + (40 * m_cursolNum), 40, 115 + (40 * m_cursolNum), 0xff0000, true);

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}