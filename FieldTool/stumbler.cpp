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
	m_move = D3DXVECTOR2(-1.0f, -1.0f);
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
		D3DXVECTOR2(112 * MAG, 128 * MAG),		// TYPE_SIGNBOARD
		D3DXVECTOR2(112 * MAG, 112 * MAG),		// TYPE_LION
		D3DXVECTOR2(128 * MAG, 96  * MAG),		// TYPE_ROCK
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_LOG_LEFT
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_LOG_CENTER
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_LOG_RIGHT
		D3DXVECTOR2(96  * MAG, 96  * MAG),		// TYPE_BIRD
		D3DXVECTOR2(80  * MAG, 96  * MAG),		// TYPE_DUSTBOX
		D3DXVECTOR2(198 * MAG, 112 * MAG),		// TYPE_BARRICADE
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_CUCTUS
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_ICEBERG
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_ICICLE
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_NUTS
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_NUTS_REVERSE
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_SANDSTONE
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_BEE
		D3DXVECTOR2(128 * MAG, 128 * MAG),		// TYPE_HUNEYCOMB
	};

	// �����蔻����W�I�t�Z�b�g�l���X�g
	D3DXVECTOR2 Offset_List[] =
	{
		D3DXVECTOR2(0, 0),			// TYPE_SIGNBOARD
		D3DXVECTOR2(0, 8 * MAG),	// TYPE_LION
		D3DXVECTOR2(0, 16 * MAG),	// TYPE_ROCK
		D3DXVECTOR2(0, 0),			// TYPE_LOG_LEFT
		D3DXVECTOR2(0, 0),			// TYPE_LOG_CENTER
		D3DXVECTOR2(0, 0),			// TYPE_LOG_RIGHT
		D3DXVECTOR2(0, 0),			// TYPE_BIRD
		D3DXVECTOR2(0, 16 * MAG),	// TYPE_DUSTBOX
		D3DXVECTOR2(0, 8 * MAG),	// TYPE_BARRICADE
		D3DXVECTOR2(0, 0),			// TYPE_CUCTUS
		D3DXVECTOR2(0, 0),			// TYPE_ICEBERG
		D3DXVECTOR2(0, 0),			// TYPE_ICICLE
		D3DXVECTOR2(0, 0),			// TYPE_NUTS
		D3DXVECTOR2(0, 0),			// TYPE_NUTS_REVERSE
		D3DXVECTOR2(0, 0),			// TYPE_SANDSTONE
		D3DXVECTOR2(0, 0),			// TYPE_BEE
		D3DXVECTOR2(0, 0),			// TYPE_HUNEYCOMB
	};

	CStumbler* pointer = new CStumbler;
	pointer->Init(device, (CImport::TEXTURES)(CImport::SIGNBOARD + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetPos((data.Index.x -(page * 20)) * GRID_SIZE, SCREEN_HEIGHT - ((data.Index.y * GRID_SIZE) + (GRID_SIZE * 2)));
	// �f�t�H���g�ʒu�Z�b�g����
	pointer->SetDefPos(pointer->GetPos());

	// ��Q���^�C�v�ɂ�铖���蔻��̕ύX
	pointer->SetHitSize(Size_List[data.type]);
	pointer->SetHitOffset(Offset_List[data.type]);

	// ��Q���^�C�v�̕ۑ�
	pointer->SetStumType(data.type);

	// ��Q���^�C�v�ɂ���Ă̓f�[�^�̕ύX
	switch(data.type)
	{
	case TYPE_BIRD:
		pointer->SetCord(0, D3DXVECTOR2(0, 0));
		pointer->SetCord(1, D3DXVECTOR2(0.5, 0));
		pointer->SetCord(2, D3DXVECTOR2(0, 1));
		pointer->SetCord(3, D3DXVECTOR2(0.5, 1));
		break;

	case TYPE_BARRICADE:
		pointer->SetSize(256.0f, 128.0f);
		break;

	case TYPE_BEE:
		pointer->SetCord(0, D3DXVECTOR2(0, 0));
		pointer->SetCord(1, D3DXVECTOR2(0.25, 0));
		pointer->SetCord(2, D3DXVECTOR2(0, 1));
		pointer->SetCord(3, D3DXVECTOR2(0.25, 1));
		pointer->SetStumMove(D3DXVECTOR2(-4.0f, -4.0f));
		break;

	default:
		break;
	}

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
		// �폜�t���O���Ă�
		SetStumDelete();
	}
/*	else
	{
		// �^�C�v�ɂ���ĐF�X����
		switch(m_type)
		{
		case TYPE_BIRD:			// �J���X�̎�
			// �㉺�ړ�
			CScene2D::SetPosY(m_pos.y + m_move.y);
			// �f�t�H���g�ʒu�Ƃ̊J�����K��l�𒴂����甽�]
			if(abs(m_defpos.y - m_pos.y) > 45.0f)
				m_move.y *= -1;
			// 12f���ƂɃe�N�X�`���A�j���[�V����
			m_texAnim++;
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

		case TYPE_BEE:		// �I�̎�
			// ���E�ړ�
			CScene2D::SetPosX(m_pos.x + m_move.x);
			// �f�t�H���g�ʒu�Ƃ̊J�����K��l�𒴂����甽�]
			if(abs(m_defpos.x - m_pos.x) > 96.0f)
			{
				m_move.x *= -1;
			}

			// �㉺�ړ�
			CScene2D::SetPosY(m_pos.y + m_move.y);
			// �f�t�H���g�ʒu�Ƃ̊J�����K��l�𒴂����甽�]
			if(abs(m_defpos.y - m_pos.y) > 48.0f)
			{
				m_move.y *= -1;
			}

			// 8f���ƂɃe�N�X�`���A�j���[�V����
			m_texAnim++;
			if(m_texAnim % 8 == 0)
			{
				if(m_coord[0].x != 0.75f)
				{
					D3DXVECTOR2 tmp;
					for(int i = 0; i < 4;  i++)
					{
						tmp = CScene2D::GetCord(i);
						tmp.x += 0.25;
						CScene2D::SetCord(i, tmp);
					}
				}
				else
				{
					CScene2D::SetCord(0, D3DXVECTOR2(0, 0));
					CScene2D::SetCord(1, D3DXVECTOR2(0.25, 0));
					CScene2D::SetCord(2, D3DXVECTOR2(0, 1));
					CScene2D::SetCord(3, D3DXVECTOR2(0.25, 1));
				}
			}
			break;

		case TYPE_NUTS:
		case TYPE_NUTS_REVERSE:
		case TYPE_ICICLE:			// �������g���b�v��
			if(m_fallFrag)
			{
				m_texAnim++;
				// 30f���h�ꂷ��
				if(m_texAnim < 30)
					if(m_texAnim % 4 == 0 || m_texAnim % 4 == 1)
					{
						CScene2D::SetPosX(m_pos.x += 16.0f);
					}
					else
					{
						CScene2D::SetPosX(m_pos.x -= 16.0f);
					}
				// �ҋ@�t���[���o�ߌ㗎��
				else
					CScene2D::SetPosY(m_pos.y += 16.0f);
				// ��ʉ��ɏo���玀��
				if(m_pos.y >= 760.0f)
				{
					SetStumDelete();
				}
			}
			break;

		default:
			break;
		
		// �p�����̍X�V�����Ăяo��
		CScene2D::Update();
		}
	}*/
}

//=============================================================================
// �`��
//=============================================================================
void CStumbler::Draw(void)
{
	// �p�����̕`�揈���Ăяo��
	CScene2D::Draw();

	// �����蔻��{�b�N�X�̕`��
	//DrawHitBox();
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