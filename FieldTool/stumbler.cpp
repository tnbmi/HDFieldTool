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
	m_next = NULL;
	m_prev = NULL;
	m_move = -1.0f;
	m_defpos = D3DXVECTOR2(0.0f, 0.0f);
	m_texAnim = 0;
}

//=============================================================================
// ����
//=============================================================================
CStumbler* CStumbler::Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType, int page)
{
	// �����蔻��傫�����X�g
	D3DXVECTOR2 Size_List[] =
	{
		D3DXVECTOR2(112, 128),		// TYPE_SIGNBOARD
		D3DXVECTOR2(112, 112),		// TYPE_LION
		D3DXVECTOR2(128, 96),		// TYPE_ROCK
		D3DXVECTOR2(128, 128),		// TYPE_LOG_LEFT
		D3DXVECTOR2(128, 128),		// TYPE_LOG_CENTER
		D3DXVECTOR2(128, 128),		// TYPE_LOG_RIGHT
		D3DXVECTOR2(96, 96),		// TYPE_BIRD
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

	CStumbler* pointer = new CStumbler;
	pointer->Init(device, (CImport::TEXTURES)(CImport::SIGNBOARD + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetPos((data.Index.x - (page * 20)) * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// �f�t�H���g�ʒu�Z�b�g����
	pointer->SetDefPos(pointer->GetPos());
	pointer->SetPosDef(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 128));
	// �J���X�̎��Ƀe�N�X�`��UV�̕ύX
	if(data.type == TYPE_BIRD)
	{
		pointer->SetCord(0, D3DXVECTOR2(0, 0));
		pointer->SetCord(1, D3DXVECTOR2(0.5, 0));
		pointer->SetCord(2, D3DXVECTOR2(0, 1));
		pointer->SetCord(3, D3DXVECTOR2(0.5, 1));
	}
	// ��Q���^�C�v�ɂ�铖���蔻��̕ύX
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);
	pointer->SetStumType(data.type);
	pointer->SetData(data);

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
	// HP��0�ȉ��Ȃ�폜�t���O���Ă�
	if(m_life <= 0)
	{
		// �O��|�C���^�̌q���ւ�
		if(m_prev != NULL)
		m_prev->m_next = m_next;
		if(m_next != NULL)
			m_next->m_prev = m_prev;
		// �폜�t���O���Ă�
		CScene::Delete();
	}

	// �^�C�v�ɂ���ĐF�X����
	switch(m_type)
	{
	case TYPE_BIRD:			// �J���X�̎�
		// �㉺�ړ�
		CScene2D::SetPosY(m_pos.y + m_move);
		// �f�t�H���g�ʒu�Ƃ̊J�����K��l�𒴂����甽�]
		if(abs(m_defpos.y - m_pos.y) > 45.0f)
			m_move *= -1;
		// 12f���ƂɃe�N�X�`���A�j���[�V����
		if(m_texAnim % 12 == 0)
		{
			if(m_coord[0].x != 0.5f)
			{
				CScene2D::SetCord(0, D3DXVECTOR2(0.5, 0));
				CScene2D::SetCord(1, D3DXVECTOR2(1, 0));
				CScene2D::SetCord(2, D3DXVECTOR2(0.5, 1));
				CScene2D::SetCord(3, D3DXVECTOR2(1, 1));
			}
			else
			{
				CScene2D::SetCord(0, D3DXVECTOR2(0, 0));
				CScene2D::SetCord(1, D3DXVECTOR2(0.5, 0));
				CScene2D::SetCord(2, D3DXVECTOR2(0, 1));
				CScene2D::SetCord(3, D3DXVECTOR2(0.5, 1));
			}
		}
		break;

	default:
		break;
	}

	m_texAnim++;

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
	DrawHitBox();
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