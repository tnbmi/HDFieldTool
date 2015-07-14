//*****************************************************************************
//
// CImport�N���X [import.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_IMPORT_H
#define _MY_IMPORT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CMapData;

class CImport
{
public:
	enum TEXTURES
	{
		NONE = 0,

		// �O���b�h
		GRID,

		// ��
		SKY1,

		// �X
		FOREST_01,

		// ����
		WATERSIDE_01,

		// ����
		DESERT_01,
		DESERT_02,
		DESERT_03,

		// �X��
		GLACIER_01,
		GLACIER_02,
		GLACIER_03,
		GLACIER_04,
		GLACIER_05,

		// �T�o���i
		SAVANNAH_01,
		SAVANNAH_02,
		SAVANNAH_03,
		SAVANNAH_04,
		SAVANNAH_05,

		// ��
		DIRT,
		SAND,
		ICE,
		GRASSFIELD,
		WATER,

		// ��Q��
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

		// �^�[�Q�b�g
		GOAL,

		TEX_MAX,
	};

	enum MAPS
	{
		// �X�i���j
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