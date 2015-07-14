//*****************************************************************************
//
// CImportクラス [import.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "import.h"
#include "mapBg.h"
#include "mapObj.h"
#include "mapData.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FromFileChk(hr)	if(FAILED(hr)){MessageBox(nullptr, "テクスチャ無し", "D3DXCreateTextureFromFile", MB_OK);}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// テクスチャパス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// テクスチャ
const char* TEX_PATH[] =
{
	nullptr,

	// グリッド
	"./data/TEXTURE/grid.png",

	// 空
	"./data/TEXTURE/sky/sky_01.png",

	// 森
	"./data/TEXTURE/forest/forest_01.png",

	// 水辺
	"./data/TEXTURE/waterside/waterside_01.png",

	// 砂漠
	"./data/TEXTURE/desert/desert_01.png",
	"./data/TEXTURE/desert/desert_02.png",
	"./data/TEXTURE/desert/desert_03.png",

	// 氷河
	"./data/TEXTURE/glacier/glacier_01.png",
	"./data/TEXTURE/glacier/glacier_02.png",
	"./data/TEXTURE/glacier/glacier_03.png",
	"./data/TEXTURE/glacier/glacier_04.png",
	"./data/TEXTURE/glacier/glacier_05.png",

	// サバンナ
	"./data/TEXTURE/savannah/savannah_01.png",
	"./data/TEXTURE/savannah/savannah_02.png",
	"./data/TEXTURE/savannah/savannah_03.png",
	"./data/TEXTURE/savannah/savannah_04.png",
	"./data/TEXTURE/savannah/savannah_05.png",

	// 道
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/desert/sand.png",
	"./data/TEXTURE/glacier/ice.png",
	"./data/TEXTURE/savannah/grassfield.png",
	"./data/TEXTURE/waterside/water.png",

	// 障害物
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

	// ターゲット
	"./data/TEXTURE/goal/tv_off.png",
};

#define BG_MAX		((TOWN_01 + 1) - FOREST_01)
#define OBJ_MAX	((GOAL_OFF + 1) - DIRT)

// マップ
const char* MAP_PATH[] =
{
	"./data/MAP/stage1-1.txt"
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX] = {nullptr};
CMapData*			CImport::m_map[STAGE_MAX] = {nullptr};

//=============================================================================
// コンストラクタ
//=============================================================================
CImport::CImport(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CImport* CImport::Create(LPDIRECT3DDEVICE9 device)
{
	CImport* pointer = new CImport;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CImport::Init(LPDIRECT3DDEVICE9 device)
{
	HRESULT hr;

	//----------------------------
	// テクスチャ読み込み
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; ++cnt)
	{
		m_tex[cnt] = nullptr;

		hr = D3DXCreateTextureFromFile(device, TEX_PATH[cnt], &m_tex[cnt]);
		FromFileChk(hr)
	}

	////----------------------------
	//// マップ
	////----------------------------
	//for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	//{
	//	m_map[cnt] = CMapData::Create(MAP_PATH[cnt]);
	//}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CImport::Uninit(void)
{
	//----------------------------
	// テクスチャ
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; cnt++)
	{
		SAFE_RELEASE(m_tex[cnt]);
	}

	////----------------------------
	//// マップ
	////----------------------------
	//for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	//{
	//	// テクスチャの開放
	//	SAFE_END(m_map[cnt]);
	//}
}

//=============================================================================
// 背景タイプコンボボックスの設定
//=============================================================================
void CImport::SetComboBgType(HWND wnd, int id)
{
	// コンボボックスをクリア
	SendMessage(GetDlgItem(wnd, id), CB_DELETESTRING, 0, 0);

	// タイプをセット
	for(int cnt = 0; cnt < BG_NUM; ++cnt)
	{
		LPCTSTR strItem = TEXT(TYPE_BG[cnt]);
		SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
	}
}

//=============================================================================
// オブジェクトカテゴリコンボボックスの設定
//=============================================================================
void CImport::SetComboObjCategory(HWND wnd, int id)
{
	// カテゴリ
	for(int cnt = 0; cnt < CATEGORY_OBJ_NUM; ++cnt)
	{
		LPCTSTR strItem = TEXT(CATEGORY_OBJ[cnt]);
		SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
	}

	m_categoryObj = -1;
}

//=============================================================================
// オブジェクトタイプコンボボックスの設定
//=============================================================================
void CImport::SetComboObjType(HWND wnd, int id, int category)
{
	// カテゴリが変わっている
	if(m_categoryObj != category)
	{
		// コンボボックスをクリア
		SendMessage(GetDlgItem(wnd, id), CB_RESETCONTENT, 0, 0);

		// タイプをセット
		switch(category)
		{
		// 道
		case 0:
			for(int cnt = 0; cnt < ROAD_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_ROAD[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		// 障害物
		case 1:
			for(int cnt = 0; cnt < SRUMBLER_NUM; ++cnt)
			{
				LPCTSTR strItem = TEXT(TYPE_SRUMBLER[cnt]);
				SendMessage(GetDlgItem(wnd, id), CB_ADDSTRING, 0, (LPARAM)strItem);
			}
			break;

		// ターゲット
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

		// 現在のカテゴリをセット
		m_categoryObj = category;
	}
}
