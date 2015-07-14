//*****************************************************************************
//
// CManegerクラス [manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "manager.h"

#include "renderer.h"
#include "debugproc.h"
#include "import.h"

#include "phase.h"
#include "create.h"

#include "inputKeyboard.h"

#include "listObject.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CPhase* CManager::m_phaseNext = nullptr;
HWND	CManager::m_window_handle = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CManager* CManager::Create(HINSTANCE instance, HWND wnd, bool window)
{
	CManager* pointer = new CManager;
	pointer->Init(instance, wnd, window);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager::Init(HINSTANCE instance, HWND wnd, bool window)
{
	LPDIRECT3DDEVICE9 device;

	//----------------------------
	// 共通部
	//----------------------------
	// ウィンドウハンドル
	m_window_handle = wnd;
	// レンダラー
	m_renderer	= CRenderer::Create(wnd, window);
	device		= m_renderer->GetDevice();

	// 入力
	m_keyboard = CInputKeyboard::Create(instance, wnd);

	// デバッグ表示
	m_debugproc = CDebugproc::Create(device);
	m_renderer->SetDebugproc(m_debugproc);

	//----------------------------
	// 初期起動表示
	//----------------------------
	CScene2D* setup = CScene2D::Create(device, "./data/TEXTURE/fade.jpg", CScene2D::POINT_CENTER);
	setup->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	setup->SetPos(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

	m_renderer->Draw();

	//----------------------------
	// ファイル読み込み
	//----------------------------
	m_import = CImport::Create(device);

	//----------------------------
	// フェーズ
	//----------------------------
	m_phase = (CPhase*)new CCreate;
	m_phase->Init(device);
	m_phase->SetKeyboard(m_keyboard);

	m_phaseNext = m_phase;

	//----------------------------
	// 入力設定
	//----------------------------
	m_debugproc->SetKeyboard(m_keyboard);

	//----------------------------
	// 初期化成功
	//----------------------------
	// 起動画面破棄
	setup->UnLinkScene();
	SAFE_END(setup);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManager::Uninit(void)
{
	//----------------------------
	// フェーズ
	//----------------------------
	SAFE_END(m_phase);

	//----------------------------
	// 共通部
	//----------------------------
	// インポート
	SAFE_END(m_import);

	// デバッグ表示
	SAFE_END(m_debugproc);

	// 入力
	SAFE_END(m_keyboard);

	// レンダラー
	SAFE_END(m_renderer);

	// 解放忘れをしない為
	CScene::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CManager::Update(void)
{
	//----------------------------
	// 共通部(レンダラー、サウンド以外)
	//----------------------------
	// デバッグ表示
	m_debugproc->Update();

#ifdef _DEBUG
	// FPS更新
	m_debugproc->PrintDebugProc("FPS:%d\n", m_renderer->GetFPS());
#endif

	// 入力
	m_keyboard->Update();

	//----------------------------
	// フェーズ
	//----------------------------
	if(m_phase != nullptr)
	{
		m_phase->Update();
	}

	//----------------------------
	// レンダラー、サウンド
	//----------------------------
	// レンダラー
	m_renderer->Update();

	//----------------------------
	// フェーズ切替
	//----------------------------
	if(m_phaseNext != m_phase)
	{
		// 現在フェーズを破棄
		SAFE_END(m_phase);

		// 次のフェーズを生成・初期化
		m_phase = m_phaseNext;
		m_phase->Init(m_renderer->GetDevice());
	}
}

//=============================================================================
// 描画
//=============================================================================
void CManager::Draw(void)
{
	//----------------------------
	// フェーズ
	//----------------------------
	if(m_phase != nullptr)
	{
		m_phase->Draw();
	}

	//----------------------------
	// レンダラー
	//----------------------------
	m_renderer->Draw();
}

//=============================================================================
// FPS測定
//=============================================================================
void CManager::CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime)
{
	m_renderer->SetFPS(frameCnt * 1000 / (curTime - FPSLastTime));
}

//=============================================================================
// 背景生成
//=============================================================================
void CManager::CreateBg(int no, int category, int type)
{
	if(m_phase != nullptr)
	{
		m_phase->CreateBg(no, category, type);
	}
}

//=============================================================================
// 背景削除
//=============================================================================
void CManager::DeleteBg(int no)
{
	if(m_phase != nullptr)
	{
		m_phase->DeleteBg(no);
	}
}

//=============================================================================
// オブジェクト生成
//=============================================================================
void CManager::CreateObj(int no, int category, int type, int x, int y)
{
	if(m_phase != nullptr)
	{
		m_phase->CreateObj(no, category, type, x, y);
	}
}

//=============================================================================
// オブジェクト削除
//=============================================================================
void CManager::DeleteObj(int no, int category)
{
	if(m_phase != nullptr)
	{
		m_phase->DeleteObj(no, category);
	}
}

//=============================================================================
// スクロール
//=============================================================================
void CManager::Scroll(float scroll)
{
	if(m_phase != nullptr)
	{
		m_phase->Scroll(scroll);
	}
}

//=============================================================================
// ページ取得
//=============================================================================
int CManager::GetPage(void)
{
	return m_phase->GetPage();
}
