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
#include "debugproc.h"

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

#define TEXT_MAX	(256)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool g_initFlg = false;
CManager* g_manager = nullptr;

HWND g_toolBoxDlgWnd = nullptr;

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
		nullptr,						// アイコン指定
		LoadCursor(nullptr, IDC_ARROW),	// マウスカーソル指定
		(HBRUSH)(COLOR_WINDOW + 0),		// 背景
		MAKEINTRESOURCE(nullptr),		// メニューの表示
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
	g_initFlg = true;

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
	// 左クリック
	//----------------------------
	case WM_LBUTTONDOWN:
		{
			// 座標設定
			POINT pt;
			GetCursorPos(&pt);		// ディスプレイ上
			ScreenToClient(wnd, &pt);	// ウィンドウ領域座標にする

			// グリッド計算
			int gridX = pt.x / 64;
			int gridY = 10 - ((pt.y - 16) / 64);
			g_manager->SetGrid(gridX, gridY);

			// オブジェクト生成
			int category = SendMessage(GetDlgItem(g_toolBoxDlgWnd, COMBO_OBJ_CATEGORY), CB_GETCURSEL, 0, 0);
			int type	 = SendMessage(GetDlgItem(g_toolBoxDlgWnd, COMBO_OBJ_TYPE), CB_GETCURSEL, 0, 0);
			g_manager->CreateObj(category, type, gridX, gridY);
			break;
		}

	//----------------------------
	// 右クリック
	//----------------------------
	case WM_RBUTTONDOWN:
		{
			// 座標設定
			POINT pt;
			GetCursorPos(&pt);		// ディスプレイ上
			ScreenToClient(wnd, &pt);	// ウィンドウ領域座標にする

			// グリッド計算
			int gridX = pt.x / 64;
			int gridY = 10 - ((pt.y - 16) / 64);
			g_manager->SetGrid(gridX, gridY);

			// オブジェクト生成
			g_manager->DeleteObj(gridX, gridY);
			break;
		}

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
	//----------------------------
	// コンボボックス初期化
	//----------------------------
	if(g_initFlg)
	{
		CImport* import = g_manager->GetImport();
		import->SetComboBgType(wnd, COMBO_BG_TYPE);
		import->SetComboObjCategory(wnd, COMBO_OBJ_CATEGORY);
		g_initFlg = false;
	}

	switch(msg)
	{
	//----------------------------
	// 初期化
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, EDIT_PAGE,	0, false);
			return TRUE;
		}

	//----------------------------
	// コマンド
	//----------------------------
	case WM_COMMAND:
		{
			//=============================================
			switch(LOWORD(wParam))
			{
			// キャンセルボタン
			case IDCANCEL:
				DestroyWindow(wnd);
				g_toolBoxDlgWnd = nullptr;
				break;

			// 読み込み
			case BTN_LOAD:
				{
					OPENFILENAME ofn = {0};
					char		 defDir[MAX_PATH]	= {0};
					char		 file[MAX_PATH]		= {0};
					char		 fileName[MAX_PATH] = {0};

					// カレントディレクトリ取得
					GetCurrentDirectory(MAX_PATH, &defDir[0]);

					// オープンファイルの設定
					ofn.lStructSize		= sizeof(OPENFILENAME);
					ofn.hwndOwner		= wnd;
					ofn.lpstrInitialDir	= defDir;
					ofn.lpstrFilter		= "テキスト(*.txt)\0*.txt\0";
					ofn.lpstrFile		= file;
					ofn.nMaxFile		= MAX_PATH;
					ofn.lpstrFileTitle	= fileName;
					ofn.nMaxFileTitle	= MAX_PATH;
					ofn.Flags			= OFN_PATHMUSTEXIST;
					ofn.lpstrDefExt		= "txt";

					if(GetOpenFileName(&ofn))
					{
						g_manager->LoadMap(g_manager, ofn.lpstrFile, ofn.lpstrFileTitle);
					}
					break;
				}

			// 保存
			case BTN_SAVE:
				{
					OPENFILENAME ofn = {0};
					char		 defDir[MAX_PATH]	= {0};
					char		 file[MAX_PATH]		= {0};
					char		 fileName[MAX_PATH] = {0};

					// カレントディレクトリ取得
					GetCurrentDirectory(MAX_PATH, &defDir[0]);

					// オープンファイルの設定
					ofn.lStructSize		= sizeof(OPENFILENAME);
					ofn.hwndOwner		= wnd;
					ofn.lpstrInitialDir	= defDir;
					ofn.lpstrFilter		= "テキスト(*.txt)\0*.txt\0";
					ofn.lpstrFile		= file;
					ofn.nMaxFile		= MAX_PATH;
					ofn.lpstrFileTitle	= fileName;
					ofn.nMaxFileTitle	= MAX_PATH;
					ofn.Flags			= OFN_PATHMUSTEXIST;
					ofn.lpstrDefExt		= "txt";

					if(GetSaveFileName(&ofn))
					{
						g_manager->SaveMap(ofn.lpstrFile, ofn.lpstrFileTitle);
					}
					break;
				}

			// 左スクロールボタン
			case BTN_SCROLL_L:
				g_manager->Scroll((float)-SCREEN_WIDTH);
				SetDlgItemInt(wnd, EDIT_PAGE, g_manager->GetPage(), false);
				break;

			// 右スクロールボタン
			case BTN_SCROLL_R:
				g_manager->Scroll((float)SCREEN_WIDTH);
				SetDlgItemInt(wnd, EDIT_PAGE, g_manager->GetPage(), false);
				break;

			// 背景セットボタン
			case BTN_BG_SET:
				{
					int no	 = GetDlgItemInt(wnd, EDIT_PAGE, false, false);
					int type = SendMessage(GetDlgItem(wnd, COMBO_TYPE), CB_GETCURSEL, 0, 0);
					g_manager->CreateBg(no, type);
					break;
				}

			// 背景削除ボタン
			case BTN_BG_DEL:
				{
					int no = GetDlgItemInt(wnd, EDIT_PAGE, false, false);
					g_manager->DeleteBg(no);
					break;
				}
			}

			//=============================================
			switch(HIWORD(wParam))
			{
			// コンボボックス選択変更
			case CBN_SELENDOK:
				int category = SendMessage(GetDlgItem(wnd, COMBO_OBJ_CATEGORY), CB_GETCURSEL, 0, 0);
				g_manager->GetImport()->SetComboObjType(wnd, COMBO_OBJ_TYPE, category);
				break;
			}

			break;
		}
	}

	return FALSE;
}
