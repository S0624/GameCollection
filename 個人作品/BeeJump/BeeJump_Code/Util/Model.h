#pragma once
#include"../Common.h"

class Model
{
public:
	// �R���X�g���N�^
	// �t�@�C�������w�肵�ă��[�h���s��
	Model(const char* fileName);
	// �w�肳�ꂽ�n���h���̃��f����Duplicate���Đ�������
	Model(int orgModel);
	// �f�X�g���N�^
	virtual ~Model();

	// �����蔻��ݒ�
	void setUseCollision(bool isUse, bool isNeedUpdate);

	void Update();

	void Draw();

	// ���f���̃n���h���擾
	int GetModelHandle() const { return m_modelHandle; }
	// �����蔻��Ɏg�p����t���[���C���f�b�N�X���擾����
	int GetColFrameIndex() const { return m_colFrameIndex; }

	// �\���ʒu�̐ݒ�
	void SetPos(VECTOR pos);
	// �X�P�[���̐ݒ�
	void SetScale(VECTOR scale);
	// ��]��Ԃ̐ݒ�
	void SetRot(VECTOR rot);

	// �A�j���[�V�����̐���

	// �A�j���[�V������ݒ肷��i�ς��Ɛ؂�ւ���j

	/// <summary>
	/// �A�j���[�V������ݒ肷��(�ς��Ɛ؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX��A�j���[�V�����ύX</param>
	/// <param name="isLoop">�A�j���[�V���������[�v�����邩</param>
	/// <param name="isForceChenge">���Ɏw�肳�ꂽ�A�j�����Đ�����Ă���ꍇ���ύX���邩</param>
	void SetAnimation(int animNo, bool isLoop, bool isForceChenge);

	// �A�j���[�V������ω�������ichangeFrame�t���[�������Đ؂�ւ���j
	void ChangeAnimation(int animNo, bool isLoop, bool isForceChenge, int changeFrame);

	// ���݂̃A�j���[�V�������I�����Ă��邩�ǂ������擾����iLoop�A�j���̏ꍇ�͎擾�ł��Ȃ� false���������j
	bool IsAnimEnd();

private:
	// �A�j���[�V�������
	struct AnimData
	{
		int animNo;			// �A�j���[�V�����ԍ�

		int attachNo;		// �A�^�b�`�ԍ�
		float totalTime;	// �A�j���[�V�����̑��Đ�����
		bool isLoop;		//�A�j���[�V���������[�v���邩
	};
private:
	// �A�j���[�V�����f�[�^�̃N���A
	void ClearAnimeData(AnimData& anim);
	// �A�j���[�V�����̍X�V
	void UpdateAnim(AnimData anim, float dt = 0.5f);
	// ���݂̃A�j���[�V�����؂�ւ���񂩂�A�j���[�V�����̃u�����h����ݒ肷��
	void UpdateAnimeBlendRate();

private:
	// ���f���̃n���h��
	int m_modelHandle;
	// �����蔻������g�p����
	bool m_isUseCollision;
	// �����蔻����𖈃t���[���X�V����
	bool m_isUpdateCollision;
	// �����蔻��Ƃ��Ďg�p����t���[���̃C���f�b�N�X
	int m_colFrameIndex;

	// �A�j���[�V�����A�^�b�`�ԍ�
	AnimData m_animPrev;		// �ύX�O�A�j���[�V�������
	AnimData m_animNext;		// �ύX��A�j���[�V�����f�[�^

	// �A�j���[�V�����̐؂�ւ����
	int m_animChangeFrame;			// ���݂̐؂�ւ��t���[��
	int m_animChangeFrameTotal;		// �؂�ւ��ɂ����鑍�t���[����

};

