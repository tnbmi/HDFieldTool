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

	// ��
	"./data/TEXTURE/sky/sky_01.png",
	"./data/TEXTURE/sky/sky_02.png",
	"./data/TEXTURE/sky/sky_03.png",
	"./data/TEXTURE/sky/sky_04.png",
	"./data/TEXTURE/sky/sky_05.png",

	// �X
	"./data/TEXTURE/forest/forest_01.png",

	// ��
	"./data/TEXTURE/town/town_01.png",

	// ��
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/town/asphalt.png",

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
	"./data/TEXTURE/stumbler/needle.png",

	// �^�[�Q�b�g
	"./data/TEXTURE/goal/tv_off.png",

	// �v���C���[
	"./data/TEXTURE/player/player_wait.png",
	"./data/TEXTURE/player/player_attack.png",
	"./data/TEXTURE/player/player_light.png",

	// ��蕨
	"./data/TEXTURE/assy/tram.png",
};

#define BG_MAX		((TOWN_01 + 1) - FOREST_01)
#define OBJ_MAX	((GOAL_OFF + 1) - DIRT)

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
// �w�i�J�e�S���R���{�{�b�N�X�̐ݒ�
//=============================================================================
void CImport::SetComboBgCategory(HWND wnd, int id)
{
	// �J�e�S��
	for(int cnt = 0; cnt < CATEGORY_BG_NUM; ++cnt)
	{
		LPCTSTR strItem = TEXT(CATEGORY_BG[cnt]);
		SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
	}

	m_categoryBg = -1;
}

//=============================================================================
// �w�i�^�C�v�R���{�{�b�N�X�̐ݒ�
//=============================================================================
void CImport::SetComboBgType(HWND wnd, int id, int category)
{
	// �J�e�S�����ς���Ă���
	if(m_categoryBg != category)
	{
		// �R���{�{�b�N�X���N���A
		SendMessage(GetDlgItem(wnd, id), CB_DELETESTRING, 0, 0);

		// �^�C�v���Z�b�g
		switch(category)
		{
		// �X
		case 0:
			for(int cnt = 0; cnt < FOREST_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_FOREST[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		// ��
		case 1:
			for(int cnt = 0; cnt < TOWN_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_TOWN[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		default:
			break;
		}

		// ���݂̃J�e�S�����Z�b�g
		m_categoryBg = category;
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
		SendMessage(GetDlgItem(wnd, id), CB_DELETESTRING, 0, 0);

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
