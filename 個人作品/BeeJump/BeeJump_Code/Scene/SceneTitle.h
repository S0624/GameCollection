#pragma once
#include "SceneBase.h"
#include"../Common.h"

class BackGround;

class SceneTitle :
    public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

	virtual void ShaderInit();
private:
	BackGround* m_pBack;// �w�i�̃|�C���^
	int m_titleHandle;
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g
	int m_cursolNum;	// �I�𒆂̔ԍ�
	int m_guideHandle;	// �����̃n���h��
	int m_frameHandle;	// �����̃t���[��

	bool m_pushButton;	// �ڂ�������������ǂ���

	int m_makeScreen;	// �V�F�[�_�[���������摜��\������ϐ�
	int m_pshandle;		// �V�F�[�_�[����݂��ޕϐ�
	VERTEX2DSHADER m_vert[6];	// �V�F�[�_�[��\������̂Ɏg�p���钸�_
};