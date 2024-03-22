#pragma once
#include "SceneBase.h"

// �N���X�̐錾
class BackGround;

// �V�[���x�[�X�N���X���p�����ăV�[�����쐬����
class SceneResult :
	public SceneBase
{
public:
	// �R���X�g���N�^
	SceneResult(int score);
	// �f�X�g���N�^
	virtual ~SceneResult();

	// ������
	virtual void Init();
	// �G���h����
	virtual void End();
	// �X�V����
	virtual SceneBase* Update() override;
	// �`�揈��
	virtual void Draw();

	// �Q�[���N���A�A�I�[�o�[���ɕ\�����������`�悷�鏈��
	void DrawGuide();

	// �t�@�C���̐���
	void FileGenerate();
	// �t�@�C���̓ǂݍ���
	void FileRead();
private:
	BackGround* m_pBack;// �w�i�̃|�C���^

	int m_scoreHandle;	// �X�R�A��\������p�l��
	int m_guideHandle;	// �N���A�A�Q�[���I�[�o�[���̑I�����
	int m_frameHandle;	// �N���A�A�Q�[���I�[�o�[���̃t���[���摜
	int m_selectNum;	// �N���A�A�Q�[���I�[�o�[���̑I�񂾔ԍ�

	int m_gamefont;		// �J�E���g�_�E���ȂǂɎg�p����t�H���g
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g

	bool m_seFlag;		// SE���Đ��������ǂ���

	int m_cursolNum;	// �N���A�A�Q�[���I�[�o�[���̑I�񂾔ԍ�

	int	m_nowScore;	// ���l�����X�R�A
	int m_maxScore;	// �X�R�A���J�E���g����p�̕ϐ�
};
