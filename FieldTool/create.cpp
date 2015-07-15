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

#include "manager.h"

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
	m_page = 0;

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
	// ��
	CSky* sky = CSky::Create(device);

	// �O���b�h
	CScene2D* grid = CScene2D::Create(device, CImport::GRID, CScene2D::POINT_LEFTTOP, PRIORITY_MAX-1);
	grid->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//=============================================================================
// �w�i����
//=============================================================================
void CCreate::CreateBg(int no, int type)
{
	// �w�i����
	BG_DATA data = {(BG_TYPE)(TYPE_FOREST_01 + type), no};
	CBackground* bg = CBackground::Create(m_device, data, m_page);

	// �}�b�v�f�[�^�ɒǉ�
	CListMapData::LinkBg(no, bg);
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
void CCreate::CreateObj(int category, int type, int x, int y)
{
	switch(category)
	{
		// ��
		case 0:
		{
			// ������
			ROAD_DATA data = {(ROAD_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CRoad* road = CRoad::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// �d�Ȃ��������폜
			CRoad** roadChk = new CRoad*;
			if(CListMapData::GridChkRoad(data.Index.x, data.Index.y, roadChk))
			{
				CListMapData::DelRoad(*roadChk);
			}

			// �d�Ȃ����^�[�Q�b�g���폜
			CTarget** targetChk = new CTarget*;
			if(CListMapData::GridChkTarget(data.Index.x, data.Index.y, targetChk))
			{
				CListMapData::DelTarget(*targetChk);
			}

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkRoad(road);
			break;
		}

		// ��Q��
		case 1:
		{
			// ��Q������
			STUM_DATA data = {(STUM_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CStumbler* stum = CStumbler::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// �d�Ȃ�����Q�����폜
			CStumbler** stumChk = new CStumbler*;
			if(CListMapData::GridChkStum(data.Index.x, data.Index.y, stumChk))
			{
				CListMapData::DelStum(*stumChk);
			}

			// �d�Ȃ����^�[�Q�b�g���폜
			CTarget** targetChk = new CTarget*;
			if(CListMapData::GridChkTarget(data.Index.x, data.Index.y, targetChk))
			{
				CListMapData::DelTarget(*targetChk);
			}

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkStum(stum);
			break;
		}

		// �^�[�Q�b�g
		case 2:
		{
			// �^�[�Q�b�g����
			TARGET_DATA data = {(TARGET_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CTarget* target = CTarget::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// �d�Ȃ����I�u�W�F�N�g���폜
			DeleteObj(data.Index.x, data.Index.y);

			// �}�b�v�f�[�^�ɒǉ�
			CListMapData::LinkTarget(target);
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
void CCreate::DeleteObj(int x, int y)
{
	CScene2D** obj = new CScene2D*;
	int category = CListMapData::GridChk(x + (m_page * 20), y, obj);

	switch(category)
	{
		// ��
		case 0:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelRoad((CRoad*)*obj);
			break;
		}

		// ��Q��
		case 1:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelStum((CStumbler*)*obj);
			break;
		}

		// �^�[�Q�b�g
		case 2:
		{
			// �}�b�v�f�[�^���폜
			CListMapData::DelTarget((CTarget*)*obj);
			break;
		}

		default:
		{
			break;
		}
	}
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CCreate::Scroll(float scroll)
{
	// �y�[�W�X�V
	if(scroll < 0)
	{
		// �߂�
		m_page--;

		// �߂�Ȃ���
		if(m_page < 0)
		{
			m_page = 0;
			return;
		}
	}
	else
	{
		// �i��
		m_page++;
	}

	// �X�N���[���X�V
	CListMapData::Scroll(scroll);
}

//=============================================================================
// �}�b�v�ǂݍ���
//=============================================================================
void CCreate::LoadMap(CManager* manager, const char* filePath, const char* fileName)
{
	CListMapData::LoadMap(manager, filePath, fileName);
}

//=============================================================================
// �}�b�v�Z�[�u
//=============================================================================
void CCreate::SaveMap(const char* filePath, const char* fileName)
{
	CListMapData::SaveMap(filePath, fileName);
}
