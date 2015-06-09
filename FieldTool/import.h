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
class CImport
{
public:
	typedef enum
	{
		NONE = 0,

		// �V�X�e��
		FADE,
		VERSION,

		// ���S
		TITLELOGO,

		// ��
		TEX_SKY_BG,
		TEX_SKY1,
		TEX_SKY2,
		TEX_SKY3,
		TEX_SKY4,
		TEX_SKY5,

		// �X
		DIRT,
		FOREST_01,

		// ��
		ASPHALT,
		TOWN_01,

		// �S�[��
		GOAL_OFF,
		GOAL_ON,
		GOAL_CLEAR,

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

		// �v���C���[
		PLAYER_WAIT,
		PLAYER_ATTACK,
		PLAYER_LIGHT,
		PLAYER_GOODMOOD,
		PLAYER_BADMOOD,

		// ��蕨
		ASSY_TRAM,

		TEX_MAX
	} TEXTURES;

	CImport();
	~CImport(){};

	static	CImport* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);

	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURES tex){return m_tex[tex];}

private:
	static LPDIRECT3DTEXTURE9 m_tex[TEX_MAX];;
};

//=============================================================================
#endif