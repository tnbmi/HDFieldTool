//*****************************************************************************
//
// CInputKeyboardクラス [inputKeyboard.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "inputKeyboard.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define REPEAT_MIN		(30)	// リピート開始カウント数
#define REPEAT_BETWEEN	(3)		// リピート間隔カウント数

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BYTE CInputKeyboard::m_state[KEYBOARD_MAX];
BYTE CInputKeyboard::m_trigger[KEYBOARD_MAX];
BYTE CInputKeyboard::m_release[KEYBOARD_MAX];
BYTE CInputKeyboard::m_repeat[KEYBOARD_MAX];

//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard(void)
{
	for(int cnt = 0; cnt < KEYBOARD_MAX; ++cnt)
	{
		m_state[cnt]	 = 0x00;
		m_trigger[cnt]	 = 0x00;
		m_release[cnt]	 = 0x00;
		m_repeat[cnt]	 = 0x00;
		m_cntRepeat[cnt] = 0;
	}

}

//=============================================================================
// 生成
//=============================================================================
CInputKeyboard* CInputKeyboard::Create(HINSTANCE instance, HWND wnd)
{
	CInputKeyboard* pointer = new CInputKeyboard;
	pointer->Init(instance, wnd);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE instance, HWND wnd)
{
	//----------------------------
	// 生成
	//----------------------------
	// DirectInputオブジェクト
	HRESULT_FUNC(CInput::Init(instance, wnd))

	// デバイスの生成
	if(FAILED(m_input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, nullptr)))
	{
		MessageBox(nullptr, "デバイスが生成できませんでした", "エラー", (MB_OK | MB_ICONERROR));
		return E_FAIL;
	}

	//----------------------------
	// 設定
	//----------------------------
	// データフォーマット
	if(FAILED(m_inputDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(nullptr, "データフォーマットを設定できませんでした", "エラー", (MB_OK | MB_ICONERROR));
		return E_FAIL;
	}

	// 協調モード
	if(FAILED(m_inputDevice->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(nullptr, "協調モードを設定できませんでした", "エラー", (MB_OK | MB_ICONERROR));
		return E_FAIL;
	}

	//----------------------------
	// アクセス権取得
	//----------------------------
	m_inputDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// オブジェ開放
	CInput::Uninit();

	// アクセス権開放
	if(m_inputDevice != nullptr)
	{
		m_inputDevice->Unacquire();
		m_inputDevice->Release();
		m_inputDevice = nullptr;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[KEYBOARD_MAX];

	if(SUCCEEDED(m_inputDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for(int cnt = 0; cnt < KEYBOARD_MAX; ++cnt)
		{
			// 現状取得
			aKeyState[cnt] &= 0x80;

			//----------------------------
			// 状態情報作成
			//----------------------------
			// トリガー
			m_trigger[cnt] = (aKeyState[cnt] ^ m_state[cnt]) & aKeyState[cnt];

			// リリース
			m_release[cnt] = (aKeyState[cnt] ^ m_state[cnt]) & m_state[cnt];

			// リピート
			if(aKeyState[cnt])
			{
				// カウントアップ・キーリセット
				++m_cntRepeat[cnt];
				m_repeat[cnt] = 0;

				if((m_cntRepeat[cnt] >= REPEAT_MIN && (m_cntRepeat[cnt] % REPEAT_BETWEEN == 0)) || m_trigger[cnt])
				{
					// リピート開始
					m_repeat[cnt] = aKeyState[cnt];
				}
			}
			else
			{
				m_repeat[cnt] = aKeyState[cnt];
				m_cntRepeat[cnt] = 0;
			}

			// プレス
			m_state[cnt] = aKeyState[cnt];
		}
	}
	else
	{
		// アクセス権取り直し
		m_inputDevice->Acquire();
	}
}