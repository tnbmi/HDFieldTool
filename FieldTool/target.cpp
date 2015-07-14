//*****************************************************************************
//
// target�N���X [target.cpp]
// Author : KEN MATSUURA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "target.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTarget::CTarget(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_next = NULL;
	m_prev = NULL;
	m_targetFlag = NULL;
}

//=============================================================================
// ����
//=============================================================================
CTarget* CTarget::Create(LPDIRECT3DDEVICE9 device, TARGET_DATA data, POINT_TYPE pointType, int page)
{
	// �����蔻��傫�����X�g
	D3DXVECTOR2 Size_List[] =
	{
		D3DXVECTOR2(32, SCREEN_HEIGHT),		// GOAL_OFF
		D3DXVECTOR2(32, SCREEN_HEIGHT),		// GOAL_ON
		D3DXVECTOR2(32, SCREEN_HEIGHT)		// GOAL_CLEAR
	};

	// �����蔻����W�I�t�Z�b�g�l���X�g
	D3DXVECTOR2 Offset_List[] =
	{
		D3DXVECTOR2(0.0f, -232.0f),			// GOAL_OFF
		D3DXVECTOR2(0.0f, -232.0f),			// GOAL_ON
		D3DXVECTOR2(0.0f, -232.0f)			// GOAL_CLEAR
	};

	CTarget* pointer = new CTarget;
	pointer->Init(device, (CImport::TEXTURES)(CImport::GOAL + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetPos((data.Index.x - (page * 20)) * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// �f�t�H���g�ʒu�Z�b�g����
	pointer->SetPosDef(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// �^�[�Q�b�g�^�C�v�ɂ�铖���蔻��̕ύX
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);
	// ������������̂��ǂ����̃t���O�ݒ�
	if(data.type == TYPE_TARGET_OFF)
		pointer->SetTargetFrag();
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTarget::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
{
	HRESULT hr;

	// �p�����̏������Ăяo��
	hr = CScene2D::Init(device, texture, pointType);
	// �p�����̏������Ɏ��s������
	if(hr == E_FAIL)
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTarget::Uninit(void)
{
	// �p�����̏I�������Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CTarget::Update(void)
{
	// �p�����̍X�V�����Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CTarget::Draw(void)
{
	// �p�����̕`�揈���Ăяo��
	CScene2D::Draw();

	// �����蔻��{�b�N�X�̕`��
	DrawHitBox();
}