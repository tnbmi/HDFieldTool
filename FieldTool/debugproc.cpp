//*****************************************************************************
//
// CDebugprocクラス [debugproc.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "debugproc.h"

#include "inputKeyboard.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CInputKeyboard* CDebugproc::m_keyboard = nullptr;
char CDebugproc::m_strDebug[STR_MAX];
bool CDebugproc::m_drawFlg;

//=============================================================================
// コンストラクタ
//=============================================================================
CDebugproc::CDebugproc(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CDebugproc* CDebugproc::Create(LPDIRECT3DDEVICE9 device)
{
	CDebugproc* pointer = new CDebugproc;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CDebugproc::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// 情報表示用フォントを設定
	//----------------------------
	D3DXCreateFont(m_device,					// デバイス
					15,							// 文字の高さ
					8,							// 文字幅
					0,							// フォントの太さ
					0,							// MIPMAPのレベル
					FALSE,						// イタリックかどうか
					SHIFTJIS_CHARSET,			// 文字セット
					OUT_DEFAULT_PRECIS,			// 出力精度
					DEFAULT_QUALITY,			// 出力品質
					DEFAULT_PITCH | FF_SWISS,	// フォントピッチとファミリ
					"Terminal",					// フォント名
					&m_font);					// ポインタへのアドレス
	
	// デバッグ情報バッファのクリア
	memset(&m_strDebug, 0, STR_MAX);

	// デバッグフラグ
#ifdef _DEBUG
	m_drawFlg = true;
#else
	m_drawFlg = false;
#endif

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CDebugproc::Uninit(void)
{
	// 情報表示用フォントの開放
	SAFE_RELEASE(m_font)
}

//=============================================================================
// 更新
//=============================================================================
void CDebugproc::Update(void)
{
	// デバッグ情報バッファのクリア
	memset(&m_strDebug, 0, STR_MAX);

	// デバッグ表示切替
	if(m_keyboard->GetTrigger(DIK_F1) == true)
	{
		if(m_drawFlg)
		{
			m_drawFlg = false;
		}
		else
		{
			m_drawFlg = true;
		}
	}

	// 切り替えアナウンス
	if(m_drawFlg)
	{
		CDebugproc::PrintDebugProc("デバッグON/OFF：[F1]\n");
	}
}

//=============================================================================
// 描画
//=============================================================================
void CDebugproc::Draw(void)
{
	if(m_drawFlg)
	{
		RECT rect = { 0, 0, static_cast<LONG>(SCREEN_WIDTH), static_cast<LONG>(SCREEN_HEIGHT) };

		m_font->DrawText(nullptr, m_strDebug, -1, &rect,
						 DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

//=============================================================================
// デバッグ表示の登録
//=============================================================================
void CDebugproc::PrintDebugProc(const char *fmt, ...)
{
	char	str[1024];	// 処理文字列
	va_list	args;		// 可変引数処理用

	// ワーク初期化
	memset(str, 0, sizeof(str));

	//----------------------------
	// 文字列追加
	//----------------------------
	va_start(args, fmt);	// 可変引数へのアクセス開始

	// 文字列変換
	vsnprintf_s(str, _TRUNCATE, fmt, args);

	// 文字列結合
	strcat_s(m_strDebug, sizeof(m_strDebug), str);

	// ワーククリア
	memset(str, 0, sizeof(str));

	va_end(args);	// 可変引数へのアクセス終了
}
