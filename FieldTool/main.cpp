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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ToolDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK BgDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK ObjDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CManager* g_manager = nullptr;

HWND g_toolBoxDlgWnd = nullptr;
HWND g_bgDlgWnd		 = nullptr;
HWND g_objDlgWnd	 = nullptr;

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
		nullptr,							// �A�C�R���w��
		LoadCursor(nullptr, IDC_ARROW),	// �}�E�X�J�[�\���w��
		(HBRUSH)(COLOR_WINDOW + 0),		// �w�i
		MAKEINTRESOURCE(nullptr),			// ���j���[�̕\��
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
	switch(msg)
	{
	//----------------------------
	// ������
	//----------------------------
	case WM_INITDIALOG:
		{
			return TRUE;
		}

	//----------------------------
	// �R�}���h
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			// �L�����Z���{�^��
			case IDCANCEL:
				DestroyWindow(wnd);
				g_toolBoxDlgWnd = nullptr;
				break;

			// �w�i�{�^��
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

			// �I�u�W�F�N�g�{�^��
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
// �w�i�_�C�A���O�v���V�[�W��
//=============================================================================
BOOL CALLBACK BgDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// ������
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, BG_NO, 0, false);
			g_manager->GetImport()->SetComboBgCategory(wnd, COMBO_CATEGORY);
			return TRUE;
		}

	//----------------------------
	// �R�}���h
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				// �L�����Z���{�^��
				case IDCANCEL:
				{
					DestroyWindow(wnd);
					g_bgDlgWnd = nullptr;
					break;
				}

				// �Z�b�g�{�^��
				case BTN_SET:
				{
					int no = GetDlgItemInt(wnd, BG_NO, false, false);
					int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
					int type	 = SendMessage(GetDlgItem(wnd, COMBO_TYPE), CB_GETCURSEL, 0, 0);
					g_manager->CreateBg(no, category, type);
					break;
				}

				// �폜�{�^��
				case BTN_DEL:
				{
					int no = GetDlgItemInt(wnd, BG_NO, false, false);
					g_manager->DeleteBg(no);
					break;
				}
			}

			switch(HIWORD(wParam))
			{
			// �R���{�{�b�N�X�I��ύX
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
// �I�u�W�F�N�g�_�C�A���O�v���V�[�W��
//=============================================================================
BOOL CALLBACK ObjDlgProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//----------------------------
	// ������
	//----------------------------
	case WM_INITDIALOG:
		{
			SetDlgItemInt(wnd, OBJ_NO, 0, false);
			g_manager->GetImport()->SetComboObjCategory(wnd, COMBO_CATEGORY);
			return TRUE;
		}

	//----------------------------
	// �R�}���h
	//----------------------------
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				// �L�����Z���{�^��
				case IDCANCEL:
				{
					DestroyWindow(wnd);
					g_objDlgWnd = nullptr;
					break;
				}

				// �Z�b�g�{�^��
				case BTN_SET:
				{
					int no = GetDlgItemInt(wnd, OBJ_NO, false, false);
					int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
					int type	 = SendMessage(GetDlgItem(wnd, COMBO_TYPE), CB_GETCURSEL, 0, 0);
					int x = GetDlgItemInt(wnd, OBJ_X, false, false);
					int y = GetDlgItemInt(wnd, OBJ_Y, false, false);
					g_manager->CreateObj(no, category, type, x, y);
					break;
				}

				// �폜�{�^��
				case BTN_DEL:
				{
					int no = GetDlgItemInt(wnd, OBJ_NO, false, false);
					int category = SendMessage(GetDlgItem(wnd, COMBO_CATEGORY), CB_GETCURSEL, 0, 0);
					g_manager->DeleteObj(no, category);
					break;
				}
			}

			switch(HIWORD(wParam))
			{
			// �R���{�{�b�N�X�I��ύX
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
