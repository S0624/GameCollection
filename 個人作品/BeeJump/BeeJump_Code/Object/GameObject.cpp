#include "GameObject.h"
#include"../Util/Model.h"
#include <cassert>

namespace
{
	// �X�N���[����
	//constexpr float kMoveScroll = -1.5f;
	constexpr float kMoveScroll = -1.0f;
	//float kAddScroll = 0.0f;
	
	// �����蔻��̑傫��
	constexpr float kColRadius = 6.0f;

	// �v���C���[�̈ʒu���󂯎��
	VECTOR kPlayerPos = {0,0,0};
	// �v���C���[�̓����蔻��̑傫�����󂯎��
	float kPlayerRad = 0;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObject::GameObject(const char* modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),// �Q�[���I�u�W�F�N�g�̃n���h��
	m_objectNum(objNum),// �I�u�W�F�N�g�̔ԍ�
	m_speed(3.0f),// �X�N���[���̃X�s�[�h
	m_scale(0.05f),	// �X�P�[��
	m_blockX(blockX),// �I�u�W�F�N�g�̈ʒu���󂯎��
	m_blockY(blockY),// �I�u�W�F�N�g�̈ʒu���󂯎��
	m_isExist(false),//	�`�悵�Ă����͈͂��ǂ���
	m_drawRange(false)//  �I�u�W�F�N�g�̎g�p���Ă���ԍ�
{
	// �n���h�����󂯎��
	m_modelHandle = MV1LoadModel(modelhnadle);
	// 3D���f���̐���
	m_pModel = std::make_shared<Model>(modelhnadle);
	// �����蔻��̗L����
	m_pModel->setUseCollision(true, true);

	// �ʒu�̏�����
	m_pos = VAdd(VGet(250.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	// ��]�̐ݒ�
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// ��]�i���f�������Ɍ�������j
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

GameObject::GameObject(int modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),// �Q�[���I�u�W�F�N�g�̃n���h��
	m_objectNum(objNum),// �I�u�W�F�N�g�̔ԍ�
	m_speed(3.0f),// �X�N���[���̃X�s�[�h
	m_scale(0.05f),	// �X�P�[��
	m_blockX(blockX),// �I�u�W�F�N�g�̈ʒu���󂯎��
	m_blockY(blockY),// �I�u�W�F�N�g�̈ʒu���󂯎��
	m_isExist(false),//	�`�悵�Ă����͈͂��ǂ���
	m_drawRange(false)//  �I�u�W�F�N�g�̎g�p���Ă���ԍ�
{
	// �n���h�����󂯎��
	//m_modelHandle = MV1LoadModel(modelhnadle);
	// 3D���f���̐���
	m_pModel = std::make_shared<Model>(modelhnadle);
	// �����蔻��̗L����
	m_pModel->setUseCollision(true, true);

	// �ʒu�̏�����
	m_pos = VAdd(VGet(250.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	// ��]�̐ݒ�
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// ��]�i���f�������Ɍ�������j
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// �X�V
/// </summary>
void GameObject::Update()
{
	// �X�N���[������
	m_pos.x += kMoveScroll;

	// ��]�̐ݒ�
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// ��]�i���f�������Ɍ�������j
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
	// �X�V����
	m_pModel->Update();
}

/// <summary>
/// �`��
/// </summary>
void GameObject::Draw()
{

	// ���݂��Ă��Ȃ�������`�悵�Ȃ�
	if (IsDrawFlag())
	{
		// �RD���f���̃|�W�V�����ݒ�
		m_pModel->SetPos(m_pos);
		// �`�揈��
		m_pModel->Draw();
	}

}

/// <summary>
/// �͈͊O�������瑶�݂�����
/// </summary>
/// <returns>m_isExist</returns>
bool GameObject::IsExist()
{
	// �I�u�W�F�N�g�̈ʒu����ʊO�ɍs������
	if (m_pos.x < 0)	{m_isExist = false;}
	else				{ m_isExist = true; }
	// ���݂̑��ݏ���Ԃ�
	return m_isExist;
}

bool GameObject::IsDrawFlag()
{
	if (m_pos.x > 0 && m_pos.x < 250)
	{
		// ����ȊO�͑��݂���
		m_drawRange = true;
	}
	else
	{
		// ���݂�����
		m_drawRange = false;
	}
	return m_drawRange;
}

/// <summary>
/// ���f���n���h���̎擾
/// </summary>
/// <returns>m_pModel->GetModelHandle()</returns>
int GameObject::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}

/// <summary>
/// �����蔻��̎擾
/// </summary>
/// <returns>m_pModel->GetColFrameIndex()</returns>
int GameObject::GetCollisionFrameIndex() const
{
	return m_pModel->GetColFrameIndex();
}