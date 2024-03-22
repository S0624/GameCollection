#include"../Common.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneSelect.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"
#include "../Util/Effect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneMain::SceneMain(int selectNum) :
	m_teimer(60 * 2),
	m_scoreHandle(0),
	m_guideHandle(0),
	m_frameHandle(0),
	m_selectNum(selectNum),
	m_gamefont(0),
	m_guidefont(0),
	m_seFlag(false),
	m_cursolNum(0),
	m_gameHandle(0),
	m_scoreCount(0),
	m_makeScreen(0),
	m_shadowMap(0)
{
	// �������֌W
	m_pCamera = new Camera();
	m_pPlayer = new Player();
	m_pMap = new Map(m_selectNum);
	m_pBack = new BackGround();

	m_pEffect = new Effect;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneMain::~SceneMain()
{
	// BGM ��~
	Sound::StopBGM(Sound::MainBGM);
	Sound::StopBGM(Sound::GameClear);
	Sound::StopBGM(Sound::GameOver);
	// �폜
	delete(m_pPlayer);
	delete(m_pMap);
	delete(m_pBack);
	delete(m_pCamera);
	//delete(m_pEffect);

	DeleteGraph(m_scoreHandle);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_gameHandle);

	DeleteFontToHandle(m_gamefont);
	DeleteFontToHandle(m_guidefont);

	//// �V���h�E�}�b�v�̍폜
	//DeleteShadowMap(m_shadowMap);
}
/// <summary>
/// ����������
/// </summary>
void SceneMain::Init()
{
	m_isFadeOut = IsFadingOut();//�t�F�[�h�̏�����
	m_pMap->Load();// �}�b�v�̃��[�h

	// �摜�̓ǂݍ���
	m_scoreHandle = LoadGraph("Data/Img/ScorePlate.png");
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");
	m_gameHandle = LoadGraph("Data/Img/GameEndImg.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_gamefont = CreateFontToHandle("yosugara ver12", 100, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��

	m_pEffect->Init();

	//// �V���h�E�}�b�v�̐���
	//m_shadowMap = MakeShadowMap(1024, 1024);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}
/// <summary>
/// �G���h����
/// </summary>
void SceneMain::End()
{
	// ���̂Ƃ��돈���Ȃ�
}
/// <summary>
/// �X�V����
/// </summary>
SceneBase* SceneMain::Update()
{	
	Sound::LoopBGM(Sound::MainBGM);
	m_pCamera->Update(*m_pPlayer);// �J�����̍X�V����
	m_pEffect->Update();
	m_pPlayer->Update(); // �v���C���[�̍X�V����
	// OPTIMIZE �Q�[���̏�Ԃ��󂯎���Ă���
	m_pPlayer->GameClearFlag(m_pMap->GameClearFlag());	// �Q�[���̏�Ԃ��󂯎��
		// �v���C���[������ł��Ȃ��������ɍX�V�������s��
	if (!m_pPlayer->IsExistPlayer())
	{
		m_pBack->Update(); // �w�i�̍X�V����
		// �^�C�}�[�̕\�����I�������
		if (Timer())
		{
			m_scoreCount++;
			m_pMap->Update(); // �}�b�v�̍X�V����
			m_pMap->CollisionDetection(m_pPlayer); // �����蔻��̏���
		}
	}
	else
	{
		// BGM ��~
		Sound::StopBGM(Sound::MainBGM);
		if (!m_seFlag)
		{
			Sound::PlaySE(Sound::GameOver);
			m_seFlag = true;
		}
	}
	if (m_pMap->GameClearFlag() == true)
	{
		// BGM ��~
		Sound::StopBGM(Sound::MainBGM);
		// ���[�v�ʒu�����̐擪����2�b��ɃZ�b�g����
		Sound::SetLoopBGM(2200,Sound::GameClear);
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// resultScene�ɔ��
			if (m_selectNum == Endless)
			{
				// �ڍs����ۂɃX�R�A��n��
				return (new SceneResult(m_scoreCount));
			}
			if (m_cursolNum == 0)
			{
				return (new SceneMain(m_selectNum));
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
		m_teimer--;
		// �t�F�[�h�A�E�g�J�n
		if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
		{
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				Sound::PlaySE(Sound::PushButton);
				// �t�F�[�h���J�n����
				StartFadeOut();
			}
			// �G���h���X�̏ꍇ�͋����I�Ƀ��U���g�Ɉڍs������̂ł��̏��������Ȃ�
			if (m_selectNum != Endless)
			{
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
/// <summary>
/// �`�揈��
/// </summary>
void SceneMain::Draw()
{
	//// �V���h�E�}�b�v�ւ̏�������
	//ShadowMap_DrawSetup(m_shadowMap);
	//// �V���h�E�}�b�v���g�p���ă��f���̕`����s��
	//ShadowMap_DrawEnd();
	//SetUseShadowMap(0, m_shadowMap);

	m_pBack->Draw();	// �w�i�̕\��
	m_pMap->Draw();		// �X�e�[�W�̕\��
	m_pPlayer->Draw();	// �v���C���[�̕\��
	// �G�t�F�N�g�̎���
	//SetDrawScreen(m_makeScreen);
	m_pEffect->Draw();
	//SetDrawScreen(DX_SCREEN_BACK);			//�ʏ�`��ɖ߂�
	//DrawGraph(0, 0, m_makeScreen, true);

	// �G���h���X�̏ꍇ�̂݃X�R�A��\������
	if (m_selectNum == Endless)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);			// �u�����h���[�h���������ăX�R�A�̃p�l���𔼓����ɂ���
		// �X�R�A�ł̕\��
		DrawGraph(25, 25, m_scoreHandle, true);
		// �X�R�A�̕\��
		DrawFormatStringToHandle(100,
			60, 0x000000, m_gamefont, "%d", m_scoreCount);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�
	}

	// �N���A�ƃQ�[���I�[�o�[���o��
	if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
	{
		DrawGuide();
	}
	// �^�C�}�[
	if (!Timer())
	{
		// TODO ���Ƃŉ摜������
		DrawFormatStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("%d", 16, m_gamefont)) / 2,
			Game::kScreenHeight / 2, 0xff0000, m_gamefont, "%d", m_teimer / 60 + 1);
	}

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}

bool SceneMain::Timer()
{
	// �c�莞�Ԃɂ��t���O��Ԃ�
	bool timeFlag = false;
	if (m_teimer <= 0)
	{
		m_teimer = 0;
		timeFlag = true;
	}

	return timeFlag;
}

void SceneMain::DrawGuide()
{
	// �؂���傫��(��Z����p�̕ϐ�)
	int imgY = 0;
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
	
	// �Q�[���N���A�A�Q�[���I�[�o�[��`�悷��
	if (m_pMap->GameClearFlag())
	{
		imgY = 0;
	}
	// TODO ���Ƃŉ摜������
	else
	{
		imgY = 1;		
	}

	// �Q�[���N���A�A�Q�[���I�[�o�[�̉摜���o��
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - (Game::kScreenHeight  - 300),
		0, 144 * imgY,
		897, 144,
		1.0f, 0.0f,
		m_gameHandle, true,
		false, false);
}
