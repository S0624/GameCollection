#pragma once
#include "SceneBase.h"

// �N���X�̐錾
class Player;
class Map;
class BackGround;
class Camera;
class GameObject;
class Effect;

// �V�[���x�[�X�N���X���p�����ăV�[�����쐬����
class SceneMain :
	public SceneBase
{
public:
	// �R���X�g���N�^
	SceneMain(int selectNum);
	// �f�X�g���N�^
	virtual ~SceneMain();

	// ������
	virtual void Init();
	// �G���h����
	virtual void End();
	// �X�V����
	virtual SceneBase* Update() override;
	// �`�揈��
	virtual void Draw();

	// �X�e�[�W���n�܂������̃J�E���g�_�E�������鏈��
	bool Timer();
	// �Q�[���N���A�A�I�[�o�[���ɕ\�����������`�悷�鏈��
	void DrawGuide();

private:
	Player* m_pPlayer;	// �v���C���[�̃|�C���^
	Map* m_pMap;		// �}�b�v�̃|�C���^
	BackGround* m_pBack;// �w�i�̃|�C���^
	Camera* m_pCamera;	// �J�����̃|�C���^
	Effect* m_pEffect;

	int m_scoreHandle;	// �X�R�A��\������p�l��
	int m_guideHandle;	// �N���A�A�Q�[���I�[�o�[���̑I�����
	int m_frameHandle;	// �N���A�A�Q�[���I�[�o�[���̃t���[���摜
	int m_selectNum;	// �N���A�A�Q�[���I�[�o�[���̑I�񂾔ԍ�
	int m_gameHandle;	// �N���A�A�Q�[���I�[�o�[�̉摜

	int m_gamefont;		// �J�E���g�_�E���ȂǂɎg�p����t�H���g
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g

	int m_teimer;		// �^�C�}�[(�n�܂�O�̃J�E���g�_�E���Ɏg�p)

	bool m_seFlag;		// SE���Đ��������ǂ���

	int m_cursolNum;	// �N���A�A�Q�[���I�[�o�[���̑I�񂾔ԍ�

	int m_scoreCount;	// �X�R�A���J�E���g����p�̕ϐ�

	int m_makeScreen;	// ���C�N�X�N���[��������ϐ�

	// TODO �V���h�E�}�b�v��t���悤�Ƃ��Ăł��Ȃ������̂ł��ƂŒǉ�����
	int	m_shadowMap;	// �V���h�E�}�b�v(�e)�̂��߂̕ϐ�
};

