//*****************************************************************************
//
// CListMapData�N���X [listMapData.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "listMapData.h"

#include "background.h"
#include "road.h"
#include "stumbler.h"
#include "target.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �w�i
CBackground* CListMapData::m_topBg = nullptr;
CBackground* CListMapData::m_curBg = nullptr;
unsigned int CListMapData::m_numBg = 0;

// ��
CRoad*		 CListMapData::m_topRoad = nullptr;
CRoad*		 CListMapData::m_curRoad = nullptr;
unsigned int CListMapData::m_numRoad = 0;

// ��Q��
CStumbler*	 CListMapData::m_topStum = nullptr;
CStumbler*	 CListMapData::m_curStum = nullptr;
unsigned int CListMapData::m_numStum = 0;

// �^�[�Q�b�g
CTarget*	 CListMapData::m_topTarget = nullptr;
CTarget*	 CListMapData::m_curTarget = nullptr;
unsigned int CListMapData::m_numTarget = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CListMapData::CListMapData()
{
	// �w�i
	m_topBg = nullptr;
	m_curBg = nullptr;
	m_numBg = 0;

	// ��
	m_topRoad = nullptr;
	m_curRoad = nullptr;
	m_numRoad = 0;

	// ��Q��
	m_topStum = nullptr;
	m_curStum = nullptr;
	m_numStum = 0;

	// �^�[�Q�b�g
	m_topTarget = nullptr;
	m_curTarget = nullptr;
	m_numTarget = 0;
}

//=============================================================================
// �w�i���X�g�ǉ�
//=============================================================================
void CListMapData::LinkBg(unsigned int no, CBackground* obj)
{
	//----------------------------
	// �����`�F�b�N
	//----------------------------
	CBackground* objChk = GetBg(no);
	if(objChk != nullptr)
	{
		// ���ɂ�������폜
		UnlinkBg(obj);

		// �S�̃J�E���g
		m_numBg--;
	}

	//----------------------------
	// �V�K�ǉ�
	//----------------------------
	// �擪�`�F�b�N
	if(m_topBg == nullptr)
	{
		m_topBg = obj;
		obj->SetBgPrev(nullptr);
	}
	else
	{
		// �O�I�u�W�F�N�g����A��
		m_curBg->SetBgNext(obj);
		obj->SetBgPrev(m_curBg);
	}

	// ���I�u�W�F�N�g������
	obj->SetBgNext(nullptr);
	// �I�[�A�h���X�ݒ�
	m_curBg = obj;

	// �S�̃J�E���g
	m_numBg++;
}

//=============================================================================
// �w�i���X�g����j��
//=============================================================================
void CListMapData::UnlinkBg(CBackground* obj)
{
	CBackground* prev = obj->GetBgPrev();
	CBackground* next = obj->GetBgNext();

	if(prev != nullptr)
	{
		prev->SetBgNext(next);
	}
	else // Top�������ꍇ
	{
		m_topBg = next;

		if(m_topBg != nullptr)
		{
			m_topBg->SetBgPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetBgPrev(prev);
	}
	else // Cur�������ꍇ
	{
		m_curBg = prev;

		if(m_curBg != nullptr)
		{
			m_curBg->SetBgNext(nullptr);
		}
	}
}

//=============================================================================
// �w�i���X�g����C�ӂ̕����擾
//=============================================================================
CBackground* CListMapData::GetBg(unsigned int no)
{
	CBackground* obj = m_topBg;

	// �C�ӂ̐��܂Ői��
	for(unsigned int cnt = 0; cnt < m_numBg; ++cnt)
	{
		if(obj->GetData().index == no)
		{
			return obj;
		}

		obj = obj->GetBgNext();
	}

	return nullptr;
}

//=============================================================================
// �w�i���X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelBg(unsigned int no)
{
	CBackground* obj = GetBg(no);

	if(obj != nullptr)
	{
		// ���X�g����j��
		UnlinkBg(obj);

		// �V�[�����폜
		obj->Uninit();

		// �S�̃J�E���g
		m_numBg--;
	}
	else
	{
		MessageBox(nullptr, "���̔ԍ��͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
	}
}

//=============================================================================
// �����X�g�ǉ�
//=============================================================================
void CListMapData::LinkRoad(unsigned int no, CRoad* obj)
{
	// �擪�`�F�b�N
	if(m_topRoad == nullptr)
	{
		m_topRoad = obj;
		obj->SetRoadPrev(nullptr);
	}
	else
	{
		// �O�I�u�W�F�N�g����A��
		m_curRoad->SetRoadNext(obj);
		obj->SetRoadPrev(m_curRoad);
	}

	// ���I�u�W�F�N�g������
	obj->SetRoadNext(nullptr);
	// �I�[�A�h���X�ݒ�
	m_curRoad = obj;

	// �S�̃J�E���g
	m_numRoad++;
}

//=============================================================================
// �����X�g����j��
//=============================================================================
void CListMapData::UnlinkRoad(CRoad* obj)
{
	CRoad* prev = obj->GetRoadPrev();
	CRoad* next = obj->GetRoadNext();

	if(prev != nullptr)
	{
		prev->SetRoadNext(next);
	}
	else // Top�������ꍇ
	{
		m_topRoad = next;

		if(m_topRoad != nullptr)
		{
			m_topRoad->SetRoadPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetRoadPrev(prev);
	}
	else // Cur�������ꍇ
	{
		m_curRoad = prev;

		if(m_curRoad != nullptr)
		{
			m_curRoad->SetRoadNext(nullptr);
		}
	}
}

//=============================================================================
// �����X�g����C�ӂ̕����擾
//=============================================================================
CRoad* CListMapData::GetRoad(unsigned int no)
{
	CRoad* obj = m_topRoad;

	// �C�ӂ̐��܂Ői��
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetRoadNext();
	}

	return obj;
}

//=============================================================================
// �����X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelRoad(unsigned int no)
{
	CRoad* obj = GetRoad(no);

	if(obj != nullptr)
	{
		// ���X�g����j��
		UnlinkRoad(obj);

		// �V�[�����폜
		obj->Uninit();

		// �S�̃J�E���g
		m_numRoad--;
	}
	else
	{
		MessageBox(nullptr, "���̔ԍ��͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
	}
}

//=============================================================================
// ��Q�����X�g�ǉ�
//=============================================================================
void CListMapData::LinkStum(unsigned int no, CStumbler* obj)
{
	// �擪�`�F�b�N
	if(m_topStum == nullptr)
	{
		m_topStum = obj;
		obj->SetStumPrev(nullptr);
	}
	else
	{
		// �O�I�u�W�F�N�g����A��
		m_curStum->SetStumNext(obj);
		obj->SetStumPrev(m_curStum);
	}

	// ���I�u�W�F�N�g������
	obj->SetStumNext(nullptr);
	// �I�[�A�h���X�ݒ�
	m_curStum = obj;

	// �S�̃J�E���g
	m_numStum++;
}

//=============================================================================
// ��Q�����X�g����j��
//=============================================================================
void CListMapData::UnlinkStum(CStumbler* obj)
{
	CStumbler* prev = obj->GetStumPrev();
	CStumbler* next = obj->GetStumNext();

	if(prev != nullptr)
	{
		prev->SetStumNext(next);
	}
	else // Top�������ꍇ
	{
		m_topStum = next;

		if(m_topStum != nullptr)
		{
			m_topStum->SetStumPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetStumPrev(prev);
	}
	else // Cur�������ꍇ
	{
		m_curStum = prev;

		if(m_curStum != nullptr)
		{
			m_curStum->SetStumNext(nullptr);
		}
	}
}

//=============================================================================
// ��Q�����X�g����C�ӂ̕����擾
//=============================================================================
CStumbler* CListMapData::GetStum(unsigned int no)
{
	CStumbler* obj = m_topStum;

	// �C�ӂ̐��܂Ői��
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetStumNext();
	}

	return obj;
}

//=============================================================================
// ��Q�����X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelStum(unsigned int no)
{
	CStumbler* obj = GetStum(no);

	if(obj != nullptr)
	{
		// ���X�g����j��
		UnlinkStum(obj);

		// �V�[�����폜
		obj->Uninit();

		// �S�̃J�E���g
		m_numStum--;
	}
	else
	{
		MessageBox(nullptr, "���̔ԍ��͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
	}
}

//=============================================================================
// �^�[�Q�b�g���X�g�ǉ�
//=============================================================================
void CListMapData::LinkTarget(unsigned int no, CTarget* obj)
{
	// �擪�`�F�b�N
	if(m_topTarget == nullptr)
	{
		m_topTarget = obj;
		obj->SetTargetPrev(nullptr);
	}
	else
	{
		// �O�I�u�W�F�N�g����A��
		m_curTarget->SetTargetNext(obj);
		obj->SetTargetPrev(m_curTarget);
	}

	// ���I�u�W�F�N�g������
	obj->SetTargetNext(nullptr);
	// �I�[�A�h���X�ݒ�
	m_curTarget = obj;

	// �S�̃J�E���g
	m_numTarget++;
}

//=============================================================================
// �^�[�Q�b�g���X�g����j��
//=============================================================================
void CListMapData::UnlinkTarget(CTarget* obj)
{
	CTarget* prev = obj->GetTargetPrev();
	CTarget* next = obj->GetTargetNext();

	if(prev != nullptr)
	{
		prev->SetTargetNext(next);
	}
	else // Top�������ꍇ
	{
		m_topTarget = next;

		if(m_topTarget != nullptr)
		{
			m_topTarget->SetTargetPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetTargetPrev(prev);
	}
	else // Cur�������ꍇ
	{
		m_curTarget = prev;

		if(m_curTarget != nullptr)
		{
			m_curTarget->SetTargetNext(nullptr);
		}
	}
}

//=============================================================================
// �^�[�Q�b�g���X�g����C�ӂ̕����擾
//=============================================================================
CTarget* CListMapData::GetTarget(unsigned int no)
{
	CTarget* obj = m_topTarget;

	// �C�ӂ̐��܂Ői��
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetTargetNext();
	}

	return obj;
}

//=============================================================================
// �^�[�Q�b�g���X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelTarget(unsigned int no)
{
	CTarget* obj = GetTarget(no);

	if(obj != nullptr)
	{
		// ���X�g����j��
		UnlinkTarget(obj);

		// �V�[�����폜
		obj->Uninit();

		// �S�̃J�E���g
		m_numTarget--;
	}
	else
	{
		MessageBox(nullptr, "���̔ԍ��͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
	}
}

//=============================================================================
// �X�N���[��
//=============================================================================
void CListMapData::Scroll(float scroll)
{
	// �w�i
	CBackground* bg = m_topBg;
	while(bg)
	{
		bg->Scroll(scroll);
		bg = bg->GetBgNext();
	}

	// ��
	CRoad* road = m_topRoad;
	while(road)
	{
		road->Scroll(scroll);
		road = road->GetRoadNext();
	}

	// ��Q��
	CStumbler* stum = m_topStum;
	while(stum)
	{
		stum->Scroll(scroll);
		stum = stum->GetStumNext();
	}

	// �^�[�Q�b�g
	CTarget* target = m_topTarget;
	while(target)
	{
		target->Scroll(scroll);
		target = target->GetTargetNext();
	}
}
