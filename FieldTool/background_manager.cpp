//*****************************************************************************
//
// CBackgroundManager�N���X [background_manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "background_manager.h"
#include "background.h"

#include "mapData.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundManager::CBackgroundManager()
{
	m_top = nullptr;
	m_cur = nullptr;
}

//=============================================================================
// ����
//=============================================================================
CBackgroundManager* CBackgroundManager::Create(LPDIRECT3DDEVICE9 device)
{
	CBackgroundManager* pointer = new CBackgroundManager;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBackgroundManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// �f�[�^�擾
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(CImport::STAGE_1_1);
	BG_DATA*	data = mapData->GetBgData();
	int			size = mapData->GetBgSize();

	//----------------------------------------
	// �f�[�^�̌�����������
	//----------------------------------------
	for(int cnt = 0; cnt < size; cnt++)
	{
		if(m_top == NULL)
		{
			m_top = CBackground::Create(device, data[cnt]);
			m_cur = m_top;
		}
		else
		{
			CBackground* pointer = CBackground::Create(device, data[cnt]);
			m_cur->SetBgNext(pointer);
			pointer->SetBgPrev(m_cur);
			m_cur = pointer;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CBackgroundManager::Scroll(float scroll)
{
	CBackground* cur = m_top;
	CBackground* next;

	while(cur)
	{
		cur->Scroll(scroll);

		next = cur->GetBgNext();

		cur = next;
	}
}
