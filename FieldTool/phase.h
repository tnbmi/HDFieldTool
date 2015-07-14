//*****************************************************************************
//
// CPhase�N���X [phase.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_PHAZE_H
#define _MY_PHAZE_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CFade;
class CInputKeyboard;
class CInputMouse;

class CManager;

class CPhase
{
public:
	CPhase(void){};
	virtual ~CPhase(){};

	virtual HRESULT	Init(LPDIRECT3DDEVICE9 device) = 0;
	virtual void	Uninit(void) = 0;
	virtual void	Update(void) = 0;
	virtual void	Draw(void)	 = 0;

	static CFade*	GetFade(void){return m_fade;}

	void SetKeyboard(CInputKeyboard* keyboard){m_keyboard = keyboard;}
	void SetMouse(CInputMouse* mouse){m_mouse = mouse;}

	virtual void CreateBg(int no, int type){}
	virtual void DeleteBg(int no){}

	virtual void CreateObj(int category, int type, int x, int y){}
	virtual void DeleteObj(int x, int y){}

	virtual void Scroll(float scroll){}

	virtual int GetPage(void){return 0;}

	virtual void LoadMap(CManager* manager, const char* filePath, const char* fileName){}
	virtual void SaveMap(const char* filePath, const char* fileName){}

protected:
	LPDIRECT3DDEVICE9 m_device;	// Device�I�u�W�F�N�g(�f�o�C�X�ւ̃|�C���^)

	static CFade* m_fade;

	static CInputKeyboard*	m_keyboard;
	static CInputMouse*		m_mouse;
};

//=============================================================================
#endif
