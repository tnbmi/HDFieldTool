//*****************************************************************************
//
// CImportクラス [import.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_IMPORT_H
#define _MY_IMPORT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CMapData;

class CImport
{
public:
	enum TEXTURES
	{
		NONE = 0,

		// グリッド
		GRID,

		// 空
		SKY1,

		// 森
		FOREST_01,

		// 水辺
		WATERSIDE_01,

		// 砂漠
		DESERT_01,
		DESERT_02,
		DESERT_03,

		// 氷河
		GLACIER_01,
		GLACIER_02,
		GLACIER_03,
		GLACIER_04,
		GLACIER_05,

		// サバンナ
		SAVANNAH_01,
		SAVANNAH_02,
		SAVANNAH_03,
		SAVANNAH_04,
		SAVANNAH_05,

		// 道
		DIRT,
		SAND,
		ICE,
		GRASSFIELD,
		WATER,

		// 障害物
		SIGNBOARD,
		LION,
		ROCK,
		LOG_LEFT,
		LOG_CENTER,
		LOG_RIGHT,
		BIRD,
		DUSTBOX,
		BARRICADE,
		CUCTUS,
		ICEBERG,
		ICICLE,
		NUTS,
		NUTS_REVERSE,
		SANDSTONE,
		BEE,
		HUNEYCOMB,
		STUMP,

		// ターゲット
		GOAL,

		TEX_MAX,
	};

	enum MAPS
	{
		// 森（仮）
		STAGE_1_1 = 0,
		STAGE_MAX
	};

	CImport();
	~CImport(){};

	static	CImport* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);

	static LPDIRECT3DTEXTURE9	GetTexture(TEXTURES tex){return m_tex[tex];}
	static CMapData*			GetMap(MAPS map){return m_map[map];}

	void SetComboBgType(HWND wnd, int id);
	void SetComboObjCategory(HWND wnd, int id);
	void SetComboObjType(HWND wnd, int id, int category);

private:
	static LPDIRECT3DTEXTURE9	m_tex[TEX_MAX];
	static CMapData*			m_map[STAGE_MAX];

	int m_categoryBg;
	int m_categoryObj;
};

//=============================================================================
#endif