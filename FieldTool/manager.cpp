//*****************************************************************************
//
// CManeger�N���X [manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
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
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CPhase* CManager::m_phaseNext = nullptr;
HWND	CManager::m_window_handle = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager(void)
{

}

//=============================================================================
// ����
//=============================================================================
CManager* CManager::Create(HINSTANCE instance, HWND wnd, bool window)
{
	CManager* pointer = new CManager;
	pointer->Init(instance, wnd, window);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HINSTANCE instance, HWND wnd, bool window)
{
	LPDIRECT3DDEVICE9 device;

	//----------------------------
	// ���ʕ�
	//----------------------------
	// �E�B���h�E�n���h��
	m_window_handle = wnd;
	// �����_���[
	m_renderer	= CRenderer::Create(wnd, window);
	device		= m_renderer->GetDevice();

	// ����
	m_keyboard = CInputKeyboard::Create(instance, wnd);

	// �f�o�b�O�\��
	m_debugproc = CDebugproc::Create(device);
	m_renderer->SetDebugproc(m_debugproc);

	//----------------------------
	// �����N���\��
	//----------------------------
	CScene2D* setup = CScene2D::Create(device, "./data/TEXTURE/fade.jpg", CScene2D::POINT_CENTER);
	setup->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	setup->SetPos(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

	m_renderer->Draw();

	//----------------------------
	// �t�@�C���ǂݍ���
	//----------------------------
	m_import = CImport::Create(device);

	//----------------------------
	// �t�F�[�Y
	//----------------------------
	m_phase = (CPhase*)new CCreate;
	m_phase->Init(device);
	m_phase->SetKeyboard(m_keyboard);

	m_phaseNext = m_phase;

	//----------------------------
	// ���͐ݒ�
	//----------------------------
	m_debugproc->SetKeyboard(m_keyboard);

	//----------------------------
	// ����������
	//----------------------------
	// �N����ʔj��
	setup->UnLinkScene();
	SAFE_END(setup);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit(void)
{
	//----------------------------
	// �t�F�[�Y
	//----------------------------
	SAFE_END(m_phase);

	//----------------------------
	// ���ʕ�
	//----------------------------
	// �C���|�[�g
	SAFE_END(m_import);

	// �f�o�b�O�\��
	SAFE_END(m_debugproc);

	// ����
	SAFE_END(m_keyboard);

	// �����_���[
	SAFE_END(m_renderer);

	// ����Y������Ȃ���
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V
//=============================================================================
void CManager::Update(void)
{
	//----------------------------
	// ���ʕ�(�����_���[�A�T�E���h�ȊO)
	//----------------------------
	// �f�o�b�O�\��
	m_debugproc->Update();

#ifdef _DEBUG
	// FPS�X�V
	m_debugproc->PrintDebugProc("FPS:%d\n", m_renderer->GetFPS());
#endif

	// ����
	m_keyboard->Update();

	//----------------------------
	// �t�F�[�Y
	//----------------------------
	if(m_phase != nullptr)
	{
		m_phase->Update();
	}

	//----------------------------
	// �����_���[�A�T�E���h
	//----------------------------
	// �����_���[
	m_renderer->Update();

	//----------------------------
	// �t�F�[�Y�ؑ�
	//----------------------------
	if(m_phaseNext != m_phase)
	{
		// ���݃t�F�[�Y��j��
		SAFE_END(m_phase);

		// ���̃t�F�[�Y�𐶐��E������
		m_phase = m_phaseNext;
		m_phase->Init(m_renderer->GetDevice());
	}
}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw(void)
{
	//----------------------------
	// �t�F�[�Y
	//----------------------------
	if(m_phase != nullptr)
	{
		m_phase->Draw();
	}

	//----------------------------
	// �����_���[
	//----------------------------
	m_renderer->Draw();
}

//=============================================================================
// FPS����
//=============================================================================
void CManager::CalculateFPS(DWORD frameCnt, DWORD curTime, DWORD FPSLastTime)
{
	m_renderer->SetFPS(frameCnt * 1000 / (curTime - FPSLastTime));
}

//=============================================================================
// �w�i����
//=============================================================================
void CManager::CreateBg(int no, int category, int type)
{
	if(m_phase != nullptr)
	{
		m_phase->CreateBg(no, category, type);
	}
}

//=============================================================================
// �w�i�폜
//=============================================================================
void CManager::DeleteBg(int no)
{
	if(m_phase != nullptr)
	{
		m_phase->DeleteBg(no);
	}
}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
void CManager::CreateObj(int no, int category, int type, int x, int y)
{
	if(m_phase != nullptr)
	{
		m_phase->CreateObj(no, category, type, x, y);
	}
}

//=============================================================================
// �I�u�W�F�N�g�폜
//=============================================================================
void CManager::DeleteObj(int no, int category)
{
	if(m_phase != nullptr)
	{
		m_phase->DeleteObj(no, category);
	}
}
