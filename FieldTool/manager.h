//*****************************************************************************
//
// CManagerクラス [manager.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_MANAGER_H
#define _MY_MANAGER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
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

	void CreateBg(int no, int type);
	void DeleteBg(int no);

	void CreateObj(int category, int type, int x, int y);
	void DeleteObj(int x, int y);

	// スクロール
	void Scroll(float scroll);

	// ページ
	int GetPage(void);

	// ファイル処理
	void LoadMap(CManager* manager, const char* filePath, const char* fileName);
	void SaveMap(const char* filePath, const char* fileName);

	// グリッド
	void SetGrid(int x, int y){m_grid[0] = x; m_grid[1] = y;}

private:
	static HWND m_window_handle;
	CRenderer*	m_renderer;
	CDebugproc*	m_debugproc;
	CImport*	m_import;

	CPhase*	m_phase;
	static CPhase*	m_phaseNext;

	CInputKeyboard*	m_keyboard;

	int m_grid[2];
};

//=============================================================================
#endif