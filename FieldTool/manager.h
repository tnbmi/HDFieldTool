//*****************************************************************************
//
// CManager�N���X [manager.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_MANAGER_H
#define _MY_MANAGER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CRenderer;
class CDebugproc;
class CImport;
class CPhase;

class CInputKeyboard;

class CManager
{
public:
	CManager();
	~CManager(){};

	static	CManager* Create(HINSTANCE instance, HWND wnd, bool window);
	HRESULT	Init(HINSTANCE instance, HWND wnd, bool window);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void	 CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime);
	CImport* GetImport(void){return m_import;}

	static void SetNextPhase(CPhase* phase){m_phaseNext = phase;}
	static HWND GetWindowHandle(){ return m_window_handle; }

	void CreateBg(int no, int category, int type);
	void DeleteBg(int no);

	void CreateObj(int no, int category, int type, int x, int y);
	void DeleteObj(int no, int category);

	void Scroll(float scroll);

	int GetPage(void);

private:
	static HWND m_window_handle;
	CRenderer*	m_renderer;
	CDebugproc*	m_debugproc;
	CImport*	m_import;

	CPhase*	m_phase;
	static CPhase*	m_phaseNext;

	CInputKeyboard*	m_keyboard;
};

//=============================================================================
#endif