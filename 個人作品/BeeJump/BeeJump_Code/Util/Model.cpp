#include "Model.h"
#include<cassert>

namespace
{
	// �����蔻��Ƃ��Ďg�p����t���[���̖��O
	const char* const kCollisionFrameNamu = "BoxCol";
}

Model::Model(const char* fileName) :
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_modelHandle(0)
{
	// ���f���̃��[�h�Ɏ��s����
	assert(m_modelHandle != -1);
	m_modelHandle = MV1LoadModel(fileName);
	// �A�j���[�V�����f�[�^�̃N���A
	ClearAnimeData(m_animPrev);
	ClearAnimeData(m_animNext);
}

Model::Model(int orgModel) :
	m_isUseCollision(false),
	m_isUpdateCollision(false),
	m_colFrameIndex(-1),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0)
{
	// ���[�h�Ɏ��s�������f�����R�s�[���Ƃ��Ďw�肳��Ă���
	assert(m_modelHandle != -1);
	m_modelHandle = MV1DuplicateModel(orgModel);
	// �A�j���[�V�����f�[�^�̃N���A
	ClearAnimeData(m_animPrev);
	ClearAnimeData(m_animNext);
}

Model::~Model()
{
	if (m_isUseCollision)
	{
		// �����蔻������g�p���Ă�����j������
		MV1TerminateCollInfo(m_modelHandle, m_colFrameIndex);
		m_isUseCollision = false;
	}
	MV1DeleteModel(m_modelHandle);
}

void Model::setUseCollision(bool isUse, bool isNeedUpdate)
{
	// �����蔻����g��Ȃ��̂ɓ����蔻��̍X�V�𖈃t���[���s�������A���͂���
	assert(isUse || (!isNeedUpdate));

	// �����蔻��g�p���ɕύX���������ꍇ�̂ݍX�V����
	if (m_isUseCollision != isUse)
	{
		if (isUse)
		{
			// �g��Ȃ����g��
			// �����蔻��p�t���[������������
			m_colFrameIndex = MV1SearchFrame(m_modelHandle, kCollisionFrameNamu);
			if (m_colFrameIndex < 0)// ������Ȃ����� or �G���[
			{
				m_colFrameIndex = -1;
			}
			MV1SetupCollInfo(m_modelHandle, m_colFrameIndex, 8, 8, 8);
		}
		else
		{
			// �g�����g��Ȃ�
			MV1TerminateCollInfo(m_modelHandle, m_colFrameIndex);
		}
	}

	m_isUseCollision = isUse;
	m_isUpdateCollision = isNeedUpdate;
}

void Model::Update()
{
	UpdateAnim(m_animPrev);
	UpdateAnim(m_animNext);

	// �w��t���[�������ăA�j���[�V������ύX����
	m_animChangeFrame++;
	if (m_animChangeFrame > m_animChangeFrameTotal)
	{
		m_animChangeFrame = m_animChangeFrameTotal;
	}
	// �A�j���[�V�����̃u�����h����ݒ肷��
	UpdateAnimeBlendRate();

	// �����蔻��f�[�^�̍X�V
	if (m_isUseCollision && m_isUpdateCollision)
	{
		MV1RefreshCollInfo(m_modelHandle, -1);
	}
}

void Model::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Model::SetPos(VECTOR pos)
{
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, pos);
}

void Model::SetScale(VECTOR scale)
{
	// 3D���f���̃X�P�[������
	MV1SetScale(m_modelHandle, scale);
}

void Model::SetRot(VECTOR rot)
{
	// ��]�i���f�������Ɍ�������j
	MV1SetRotationXYZ(m_modelHandle, rot);
}

void Model::SetAnimation(int animNo, bool isLoop, bool isForceChenge)
{
	if (!isForceChenge)
	{
		// ���łɍĐ�����Ă���A�j���͍Đ����Ȃ�
		if (m_animNext.animNo == animNo)		return;
	}
	// �ȑO�̃A�j���[�V�������c���Ă���ΏI��
	if (m_animPrev.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animPrev.attachNo);
		ClearAnimeData(m_animPrev);
	}
	if (m_animNext.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animNext.attachNo);
		ClearAnimeData(m_animNext);
	}
	// �V�����A�j���[�V������ݒ�
	m_animNext.animNo = animNo;
	m_animNext.attachNo = MV1AttachAnim(m_modelHandle, animNo, -1, false);
	m_animNext.totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_animNext.attachNo);
	m_animNext.isLoop = isLoop;

	m_animChangeFrameTotal = 1;
	m_animChangeFrame = 1;
}

void Model::ChangeAnimation(int animNo, bool isLoop, bool isForceChenge, int changeFrame)
{
	// ���łɍĐ�����Ă���A�j���͍Đ����Ȃ�
	if (m_animNext.animNo == animNo)		return;
	// �ȑO�̃A�j���[�V�������c���Ă���ΏI��
	if (m_animPrev.attachNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_animPrev.attachNo);
		ClearAnimeData(m_animPrev);
	}
	// ���ݍĐ����Ă���A�j���[�V�������Â��A�j���Ƃ���
	m_animPrev = m_animNext;
	// �V�����A�j���[�V������ݒ�
	m_animNext.animNo = animNo;
	m_animNext.attachNo = MV1AttachAnim(m_modelHandle, animNo, -1, false);
	m_animNext.totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_animNext.attachNo);
	m_animNext.isLoop = isLoop;
	// �ύX�ɂ�����t���[�������o���Ă���
	m_animChangeFrameTotal = changeFrame;
	m_animChangeFrame = 0;
	// �u�����h���̐ݒ�
	UpdateAnimeBlendRate();
}

bool Model::IsAnimEnd()
{
	// Loop�A�j���̏ꍇ�͏��false��������
	if (m_animNext.isLoop) return false;

	float time = MV1GetAttachAnimTime(m_modelHandle, m_animNext.attachNo);
	if (time >= m_animNext.totalTime)	return true;

	return false;
}

void Model::ClearAnimeData(AnimData& anim)
{
	anim.animNo = 0;
	anim.attachNo = -1;
	anim.totalTime = 0.0f;
	anim.isLoop = false;
}

void Model::UpdateAnim(AnimData anim, float dt)
{
	// �A�j���[�V�������ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ�
	if (anim.attachNo == -1)		return;

	// �A�j���[�V�����̍X�V
	float time = MV1GetAttachAnimTime(m_modelHandle, anim.attachNo);
	time += dt;
	if (time > anim.totalTime)
	{
		if (anim.isLoop)
		{
			// �A�j���[�V�����̃��[�v
			time -= anim.totalTime;
		}
		else
		{
			// �Ō�̏��
			time = anim.totalTime;
		}
	}
	MV1SetAttachAnimTime(m_modelHandle, anim.attachNo, time);
}

void Model::UpdateAnimeBlendRate()
{
	float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	if (rate > 1.0f) rate = 1.0f;

	MV1SetAttachAnimBlendRate(m_modelHandle, m_animPrev.attachNo, 1.0f - rate);
	MV1SetAttachAnimBlendRate(m_modelHandle, m_animNext.attachNo, rate);
}
