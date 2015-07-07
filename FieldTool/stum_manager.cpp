//=============================================================================
//
// stum_manager�N���X [stum_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// �C���N���[�h
//=============================================================================
#include "stum_manager.h"
#include "stumbler.h"

#include "mapData.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStumManager::CStumManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CStumManager* CStumManager::Create(LPDIRECT3DDEVICE9 device)
{
	CStumManager* manager = new CStumManager;

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
HRESULT CStumManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// �f�[�^�擾
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(CImport::STAGE_1_1);
	STUM_DATA*	data = mapData->GetStumData();
	int			size = mapData->GetStumSize();

	// �f�[�^�̌�����������
	for(int loop = 0; loop < size; loop++)
	{
		// ��Q�����X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ��Q�����X�g�擪�ɏ�Q������
			m_list_top = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g��������Q�����X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ��Q������
			CStumbler* p = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g������next�ɐ���������Q�����Z�b�g
			m_list_cur->SetStumNext(p);
			// ����������Q����prev�ɏ�Q�����X�g�������Z�b�g
			p->SetStumPrev(m_list_cur);
			// ��Q�����X�g�����𐶐�������Q����
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CStumManager::Update(void)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetStumNext();

		cur = next;
	}
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CStumManager::Scroll(float f)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		cur->Scroll(f);

		next = cur->GetStumNext();

		cur = next;
	}
}

//=============================================================================
// �Փ˔���
//=============================================================================
bool CStumManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
		{
			// �Ԃ����Ă��Q���Ƀ_���[�W
			cur->Attack(1);
			// �_���[�W�Ŏ���ł��烊�X�g����폜
			if(cur->LivingCheck())
				UnLinkStum(cur);
			return true;
		}

		next = cur->GetStumNext();

		cur = next;
	}
	return false;
}

//=============================================================================
// ���X�g����
//=============================================================================
void CStumManager::UnLinkStum(CStumbler* cur)
{
	// ���X�g�擪�������ꍇ�A����Q�������X�g�擪��
	if(cur == m_list_top)
		m_list_top = cur->GetStumNext();
	// ���X�g�����������ꍇ�A�O��Q�������X�g������
	if(cur == m_list_cur)
		m_list_cur = cur->GetStumPrev();
}
// End of File