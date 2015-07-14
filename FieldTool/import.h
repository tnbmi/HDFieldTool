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
	typedef enum
	{
		NONE = 0,

		// 空
		SKY1,
		SKY2,
		SKY3,
		SKY4,
		SKY5,

		// 森
		FOREST_01,

		// 町
		TOWN_01,

		// 道
		DIRT,
		ASPHALT,

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
		NEEDLE,

		// ターゲット
		GOAL,

		// プレイヤー
		PLAYER_WAIT,
		PLAYER_ATTACK,
		PLAYER_LIGHT,

		// 乗り物
		ASSY_TRAM,

		TEX_MAX,
	} TEXTURES;

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

	void SetComboBgCategory(HWND wnd, int id);
	void SetComboBgType(HWND wnd, int id, int category);
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