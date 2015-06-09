//*****************************************************************************
//
// stumbler�N���X [stumbler.cpp]
// Author : KEN MATSUURA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stumbler.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStumbler::CStumbler(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_life = 1;
}

//=============================================================================
// ����
//=============================================================================
CStumbler* CStumbler::Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType)
{
	CStumbler* pointer = new CStumbler;
	pointer->Init(device, (CImport::TEXTURES)(CImport::SIGNBOARD + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CStumbler::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
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
void CStumbler::Uninit(void)
{
	// �p�����̏I�������Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CStumbler::Update(void)
{
	// �p�����̍X�V�����Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CStumbler::Draw(void)
{
	// �p�����̕`�揈���Ăяo��
	CScene2D::Draw();
}

//=============================================================================
// ��Q���̐����`�F�b�N
//=============================================================================
bool CStumbler::LivingCheck(void)
{
	if(m_life <= 0)
	{
		return true;
	}
	return false;
}

//=============================================================================
// �Փ˔��� (�n���ꂽ���Ǝ����̏����r����
//=============================================================================
bool CStumbler::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// ������4���_�Ƒ����4���_���v�Z
	D3DXVECTOR2 self[4], target[4];

	// �����̒��_�����v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		self[0].x = m_pos.x;				self[0].y = m_pos.y;
		self[1].x = m_pos.x + m_size.x;		self[1].y = m_pos.y;
		self[2].x = m_pos.x + m_size.x;		self[2].y = m_pos.y + m_size.y;
		self[3].x = m_pos.x;				self[3].y = m_pos.y + m_size.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		self[0].x = m_pos.x - m_size.x/2;	self[0].y = m_pos.y - m_size.y/2;
		self[1].x = m_pos.x + m_size.x/2;	self[1].y = m_pos.y - m_size.y/2;
		self[2].x = m_pos.x + m_size.x/2;	self[2].y = m_pos.y + m_size.y/2;
		self[3].x = m_pos.x - m_size.x/2;	self[3].y = m_pos.y + m_size.y/2;
	}

	// �n���ꂽ��񂩂璸�_���v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		target[0].x = pos.x - size.x/2;		target[0].y = pos.y - size.y/2;
		target[1].x = pos.x + size.x/2;		target[1].y = pos.y - size.y/2;
		target[2].x = pos.x + size.x/2;		target[2].y = pos.y + size.y/2;
		target[3].x = pos.x - size.x/2;		target[3].y = pos.y + size.y/2;
	}

	// AABB�Փ˔���
	if( (self[0].x < target[1].x) &&
		(target[0].x < self[1].x) &&
		(self[0].y < target[3].y) &&
		(target[0].y < self[3].y) )
	{
		return true;
	}
	else
	{
		return false;
	}
}