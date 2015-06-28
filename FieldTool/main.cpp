//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "resource.h"

#include "manager.h"
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// ウィンドウ設定
//----------------------------
#define CLASS_NAME		"WindowClass"		// ウインドウのクラス名
#define WINDOW_NAME		"フィールドツール"	// ウインドウのキャプション名

//----------------------------
// 分岐マクロ
//----------------------------
#define CHK_INIT(init)	if(FAILED(init)){return -1;}	// 初期化チェック(WinMain内のみ)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK BgDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ObjDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CManager* g_manager = nullptr;

HWND g_toolBoxDlgWnd = nullptr;
HWND g_bgDlgWnd		 = nullptr;
HWND g_objDlgWnd	 = nullptr;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	// メモリーリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(prevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(cmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD execLastTime;	// 処理時刻
	DWORD FPSLastTime;	// FPS測定時刻
	DWORD curTime;		// 現在時刻
	DWORD frameCnt;		// フレームカウント

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,						// ウインドウのレイアウト
		WndProc,						// プロシージャ関数
		0,
		0,
		instance,						// インスタンスハンドル
		nullptr,							// アイコン指定
		LoadCursor(nullptr, IDC_ARROW),	// マウスカーソル指定
		(HBRUSH)(COLOR_WINDOW + 0),		// 背景
		MAKEINTRESOURCE(nullptr),			// メニューの表示
		CLASS_NAME,						// ウインドウクラスの名前
		nullptr							// 小さいアイコン指定
	};
	MSG msg;	// メッセージ
	
	//----------------------------
	// ウィンドウクラスの登録
	//----------------------------
	RegisterClassEx(&wcex);
	
	//----------------------------
	// ウィンドウの作成
	//----------------------------
	HWND wnd;	// ウインドウハンドル
	int width  = static_cast<int>(SCREEN_WIDTH) + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height = static_cast<int>(SCREEN_HEIGHT) + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	wnd = CreateWindowEx(0,
						CLASS_NAME,				// クラスの名前
						WINDOW_NAME,			// キャプション名
						WS_OVERLAPPEDWINDOW,	// スタイル
						CW_USEDEFAULT,			// X座標
						CW_USEDEFAULT,			// Y座標
						width,					// 横幅
						height,					// 縦幅
						nullptr,
						nullptr,
						instance,				// インスタンスハンドル
						nullptr);

	//----------------------------
	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	//----------------------------
	ShowWindow(wnd, cmdShow);
	UpdateWindow(wnd);

	//----------------------------
	// 初期化処理
	//----------------------------
	// マネージャ
	g_manager = CManager::Create(instance, wnd, true);

	// フレームカウント
	timeBeginPeriod(1);				// 分解能を設定
	execLastTime = timeGetTime();
	FPSLastTime	 = execLastTime;	// システム時刻をミリ秒単位で取得
	curTime	 = 0;					// 現在時刻とカウントの初期化
	frameCnt	 = curTime;

	//----------------------------
	// メッセージループ
	//----------------------------
	while(1)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // メッセージを取得しなかった場合"0"を返す
		{
			//----------------------------
			// Windowsの処理
			//----------------------------
			if(msg.message == WM_QUIT)
			{
				// ループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);	// 翻訳
				DispatchMessage(&msg);	// 送信
			}
		}
		else
		{
			curTime = timeGetTime();	// システム時刻を取得

			if((curTime - FPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				// FPSを測定
				g_manager->CalculateFPS(frameCnt, curTime, FPSLastTime);
#endif
				FPSLastTime = curTime;	// FPSを測定した時刻を保存
				frameCnt = 0;			// カウントをクリア
			}

			if((curTime - execLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				execLastTime = curTime;	// 処理した時刻を保存
				
				//----------------------------
				// DirectXの処理
				//----------------------------
				// 更新処理
				g_manager->Update();

				// 描画処理
				g_manager->Draw();

				// カウントを加算
				frameCnt++;
			}
		}
	}

	//----------------------------
	// 終了処理
	//----------------------------
	// フレームカウント
	timeEndPeriod(1);	// 分解能を戻す

	// マネージャ
	SAFE_END(g_manager);

	//----------------------------
	// ウィンドウ登録の解除
	//----------------------------
	UnregisterClass( CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// ウインドウを生成
	//----------------------------
	case WM_CREATE:
	{
		if(g_toolBoxDlgWnd == nullptr)
		{
			g_toolBoxDlgWnd = CreateDialog((HINSTANCE)GetWindowLong(wnd, GWL_HINSTANCE),
											MAKEINTRESOURCE(DIALOG_TOOL),
											wnd,
											ToolDlgProc);
			ShowWindow(g_toolBoxDlgWnd, SW_SHOW);
		}
		break;
	}

	//----------------------------
	// ウインドウ破棄
	//----------------------------
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//----------------------------
	// キーボード処理
	//----------------------------
	case WM_KEYDOWN:
		switch(wParam)
		{
		// ESCが押されたとき
		case VK_ESCAPE:
			DestroyWindow(wnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(wnd, msg, wParam, lParam);
}

//=============================================================================
// ツールボックスダイアログプロシージャ
//=============================================================================
BOOL CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// 初期化
	//----------------------------
	case WM_INITDIALOG:
		{
			return TRUE;
		}

	//----------------------------
	// コマンド
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			// キャンセルボタン
			case IDCANCEL:
				DestroyWindow(wnd);
				g_toolBoxDlgWnd = nullptr;
				break;

			// 背景ボタン
			case BTN_BG:
				if(g_bgDlgWnd == nullptr)
				{
					g_bgDlgWnd = CreateDialog((HINSTANCE)GetWindowLong(wnd, GWL_HINSTANCE),
												MAKEINTRESOURCE(DIALOG_BG),
												wnd,
												BgDlgProc);
					ShowWindow(g_bgDlgWnd, SW_SHOW);
				}
				break;

			// オブジェクトボタン
			case BTN_OBJ:
				if(g_objDlgWnd == nullptr)
				{
					g_objDlgWnd = CreateDialog((HINSTANCE)GetWindowLong(wnd, GWL_HINSTANCE),
												MAKEINTRESOURCE(DIALOG_OBJ),
												wnd,
												ObjDlgProc);
					ShowWindow(g_objDlgWnd, SW_SHOW);
				}
				break;
			}

			break;
		}
	}

	return FALSE;
}

//=============================================================================
// 背景ダイアログプロシージャ
//=============================================================================
BOOL CALLBACK BgDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// 初期化
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, BG_NO, 0, false);
			g_manager->GetImport()->SetComboBgCategory(wnd, COMBO_CATEGORY);
			return TRUE;
		}

	//----------------------------
	// コマンド
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			// キャンセルボタン
			case IDCANCEL:
				DestroyWindow(wnd);
				g_bgDlgWnd = nullptr;
				break;
			}

			switch(HIWORD(wParam))
			{
			// コンボボックス選択変更
			case CBN_SELENDOK:
				int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
				g_manager->GetImport()->SetComboBgType(wnd, COMBO_TYPE, category);
				break;

			}

			break;
		}
	}

	return FALSE;
}

//=============================================================================
// オブジェクトダイアログプロシージャ
//=============================================================================
BOOL CALLBACK ObjDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// 初期化
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, OBJ_NO, 0, false);
			g_manager->GetImport()->SetComboObjCategory(wnd, COMBO_CATEGORY);
			return TRUE;
		}

	//----------------------------
	// コマンド
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			// キャンセルボタン
			case IDCANCEL:
				DestroyWindow(wnd);
				g_objDlgWnd = nullptr;
				break;

			// セットボタン
			case BTN_SET:
				int no = GetDlgItemInt(wnd, OBJ_NO, false, false);
				int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
				int type	 = SendMessage(GetDlgItem(wnd, COMBO_TYPE), CB_GETCURSEL, 0, 0);
				int x = GetDlgItemInt(wnd, OBJ_X, false, false);
				int y = GetDlgItemInt(wnd, OBJ_Y, false, false);
				g_manager->CreateObject(no, category, type, x, y);
				break;
			}

			switch(HIWORD(wParam))
			{
			// コンボボックス選択変更
			case CBN_SELENDOK:
				int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
				g_manager->GetImport()->SetComboObjType(wnd, COMBO_TYPE, category);
				break;

			}

			break;
		}
	}

	return FALSE;
}
