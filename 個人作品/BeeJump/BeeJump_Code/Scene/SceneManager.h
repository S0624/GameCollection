#pragma once
#include "SceneBase.h"
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}
	// ������
	bool Init();
	// �I��
	void End();
	// ���t���[���̏���
	void Update();
	// �`��
	void Draw();

private:
	// �V�[���x�[�X�|�C���^
	SceneBase* m_pScene;
};

