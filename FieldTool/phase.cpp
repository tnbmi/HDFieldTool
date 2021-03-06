//*****************************************************************************
//
// CPhaseクラス [phase.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "phase.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CFade*			CPhase::m_fade		= nullptr;
CInputKeyboard*	CPhase::m_keyboard	= nullptr;
CInputMouse*	CPhase::m_mouse		= nullptr;
