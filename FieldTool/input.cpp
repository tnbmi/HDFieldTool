//*****************************************************************************
//
// CInputクラス [input.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "input.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTINPUT8	CInput::m_input		  = nullptr;
bool			CInput::m_padFlg[PAD_NUM] = {false};

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInput::Init(HINSTANCE instance, HWND wnd)
{
	//----------------------------
	// DirectInputオブジェクト生成
	//----------------------------
	if(m_input == nullptr)
	{
		if(FAILED(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, nullptr)))
		{
			MessageBox(nullptr, "オブジェクトが生成できませんでした", "エラー", (MB_OK | MB_ICONERROR));
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInput::Uninit(void)
{
	// オブジェ開放
	SAFE_RELEASE(m_input);
}
