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
#include "debugproc.h"

// �����蔻��傫�����X�g
D3DXVECTOR2 Size_List[] =
{
	D3DXVECTOR2(112, 128),		// TYPE_SIGNBOARD
	D3DXVECTOR2(112, 112),		// TYPE_LION
	D3DXVECTOR2(128, 96),		// TYPE_ROCK
	D3DXVECTOR2(128, 128),		// TYPE_LOG_LEFT
	D3DXVECTOR2(128, 128),		// TYPE_LOG_CENTER
	D3DXVECTOR2(128, 128),		// TYPE_LOG_RIGHT
	D3DXVECTOR2(128, 128),		// TYPE_BIRD
	D3DXVECTOR2(80, 96),		// TYPE_DUSTBOX
	D3DXVECTOR2(128, 128),		// TYPE_BARRICADE
	D3DXVECTOR2(128, 128)		// TYPE_MAX
};

// �����蔻����W�I�t�Z�b�g�l���X�g
D3DXVECTOR2 Offset_List[] =
{
	D3DXVECTOR2(0, 0),			// TYPE_SIGNBOARD
	D3DXVECTOR2(0, 8),			// TYPE_LION
	D3DXVECTOR2(0, 16),			// TYPE_ROCK
	D3DXVECTOR2(0, 0),			// TYPE_LOG_LEFT
	D3DXVECTOR2(0, 0),			// TYPE_LOG_CENTER
	D3DXVECTOR2(0, 0),			// TYPE_LOG_RIGHT
	D3DXVECTOR2(0, 0),			// TYPE_BIRD
	D3DXVECTOR2(0, 16),			// TYPE_DUSTBOX
	D3DXVECTOR2(0, 0),			// TYPE_BARRICADE
	D3DXVECTOR2(0, 0)			// TYPE_MAX
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStumbler::CStumbler(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_life = 1;
	m_next = NULL;
	m_prev = NULL;
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
	pointer->SetPosDef(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// ��Q���^�C�v�ɂ�铖���蔻��̕ύX
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);
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

	// �����蔻��{�b�N�X�̕`��
	if(CDebugproc::GetDrawFlg())
	{
		DrawHitBox();
	}
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