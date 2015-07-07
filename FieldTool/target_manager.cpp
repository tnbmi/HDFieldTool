//=============================================================================
//
// target_manager�N���X [target_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// �C���N���[�h
//=============================================================================
#include "target_manager.h"
#include "target.h"

#include "mapData.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTargetManager::CTargetManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CTargetManager* CTargetManager::Create(LPDIRECT3DDEVICE9 device)
{
	CTargetManager* manager = new CTargetManager;

	if(manager->Init(device) == E_FAIL)
	{
		// �������R�P����
		return NULL;
	}
	return manager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTargetManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// �f�[�^�擾
	//----------------------------------------
	CMapData*	 mapData = CImport::GetMap(CImport::STAGE_1_1);
	TARGET_DATA* data = mapData->GetTargetData();
	int			 size = mapData->GetTargetSize();

	// �f�[�^�̌�����������
	for(int loop = 0; loop < size; loop++)
	{
		// ��Q�����X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ��Q�����X�g�擪�ɏ�Q������
			m_list_top = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g��������Q�����X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ��Q������
			CTarget* p = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g������next�ɐ���������Q�����Z�b�g
			m_list_cur->SetTargetNext(p);
			// ����������Q����prev�ɏ�Q�����X�g�������Z�b�g
			p->SetTargetPrev(m_list_cur);
			// ��Q�����X�g�����𐶐�������Q����
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTargetManager::Update(void)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetTargetNext();

		cur = next;
	}
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CTargetManager::Scroll(float f)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		cur->Scroll(f);

		next = cur->GetTargetNext();

		cur = next;
	}
}

//=============================================================================
// �p�[�e�B�N���p�Փ˔���
//=============================================================================
CTarget* CTargetManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType))
		{
			if(cur->GetTargetFrag() == true)
				return cur;
		}

		next = cur->GetTargetNext();

		cur = next;
	}
	return NULL;
}

//=============================================================================
// �S�[���p�Փ˔���
//=============================================================================
bool CTargetManager::CheckHitGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType))
		{
			if(cur->GetTargetFrag() != true)
				return true;
		}

		next = cur->GetTargetNext();

		cur = next;
	}
	return false;
}

//=============================================================================
// ���X�g����
//=============================================================================
void CTargetManager::UnLinkTarget(CTarget* cur)
{
	// ���X�g�擪�������ꍇ�A����Q�������X�g�擪��
	if(cur == m_list_top)
		m_list_top = cur->GetTargetNext();
	// ���X�g�����������ꍇ�A�O��Q�������X�g������
	if(cur == m_list_cur)
		m_list_cur = cur->GetTargetPrev();
}
// End of File