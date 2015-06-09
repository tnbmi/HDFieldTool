//*****************************************************************************
//
// CBackground�N���X [background.h]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "background.h"

#include "scene2D.h"
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BG_LEFT	(-SCREEN_WIDTH)
#define BG_RIGHT	(SCREEN_WIDTH * (BG_MAX - 1))

const CImport::TEXTURES _type_bg[CBackground::TYPE_MAX] =
{
	CImport::FOREST_01,
	CImport::TOWN_01,
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackground::CBackground(void)
{
}

//=============================================================================
// ����
//=============================================================================
CBackground* CBackground::Create(LPDIRECT3DDEVICE9 device, TYPE type)
{
	CBackground* pointer = new CBackground;
	pointer->Init(device, type);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBackground::Init(LPDIRECT3DDEVICE9 device, TYPE type)
{
	for(int cnt = 0; cnt < BG_MAX; ++cnt)
	{
		m_background[cnt] = CScene2D::Create(device, _type_bg[type], CScene2D::POINT_LEFTTOP, 1);
		m_background[cnt]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_background[cnt]->SetPos((float)SCREEN_WIDTH * cnt, 0.0f);
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CBackground::Uninit(void)
{
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CBackground::Scroll(float scroll)
{
	for(int cnt = 0; cnt < BG_MAX; ++cnt)
	{
		float backgroundScroll = m_background[cnt]->GetPos().x - scroll;

		if(backgroundScroll < BG_LEFT)
		{
			backgroundScroll = BG_RIGHT - (BG_LEFT - backgroundScroll);
		}
		else if(backgroundScroll > BG_RIGHT)
		{
			backgroundScroll = BG_LEFT - (backgroundScroll - BG_RIGHT);
		}

		m_background[cnt]->SetPosX(backgroundScroll);
	}
}
