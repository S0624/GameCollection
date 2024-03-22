#include "SceneTitle.h"
#include"SceneSelect.h"
#include"../Object/BackGround.h"

SceneTitle::SceneTitle():
	m_titleHandle(0),
	m_guidefont(0),
	m_cursolNum(0),
	m_guideHandle(0),
	m_frameHandle(0),
	m_pushButton(0),
	m_makeScreen(0),
	m_pshandle(0),
	m_vert()
{
	m_pBack = new BackGround();
	// BGM �Đ�
	Sound::StartBGM(Sound::TitleBGM, 255);
}

SceneTitle::~SceneTitle()
{
	// BGM ��~
	Sound::StopBGM(Sound::TitleBGM);
	delete(m_pBack);
	DeleteGraph(m_titleHandle);
	DeleteFontToHandle(m_guidefont);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_makeScreen);
	DeleteShader(m_pshandle);
}

void SceneTitle::Init()
{
	// �t�F�[�h�֌W�̏�����
	m_isFadeOut = IsFadingOut();
	//SetUseASyncLoadFlag(true);	// �񓯊��ǂݍ��݂��s������

	m_titleHandle = LoadGraph("Data/Img/Title.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
	// �摜�̓ǂݍ���
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");

	ShaderInit();
	//SetUseASyncLoadFlag(false);	// �񓯊��ǂݍ��݂��s������

}

void SceneTitle::End()
{
	
}

SceneBase* SceneTitle::Update()
{
	m_pBack->Update(); // �w�i�̍X�V����
	Sound::LoopBGM(Sound::TitleBGM);
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			if (m_cursolNum != 1)
			{
				return (new SceneSelect);
			}
			else
			{
				DxLib_End();                // �c�w���C�u�����g�p�̏I������
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
			// �{�^���������ꂽ��t���[���̐F�𔽓]����
			m_pushButton = true;
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

void SceneTitle::Draw()
{
	m_pBack->Draw();	// �w�i�̕\��

	// �����̉摜�̕\��
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - 230,
		0, 0,
		760, 425,
		1.0f, 0.0f,
		m_guideHandle, true,
		false, false);


	// �V�F�[�_�̎���
	SetDrawScreen(m_makeScreen);
	// �N���A���Ȃ��ƃf�[�^���c�邽�߃N���A����
	ClearDrawScreen();

	// �I���t���[���̉摜�̕\��
	DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
		0, 0,
		760, 425,
		1.0f, 0.0f,
		m_frameHandle, true,
		false, false);
	
		DrawPrimitive2DToShader(m_vert, 6, DX_PRIMTYPE_TRIANGLELIST);
		SetDrawScreen(DX_SCREEN_BACK);			//�ʏ�`��ɖ߂�
	// �`��
	if (m_pushButton)
	{
		// �V�F�[�_���������摜�̕\��
		DrawGraph(0, 0, m_makeScreen, true);
	}
	// �I���t���[���̉摜�̕\��
	else if (!m_pushButton)
	{
		DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_frameHandle, true,
			false, false);
	}

	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("�X�e�[�W�Z���N�g ", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 370, "�X�e�[�W�Z���N�g ", 0xffffff, m_guidefont);
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("�Q�[��������� ", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 160, "�Q�[��������� ", 0xffffff, m_guidefont);


	// �^�C�g���̕����̕\�� 
	DrawRotaGraph(Game::kScreenWidth / 2, 250,	// �ʒu�̎w��
		1.0f, 0.0f,					// �g�嗦�A��]��
		m_titleHandle, true, false);	// �n���h���A���߁A���]

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}

void SceneTitle::ShaderInit()
{
	// �摜�̓ǂݍ���(�摜�𓧉߂��邽�߂�True�ɂ���)
	m_makeScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// �s�N�Z���V�F�[�_�[�o�C�i���R�[�h�̓ǂݍ���
	m_pshandle = LoadPixelShader("Shader/SamplePS.pso");

	// ���_�f�[�^�̏���
	m_vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	m_vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	m_vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	m_vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	m_vert[0].dif = GetColorU8(255, 255, 255, 255);
	m_vert[0].spc = GetColorU8(0, 0, 0, 0);
	m_vert[0].u = 0.0f; m_vert[0].v = 0.0f;
	m_vert[1].u = 1.0f; m_vert[1].v = 0.0f;
	m_vert[2].u = 0.0f; m_vert[2].v = 1.0f;
	m_vert[3].u = 1.0f; m_vert[3].v = 1.0f;
	m_vert[0].su = 0.0f; m_vert[0].sv = 0.0f;
	m_vert[1].su = 1.0f; m_vert[1].sv = 0.0f;
	m_vert[2].su = 0.0f; m_vert[2].sv = 1.0f;
	m_vert[3].su = 1.0f; m_vert[3].sv = 1.0f;
	m_vert[0].rhw = 1.0f;
	m_vert[1].rhw = 1.0f;
	m_vert[2].rhw = 1.0f;
	m_vert[3].rhw = 1.0f;
	m_vert[4] = m_vert[2];
	m_vert[5] = m_vert[1];

	// �g�p����e�N�X�`�����Z�b�g
	SetUseTextureToShader(0, m_makeScreen);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(m_pshandle);
}
