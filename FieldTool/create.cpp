//*****************************************************************************
//
// CCreate�N���X [game.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "create.h"
#include "manager.h"

#include "inputKeyboard.h"

#include "scene2D.h"

// �}�b�v�f�[�^
#include "listMapData.h"

// �w�i
#include "sky.h"
#include "background.h"

// �I�u�W�F�N�g
#include "road.h"
#include "stumbler.h"
#include "target.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// ������
//=============================================================================
HRESULT CCreate::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// �f�o�C�X�擾
	//----------------------------
	m_device = device;

	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	InitObject(device);

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CCreate::Uninit(void)
{
	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------

	// �V�[��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V
//=============================================================================
void CCreate::Update(void)
{
	//----------------------------
	// �f�o�b�O�R�}���h
	//----------------------------
	Debug();

	//----------------------------
	// �X�V���e
	//----------------------------
}

//=============================================================================
// �`��
//=============================================================================
void CCreate::Draw(void)
{
}

//=============================================================================
// �f�o�b�N���e
//=============================================================================
void CCreate::Debug(void)
{
}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CCreate::InitObject(LPDIRECT3DDEVICE9 device)
{

}

//=============================================================================
// �w�i����
//=============================================================================
void CCreate::CreateBg(int no, int category, int type)
{
	switch(category)
	{
		// �X
		case 0:
		{
			// �w�i����
			BG_DATA data = {(BG_TYPE)(TYPE_FOREST_01 + type), no};
			CBackground* bg = CBackground::Create(m_device, data);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkBg(no, bg);
			break;
		}

		// ��
		case 1:
		{
			// �w�i����
			BG_DATA data = {(BG_TYPE)(TYPE_TWON_01 + type), no};
			CBackground* bg = CBackground::Create(m_device, data);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkBg(no, bg);
			break;
		}

		default:
		{
			break;
		}
	}
}

//=============================================================================
// �w�i�폜
//=============================================================================
void CCreate::DeleteBg(int no)
{
	// �}�b�v�f�[�^���폜
	CListMapData::DelBg(no);
}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
void CCreate::CreateObj(int no, int category, int type, int x, int y)
{
	switch(category)
	{
		// ��
		case 0:
		{
			// �I�u�W�F�N�g����
			ROAD_DATA data = {(ROAD_TYPE)type, D3DXVECTOR2((float)x, (float)y)};
			CRoad* road = CRoad::Create(m_device, data, CScene2D::POINT_LEFTTOP);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkRoad(no, road);
			break;
		}

		// ��Q��
		case 1:
		{
			// �I�u�W�F�N�g����
			STUM_DATA data = {(STUM_TYPE)type, D3DXVECTOR2((float)x, (float)y)};
			CStumbler* stum = CStumbler::Create(m_device, data, CScene2D::POINT_LEFTTOP);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkStum(no, stum);
			break;
		}

		// �^�[�Q�b�g
		case 2:
		{
			// �I�u�W�F�N�g����
			TARGET_DATA data = {(TARGET_TYPE)type, D3DXVECTOR2((float)x, (float)y)};
			CTarget* target = CTarget::Create(m_device, data, CScene2D::POINT_LEFTTOP);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkTarget(no, target);
			break;
		}

		default:
		{
			break;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�폜
//=============================================================================
void CCreate::DeleteObj(int no, int category)
{
	switch(category)
	{
		// ��
		case 0:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelRoad(no);
			break;
		}

		// ��Q��
		case 1:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelStum(no);
			break;
		}

		// �^�[�Q�b�g
		case 2:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelTarget(no);
			break;
		}

		default:
		{
			break;
		}
	}
}