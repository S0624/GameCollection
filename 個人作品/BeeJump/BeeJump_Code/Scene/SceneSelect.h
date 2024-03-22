#pragma once
#include "SceneBase.h"

class BackGround;
class SceneSelect :
	public SceneBase
{
public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

	// �J�[�\����Update����
	void UpdateCursol();
	// cursor�̃t���O����
	void CursolFlag();
	// �I�v�V������cursor����
	void CursolOption(int cursol);
	// �I�v�V�����̕`�揈��
	void OptionDraw();
	// �I�΂ꂽ�I�v�V�����̕`�揈��
	void SelectOptionDraw();

private:
	BackGround* m_pBack;// �w�i�̃|�C���^
	int m_selectHandle; // select��ʂ̉摜�̓ǂݍ���
	int m_optionHandle; // option��ʂ̉摜�̓ǂݍ���
	int m_guideHandle;  // ��������摜�̓ǂݍ���
	int m_frameDown;	// �����̃t���[��
	int m_frameWidth;	// �����̃t���[��
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g

	// TODO �e�X�g����
	int m_test;			// �e�X�g�A�ݒ��ʂ��J�����Ƃ��ɃX���C�h������
	bool m_option;		// option��I�����Ă��邩�ǂ���
	bool m_optinPush;	// option�����������ǂ���
	int m_optionCursorNum; // option�̑I��ł���ԍ�
	int m_cursorNum;	// �J�[�\���̂����Ă���ԍ�
	int m_max;			// �}�b�N�X�l�̐ݒ�
};