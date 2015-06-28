//=============================================================================
//
// Road�N���X [road.cpp]
// Author : Ken Matsuura
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "road.h"

#define ROAD_SIZE	(64.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoad::CRoad(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_next = NULL;
	m_prev = NULL;
}

//=============================================================================
// ����
//=============================================================================
CRoad* CRoad::Create(LPDIRECT3DDEVICE9 device, ROAD_DATA data, POINT_TYPE pointType)
{
	CRoad* pointer = new CRoad;
	pointer->Init(device, (CImport::TEXTURES)(CImport::DIRT + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetSize(ROAD_SIZE, ROAD_SIZE);
	pointer->SetHitSize(D3DXVECTOR2(ROAD_SIZE, ROAD_SIZE));
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 64));
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CRoad::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
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
void CRoad::Uninit(void)
{
	// �p�����̏I�������Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CRoad::Update(void)
{
	// �p�����̍X�V�����Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CRoad::Draw(void)
{
	// �p�����̕`�揈���Ăяo��
	CScene2D::Draw();

	// �����蔻��{�b�N�X�̕`��
	DrawHitBox();
}


// End of File