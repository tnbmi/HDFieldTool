//*****************************************************************************
//
// CBackgroundManager�N���X [background_manager.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_BACKGROUND_MANAGER_H
#define _MY_BACKGROUND_MANAGER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBackground;

class CBackgroundManager
{
public:
	CBackgroundManager();
	~CBackgroundManager(){};

	static	CBackgroundManager* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	void Scroll(float scroll);

private:
	CBackground* m_top;		// �w�i���X�g�擪
	CBackground* m_cur;		// �w�i���X�g����
};

//=============================================================================
#endif
