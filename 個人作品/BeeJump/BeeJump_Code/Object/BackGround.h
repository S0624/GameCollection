#pragma once
class BackGround
{
public:
	BackGround(); // �R���X�g���N�^
	~BackGround();// �f�X�g���N�^

	void Update();// �X�V����
	void Draw();  // �`�揈��
private:
	int m_handle;
	int m_scroll;
	float m_imgIndexWidth;
	float m_imgIndexHight;
};

