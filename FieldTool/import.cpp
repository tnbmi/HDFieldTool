//*****************************************************************************
//
// CImport�N���X [import.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "import.h"
#include "mapBg.h"
#include "mapObj.h"
#include "mapData.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FromFileChk(hr)	if(FAILED(hr)){MessageBox(nullptr, "�e�N�X�`������", "D3DXCreateTextureFromFile", MB_OK);}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �e�N�X�`���p�X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �e�N�X�`��
const char* TEX_PATH[] =
{
	nullptr,

	// �O���b�h
	"./data/TEXTURE/grid.png",

	// ��
	"./data/TEXTURE/sky/sky_01.png",

	// �X
	"./data/TEXTURE/forest/forest_01.png",

	// ����
	"./data/TEXTURE/waterside/waterside_01.png",

	// ����
	"./data/TEXTURE/desert/desert_01.png",
	"./data/TEXTURE/desert/desert_02.png",
	"./data/TEXTURE/desert/desert_03.png",

	// �X��
	"./data/TEXTURE/glacier/glacier_01.png",
	"./data/TEXTURE/glacier/glacier_02.png",
	"./data/TEXTURE/glacier/glacier_03.png",
	"./data/TEXTURE/glacier/glacier_04.png",
	"./data/TEXTURE/glacier/glacier_05.png",

	// �T�o���i
	"./data/TEXTURE/savannah/savannah_01.png",
	"./data/TEXTURE/savannah/savannah_02.png",
	"./data/TEXTURE/savannah/savannah_03.png",
	"./data/TEXTURE/savannah/savannah_04.png",
	"./data/TEXTURE/savannah/savannah_05.png",

	// ��
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/desert/sand.png",
	"./data/TEXTURE/glacier/ice.png",
	"./data/TEXTURE/savannah/grassfield.png",
	"./data/TEXTURE/waterside/water.png",

	// ��Q��
	"./data/TEXTURE/stumbler/signboard.png",
	"./data/TEXTURE/stumbler/lion.png",
	"./data/TEXTURE/stumbler/rock.png",
	"./data/TEXTURE/stumbler/log_left.png",
	"./data/TEXTURE/stumbler/log_center.png",
	"./data/TEXTURE/stumbler/log_right.png",
	"./data/TEXTURE/stumbler/bird.png",
	"./data/TEXTURE/stumbler/dustbox.png",
	"./data/TEXTURE/stumbler/barricade.png",
	"./data/TEXTURE/stumbler/cuctus.png",
	"./data/TEXTURE/stumbler/iceberg.png",
	"./data/TEXTURE/stumbler/icicle.png",
	"./data/TEXTURE/stumbler/nuts.png",
	"./data/TEXTURE/stumbler/nuts_reverse.png",
	"./data/TEXTURE/stumbler/sandstone.png",
	"./data/TEXTURE/stumbler/bee.png",
	"./data/TEXTURE/stumbler/huneycomb.png",
	"./data/TEXTURE/stumbler/stump.png",

	// �^�[�Q�b�g
	"./data/TEXTURE/goal/tv_off.png",
};

// �}�b�v
const char* MAP_PATH[] =
{
	"./data/MAP/stage1-1.txt"
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX] = {nullptr};
CMapData*			CImport::m_map[STAGE_MAX] = {nullptr};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CImport::CImport(void)
{

}

//=============================================================================
// ����
//=============================================================================
CImport* CImport::Create(LPDIRECT3DDEVICE9 device)
{
	CImport* pointer = new CImport;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CImport::Init(LPDIRECT3DDEVICE9 device)
{
	HRESULT hr;

	//----------------------------
	// �e�N�X�`���ǂݍ���
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; ++cnt)
	{
		m_tex[cnt] = nullptr;

		hr = D3DXCreateTextureFromFile(device, TEX_PATH[cnt], &m_tex[cnt]);
		FromFileChk(hr)
	}

	////----------------------------
	//// �}�b�v
	////----------------------------
	//for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	//{
	//	m_map[cnt] = CMapData::Create(MAP_PATH[cnt]);
	//}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CImport::Uninit(void)
{
	//----------------------------
	// �e�N�X�`��
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; cnt++)
	{
		SAFE_RELEASE(m_tex[cnt]);
	}

	////----------------------------
	//// �}�b�v
	////----------------------------
	//for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	//{
	//	// �e�N�X�`���̊J��
	//	SAFE_END(m_map[cnt]);
	//}
}

//=============================================================================
// �w�i�^�C�v�R���{�{�b�N�X�̐ݒ�
//=============================================================================
void CImport::SetComboBgType(HWND wnd, int id)
{
	// �R���{�{�b�N�X���N���A
	SendMessage(GetDlgItem(wnd, id), CB_DELETESTRING, 0, 0);

	// �^�C�v���Z�b�g
	for(int cnt = 0; cnt < BG_NUM; ++cnt)
	{
		LPCTSTR strItem = TEXT(TYPE_BG[cnt]);
		SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
	}
}

//=============================================================================
// �I�u�W�F�N�g�J�e�S���R���{�{�b�N�X�̐ݒ�
//=============================================================================
void CImport::SetComboObjCategory(HWND wnd, int id)
{
	// �J�e�S��
	for(int cnt = 0; cnt < CATEGORY_OBJ_NUM; ++cnt)
	{
		LPCTSTR strItem = TEXT(CATEGORY_OBJ[cnt]);
		SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
	}

	m_categoryObj = -1;
}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�R���{�{�b�N�X�̐ݒ�
//=============================================================================
void CImport::SetComboObjType(HWND wnd, int id, int category)
{
	// �J�e�S�����ς���Ă���
	if(m_categoryObj != category)
	{
		// �R���{�{�b�N�X���N���A
		SendMessage(GetDlgItem(wnd, id), CB_RESETCONTENT, 0, 0);

		// �^�C�v���Z�b�g
		switch(category)
		{
		// ��
		case 0:
			for(int cnt = 0; cnt < ROAD_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_ROAD[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		// ��Q��
		case 1:
			for(int cnt = 0; cnt < SRUMBLER_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_SRUMBLER[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		// �^�[�Q�b�g
		case 2:
			for(int cnt = 0; cnt < TARGET_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_TARGET[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		default:
			break;
		}

		// ���݂̃J�e�S�����Z�b�g
		m_categoryObj = category;
	}
}
