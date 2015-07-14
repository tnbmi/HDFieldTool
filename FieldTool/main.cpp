//*****************************************************************************
//
// ���C������ [main.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "resource.h"
#include "debugproc.h"

#include "manager.h"
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// �E�B���h�E�ݒ�
//----------------------------
#define CLASS_NAME		"WindowClass"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�t�B�[���h�c�[��"	// �E�C���h�E�̃L���v�V������

//----------------------------
// ����}�N��
//----------------------------
#define CHK_INIT(init)	if(FAILED(init)){return -1;}	// �������`�F�b�N(WinMain���̂�)

#define TEXT_MAX	(256)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool g_initFlg = false;
CManager* g_manager = nullptr;

HWND g_toolBoxDlgWnd = nullptr;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	// �������[���[�N�`�F�b�N
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(prevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(cmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD execLastTime;	// ��������
	DWORD FPSLastTime;	// FPS���莞��
	DWORD curTime;		// ���ݎ���
	DWORD frameCnt;		// �t���[���J�E���g

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,						// �E�C���h�E�̃��C�A�E�g
		WndProc,						// �v���V�[�W���֐�
		0,
		0,
		instance,						// �C���X�^���X�n���h��
		nullptr,						// �A�C�R���w��
		LoadCursor(nullptr, IDC_ARROW),	// �}�E�X�J�[�\���w��
		(HBRUSH)(COLOR_WINDOW + 0),		// �w�i
		MAKEINTRESOURCE(nullptr),		// ���j���[�̕\��
		CLASS_NAME,						// �E�C���h�E�N���X�̖��O
		nullptr							// �������A�C�R���w��
	};
	MSG msg;	// ���b�Z�[�W
	
	//----------------------------
	// �E�B���h�E�N���X�̓o�^
	//----------------------------
	RegisterClassEx(&wcex);
	
	//----------------------------
	// �E�B���h�E�̍쐬
	//----------------------------
	HWND wnd;	// �E�C���h�E�n���h��
	int width  = static_cast<int>(SCREEN_WIDTH) + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height = static_cast<int>(SCREEN_HEIGHT) + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	wnd = CreateWindowEx(0,
						CLASS_NAME,				// �N���X�̖��O
						WINDOW_NAME,			// �L���v�V������
						WS_OVERLAPPEDWINDOW,	// �X�^�C��
						CW_USEDEFAULT,			// X���W
						CW_USEDEFAULT,			// Y���W
						width,					// ����
						height,					// �c��
						nullptr,
						nullptr,
						instance,				// �C���X�^���X�n���h��
						nullptr);

	//----------------------------
	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	//----------------------------
	ShowWindow(wnd, cmdShow);
	UpdateWindow(wnd);

	//----------------------------
	// ����������
	//----------------------------
	// �}�l�[�W��
	g_manager = CManager::Create(instance, wnd, true);
	g_initFlg = true;

	// �t���[���J�E���g
	timeBeginPeriod(1);				// ����\��ݒ�
	execLastTime = timeGetTime();
	FPSLastTime	 = execLastTime;	// �V�X�e���������~���b�P�ʂŎ擾
	curTime	 = 0;					// ���ݎ����ƃJ�E���g�̏�����
	frameCnt	 = curTime;

	//----------------------------
	// ���b�Z�[�W���[�v
	//----------------------------
	while(1)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{
			//----------------------------
			// Windows�̏���
			//----------------------------
			if(msg.message == WM_QUIT)
			{
				// ���[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);	// �|��
				DispatchMessage(&msg);	// ���M
			}
		}
		else
		{
			curTime = timeGetTime();	// �V�X�e���������擾

			if((curTime - FPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				// FPS�𑪒�
				g_manager->CalculateFPS(frameCnt, curTime, FPSLastTime);
#endif
				FPSLastTime = curTime;	// FPS�𑪒肵��������ۑ�
				frameCnt = 0;			// �J�E���g���N���A
			}

			if((curTime - execLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				execLastTime = curTime;	// ��������������ۑ�
				
				//----------------------------
				// DirectX�̏���
				//----------------------------
				// �X�V����
				g_manager->Update();

				// �`�揈��
				g_manager->Draw();

				// �J�E���g�����Z
				frameCnt++;
			}
		}
	}

	//----------------------------
	// �I������
	//----------------------------
	// �t���[���J�E���g
	timeEndPeriod(1);	// ����\��߂�

	// �}�l�[�W��
	SAFE_END(g_manager);

	//----------------------------
	// �E�B���h�E�o�^�̉���
	//----------------------------
	UnregisterClass( CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// �E�C���h�E�𐶐�
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
	// �E�C���h�E�j��
	//----------------------------
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//----------------------------
	// ���N���b�N
	//----------------------------
	case WM_LBUTTONDOWN:
		{
			// ���W�ݒ�
			POINT pt;
			GetCursorPos(&pt);		// �f�B�X�v���C��
			ScreenToClient(wnd, &pt);	// �E�B���h�E�̈���W�ɂ���

			// �O���b�h�v�Z
			int gridX = pt.x / 64;
			int gridY = 10 - ((pt.y - 16) / 64);
			g_manager->SetGrid(gridX, gridY);

			// �I�u�W�F�N�g����
			int category = SendMessage(GetDlgItem(g_toolBoxDlgWnd, COMBO_OBJ_CATEGORY), CB_GETCURSEL, 0, 0);
			int type	 = SendMessage(GetDlgItem(g_toolBoxDlgWnd, COMBO_OBJ_TYPE), CB_GETCURSEL, 0, 0);
			g_manager->CreateObj(category, type, gridX, gridY);
			break;
		}

	//----------------------------
	// �E�N���b�N
	//----------------------------
	case WM_RBUTTONDOWN:
		{
			// ���W�ݒ�
			POINT pt;
			GetCursorPos(&pt);		// �f�B�X�v���C��
			ScreenToClient(wnd, &pt);	// �E�B���h�E�̈���W�ɂ���

			// �O���b�h�v�Z
			int gridX = pt.x / 64;
			int gridY = 10 - ((pt.y - 16) / 64);
			g_manager->SetGrid(gridX, gridY);

			// �I�u�W�F�N�g����
			g_manager->DeleteObj(gridX, gridY);
			break;
		}

	//----------------------------
	// �L�[�{�[�h����
	//----------------------------
	case WM_KEYDOWN:
		switch(wParam)
		{
		// ESC�������ꂽ�Ƃ�
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
// �c�[���{�b�N�X�_�C�A���O�v���V�[�W��
//=============================================================================
BOOL CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//----------------------------
	// �R���{�{�b�N�X������
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
	// ������
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, EDIT_PAGE,	0, false);
			return TRUE;
		}

	//----------------------------
	// �R�}���h
	//----------------------------
	case WM_COMMAND:
		{
			//=============================================
			switch(LOWORD(wParam))
			{
			// �L�����Z���{�^��
			case IDCANCEL:
				DestroyWindow(wnd);
				g_toolBoxDlgWnd = nullptr;
				break;

			// �ǂݍ���
			case BTN_LOAD:
				{
					OPENFILENAME ofn = {0};
					char		 defDir[MAX_PATH]	= {0};
					char		 file[MAX_PATH]		= {0};
					char		 fileName[MAX_PATH] = {0};

					// �J�����g�f�B���N�g���擾
					GetCurrentDirectory(MAX_PATH, &defDir[0]);

					// �I�[�v���t�@�C���̐ݒ�
					ofn.lStructSize		= sizeof(OPENFILENAME);
					ofn.hwndOwner		= wnd;
					ofn.lpstrInitialDir	= defDir;
					ofn.lpstrFilter		= "�e�L�X�g(*.txt)\0*.txt\0";
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

			// �ۑ�
			case BTN_SAVE:
				{
					OPENFILENAME ofn = {0};
					char		 defDir[MAX_PATH]	= {0};
					char		 file[MAX_PATH]		= {0};
					char		 fileName[MAX_PATH] = {0};

					// �J�����g�f�B���N�g���擾
					GetCurrentDirectory(MAX_PATH, &defDir[0]);

					// �I�[�v���t�@�C���̐ݒ�
					ofn.lStructSize		= sizeof(OPENFILENAME);
					ofn.hwndOwner		= wnd;
					ofn.lpstrInitialDir	= defDir;
					ofn.lpstrFilter		= "�e�L�X�g(*.txt)\0*.txt\0";
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

			// ���X�N���[���{�^��
			case BTN_SCROLL_L:
				g_manager->Scroll((float)-SCREEN_WIDTH);
				SetDlgItemInt(wnd, EDIT_PAGE, g_manager->GetPage(), false);
				break;

			// �E�X�N���[���{�^��
			case BTN_SCROLL_R:
				g_manager->Scroll((float)SCREEN_WIDTH);
				SetDlgItemInt(wnd, EDIT_PAGE, g_manager->GetPage(), false);
				break;

			// �w�i�Z�b�g�{�^��
			case BTN_BG_SET:
				{
					int no	 = GetDlgItemInt(wnd, EDIT_PAGE, false, false);
					int type = SendMessage(GetDlgItem(wnd, COMBO_TYPE), CB_GETCURSEL, 0, 0);
					g_manager->CreateBg(no, type);
					break;
				}

			// �w�i�폜�{�^��
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
			// �R���{�{�b�N�X�I��ύX
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
