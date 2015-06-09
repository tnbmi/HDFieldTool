//*****************************************************************************
//
// CInputPadDirect�N���X [inputPadX.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "inputPadDirect.h"
#include "manager.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PAD_STICK_INPUTLANGE	( 32 )

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �X�^�e�B�b�N�ϐ��錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTINPUTDEVICE8 CInputPadDirect::m_input_device;
bool CInputPadDirect::m_state[PAD_MAX];
bool CInputPadDirect::m_press[PAD_MAX];
bool CInputPadDirect::m_trigger[PAD_MAX];
bool CInputPadDirect::m_repeat[PAD_MAX];
bool CInputPadDirect::m_release[PAD_MAX];
int	 CInputPadDirect::m_repeatcount[PAD_MAX];


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputPadDirect::CInputPadDirect(void)
{

}

//=============================================================================
// ����
//=============================================================================
CInputPadDirect* CInputPadDirect::Create(void)
{
	CInputPadDirect* pointer = new CInputPadDirect;
	pointer->Init();
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CInputPadDirect::Init(void)
{
	//----------------------------
	// �ϐ��錾
	//----------------------------
	HRESULT result;

	//----------------------------
	// �f�o�C�X����
	//----------------------------
	result = m_input->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		CallBackPad,
		NULL,
		DIEDFL_ATTACHEDONLY);

	// �G���[�`�F�b�N
	if (FAILED(result) || m_input_device == NULL)
	{
		return E_FAIL;
	}
	
	//----------------------------
	// �f�o�C�X���ݒ�
	//----------------------------
	result = m_input_device->SetDataFormat(&c_dfDIJoystick2);

	// �G���[�`�F�b�N
	if (FAILED(result))
	{
		return E_FAIL;
	}

	//----------------------------
	// �f�o�C�X�������x����ݒ�
	//----------------------------
	result = m_input_device->SetCooperativeLevel(CManager::GetWindowHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// �G���[�`�F�b�N
	if (FAILED(result))
	{
		return E_FAIL;
	}

	//----------------------------
	// �g�p�\�ȃf�o�C�X�̌���
	//----------------------------
	result = m_input_device->EnumObjects(CallBackAces, NULL, DIDFT_AXIS);

	// �G���[�`�F�b�N
	if (FAILED(result))
	{
		return E_FAIL;
	}

	// ���͋��̗v��
	m_input_device->Acquire();

	// ���[�N�𐶐�
	memset(&m_joystate, 0, sizeof(m_joystate));
	memset(&m_press, 0, sizeof(m_press));
	memset(&m_trigger, 0, sizeof(m_trigger));
	memset(&m_repeat, 0, sizeof(m_repeat));
	memset(&m_release, 0, sizeof(m_release));

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CInputPadDirect::Uninit(void)
{
	// �p�b�h�p�f�o�C�X�̔j��
	if (m_input_device)
	{
		m_input_device->Unacquire();
		m_input_device->Release();
		m_input_device = NULL;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CInputPadDirect::Update(void)
{

	// �ϐ��錾
	bool State[PAD_MAX];


	// �f�o�C�X�����m�F
	if (m_input_device == NULL)
	{
		return;
	}


	// �f�o�C�X����X�e�[�^�X���擾
	if (SUCCEEDED(m_input_device->GetDeviceState(sizeof(m_joystate), &m_joystate)))
	{

		for (int nPad = 0, nCnt = 0; nPad + nCnt < PAD_MAX; nPad++)
		{
			// �A�i���O�X�e�B�b�N
			if (nPad == 0)
			{
				State[PAD_LS_LEFT] = m_joystate.lX < -PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 225 * 100 && m_joystate.rgdwPOV[0] <= 315 * 100);
				State[PAD_LS_RIGHT] = m_joystate.lX > PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 45 * 100 && m_joystate.rgdwPOV[0] <= 135 * 100);
				State[PAD_LS_UP] = m_joystate.lY < -PAD_STICK_INPUTLANGE || ((m_joystate.rgdwPOV[0] >= 315 * 100 && m_joystate.rgdwPOV[0] <= 360 * 100) || (m_joystate.rgdwPOV[0] >= 0 * 100 && m_joystate.rgdwPOV[0] <= 45 * 100));
				State[PAD_LS_DOWN] = m_joystate.lY > PAD_STICK_INPUTLANGE || (m_joystate.rgdwPOV[0] >= 135 * 100 && m_joystate.rgdwPOV[0] <= 225 * 100);

				State[PAD_RS_LEFT] = m_joystate.lZ < -PAD_STICK_INPUTLANGE;
				State[PAD_RS_RIGHT] = m_joystate.lZ > PAD_STICK_INPUTLANGE;
				State[PAD_RS_UP] = m_joystate.lRz < -PAD_STICK_INPUTLANGE;
				State[PAD_RS_DOWN] = m_joystate.lRz > PAD_STICK_INPUTLANGE;

				nCnt = 8;
			}

			State[nPad + nCnt] = m_joystate.rgbButtons[nPad] == 128;
		}

		for (int nPad = 0; nPad < PAD_MAX; nPad++)
		{
			m_trigger[nPad] = (State[nPad] ^ m_state[nPad]) & State[nPad];
			m_release[nPad] = (State[nPad] ^ m_state[nPad]) & m_state[nPad];
			m_press[nPad] = State[nPad];

			// PadState Regist
			m_state[nPad] = State[nPad];

		}
	}

	// �f�o�C�X�X�e�[�^�X���擾�ł��Ă��Ȃ�������ėv��
	else
	{
		m_input_device->Acquire();
	}

}

//=============================================================================
// �f�o�C�X�I�u�W�F�N�g�̃R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputPadDirect::CallBackPad(const DIDEVICEINSTANCE *lpddi, VOID *pvRef)
{
	// �ϐ��錾
	DIDEVCAPS	DevCaps;
	HRESULT		Result;

	// �W���C�p�b�h�p�f�o�C�X�̐���
	Result = m_input->CreateDevice(lpddi->guidInstance, &m_input_device, NULL);

	// �G���[�`�F�b�N
	if (FAILED(Result))
	{
		return DIENUM_CONTINUE;
	}

	// �p�b�h�̃X�e�[�^�X������
	DevCaps.dwSize = sizeof(DIDEVCAPS);
	Result = m_input_device->GetCapabilities(&DevCaps);

	// �G���[�`�F�b�N
	if (FAILED(Result))
	{
		m_input_device->Release();
		m_input_device = NULL;
		return DIENUM_CONTINUE;
	}

	// ���^�[��
	return DIENUM_STOP;
}


//=============================================================================
// �f�o�C�X�̃R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputPadDirect::CallBackAces(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	// �ϐ��錾
	HRESULT Result;

	// �A�i���O�X�e�B�b�N�̐[�x�l��ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = 1000;


	// �v���p�e�B�ݒ�
	Result = m_input_device->SetProperty(DIPROP_RANGE, &diprg.diph);

	// �G���[�`�F�b�N
	if (FAILED(Result))
	{
		return DIENUM_STOP;
	}

	// ���^�[��
	return DIENUM_CONTINUE;

}
