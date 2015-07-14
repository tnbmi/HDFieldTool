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

#include "manager.h"

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
		DelBg(no);
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
// �w�i���X�g����C�ӂ̕����擾
//=============================================================================
CBackground* CListMapData::GetBg(unsigned int no)
{
	CBackground* obj = m_topBg;

	// �C�ӂ̐��܂Ői��
	for(unsigned int cnt = 0; cnt < m_numBg; ++cnt)
	{
		if(obj != nullptr)
		{
			if(obj->GetData().index == no)
			{
				return obj;
			}

			obj = obj->GetBgNext();
		}
	}

	return nullptr;
}

//=============================================================================
// �����X�g�ǉ�
//=============================================================================
void CListMapData::LinkRoad(CRoad* obj)
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
// �����X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelRoad(CRoad* obj)
{
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
		MessageBox(nullptr, "���̃I�u�W�F�N�g�͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
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
		if(obj != nullptr)
		{
			obj = obj->GetRoadNext();
		}
	}

	return obj;
}

//=============================================================================
// ��Q�����X�g�ǉ�
//=============================================================================
void CListMapData::LinkStum(CStumbler* obj)
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
// ��Q�����X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelStum(CStumbler* obj)
{
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
		MessageBox(nullptr, "���̃I�u�W�F�N�g�͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
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
		if(obj != nullptr)
		{
			obj = obj->GetStumNext();
		}
	}

	return obj;
}

//=============================================================================
// �^�[�Q�b�g���X�g�ǉ�
//=============================================================================
void CListMapData::LinkTarget(CTarget* obj)
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
// �^�[�Q�b�g���X�g�̔C�ӂ̕����폜
//=============================================================================
void CListMapData::DelTarget(CTarget* obj)
{
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
		MessageBox(nullptr, "���̃I�u�W�F�N�g�͑��݂��܂���B", "���݂��Ȃ��I�u�W�F�N�g", MB_OK);
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
		if(obj != nullptr)
		{
			obj = obj->GetTargetNext();
		}
	}

	return obj;
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

//=============================================================================
// �O���b�h�I�u�W�F�N�g�T��
//=============================================================================
int CListMapData::GridChk(int x, int y, CScene2D** obj)
{
	// ���T��
	if(GridChkRoad(x, y, (CRoad**)obj))
	{
		return 0;
	}

	// ��Q���T��
	if(GridChkStum(x, y, (CStumbler**)obj))
	{
		return 1;
	}

	// �^�[�Q�b�g�T��
	if(GridChkTarget(x, y, (CTarget**)obj))
	{
		return 2;
	}

	return -1;
}

//=============================================================================
// �O���b�h���T��
//=============================================================================
bool CListMapData::GridChkRoad(int x, int y, CRoad** obj)
{
	CRoad*	  road = nullptr;
	ROAD_DATA roadData;
	for(unsigned int cnt = 0; cnt < m_numRoad; ++cnt)
	{
		road = GetRoad(cnt);
		if(road != nullptr)
		{
			roadData = road->GetData();
			// �O���b�h��������
			if(roadData.Index.x == x && roadData.Index.y == y)
			{
				*obj = road;
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// �O���b�h��Q���T��
//=============================================================================
bool CListMapData::GridChkStum(int x, int y, CStumbler** obj)
{
	CStumbler*	stum = nullptr;
	STUM_DATA	stumData;
	for(unsigned int cnt = 0; cnt < m_numStum; ++cnt)
	{
		stum = GetStum(cnt);
		if(stum != nullptr)
		{
			stumData = stum->GetData();
			// �O���b�h��������
			if(stumData.Index.x == x && stumData.Index.y == y)
			{
				*obj = stum;
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// �O���b�h�^�[�Q�b�g�T��
//=============================================================================
bool CListMapData::GridChkTarget(int x, int y, CTarget** obj)
{
	CTarget*	target = nullptr;
	TARGET_DATA	targetData;
	for(unsigned int cnt = 0; cnt < m_numTarget; ++cnt)
	{
		target = GetTarget(cnt);
		if(target != nullptr)
		{
			targetData = target->GetData();
			// �O���b�h��������
			if(targetData.Index.x == x && targetData.Index.y == y)
			{
				*obj = target;
				return 2;
			}
		}
	}

	return false;
}

//=============================================================================
// �}�b�v�ǂݍ���
//=============================================================================
void CListMapData::LoadMap(CManager* manager, const char* filePath, const char* fileName)
{
	char c;
	int cnt;
	int type;
	D3DXVECTOR2 index;

	//----------------------------
	// �t�@�C���ǂݍ��݊J�n
	//----------------------------
	FILE* fp = fopen(filePath, "rt");

	if(fp == nullptr)
	{
		return;
	}

	//----------------------------
	// �f�[�^���擾
	//----------------------------
	fseek(fp, 0, SEEK_SET);
	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'n') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp,
					"%d %d %d %d",
					&m_numBg, &m_numRoad, &m_numStum, &m_numTarget);
		}
	}

	//----------------------------
	// �w�i�f�[�^�擾
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'b') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d", &type);

			int typeTop = TYPE_FOREST_01;

			BG_DATA data;
			data.type = (BG_TYPE)(typeTop + type);
			data.index = cnt;

			// �w�i����
			manager->CreateBg(data.index, data.type);

			cnt++;
		}
	}

	//----------------------------
	// ���f�[�^�擾
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'r') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_DIRT;

			ROAD_DATA data;
			data.type = (ROAD_TYPE)(typeTop + type);
			data.Index = index;
			manager->CreateObj(0, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// ��Q���f�[�^�擾
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 's') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_SIGNBOARD;

			STUM_DATA data;
			data.type = (STUM_TYPE)(typeTop + type);
			data.Index = index;
			manager->CreateObj(1, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// �^�[�Q�b�g�f�[�^�擾
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 't') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_TARGET_OFF;

			TARGET_DATA data;
			data.type = (TARGET_TYPE)(typeTop + (type - 1));
			data.Index = index;
			manager->CreateObj(2, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// �t�@�C�������
	//----------------------------
	fclose(fp);
}

//=============================================================================
// �}�b�v�ۑ�
//=============================================================================
void CListMapData::SaveMap(const char* filePath, const char* fileName)
{
	//----------------------------
	// �t�@�C���ǂݍ��݊J�n
	//----------------------------
	FILE* fp = fopen(filePath, "wt");

	if(fp == nullptr)
	{
		return;
	}

	//----------------------------
	// �w�b�_�[�R�����g
	//----------------------------
	fprintf(fp,"*****************************************************************************\n");
	fprintf(fp,"%s\n", fileName);
	fprintf(fp,"*****************************************************************************\n");
	fprintf(fp,"\n");

	//----------------------------
	// ��
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Num(Bg_Road_Stum_Target)\n");
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"n %d %d %d %d\n", m_numBg, m_numRoad, m_numStum, m_numTarget);
	fprintf(fp,"\n");

	//----------------------------
	// �w�i
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Background(Type)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numBg; ++cnt)
	{
		CBackground* bg = GetBg(cnt);
		if(bg != nullptr)
		{
			BG_DATA bgData = bg->GetData();
			fprintf(fp,"b %d\n", bgData.type);
		}
		else
		{
			fprintf(fp,"b 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// ��
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Road(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numRoad; ++cnt)
	{
		CRoad* road = GetRoad(cnt);
		if(road != nullptr)
		{
			ROAD_DATA roadData = road->GetData();
			fprintf(fp,"r %d %d %d\n", roadData.type, (int)roadData.Index.x, (int)roadData.Index.y);
		}
		else
		{
			fprintf(fp,"r 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// ��Q��
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Stumbler(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numStum; ++cnt)
	{
		CStumbler* stum = GetStum(cnt);
		if(stum != nullptr)
		{
			STUM_DATA stumData = stum->GetData();
			fprintf(fp,"s %d %d %d\n", stumData.type, (int)stumData.Index.x, (int)stumData.Index.y);
		}
		else
		{
			fprintf(fp,"s 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// �^�[�Q�b�g
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Target(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numTarget; ++cnt)
	{
		CTarget* target = GetTarget(cnt);
		if(target != nullptr)
		{
			TARGET_DATA targetData = target->GetData();
			fprintf(fp,"t %d %d %d\n", targetData.type + 1, (int)targetData.Index.x, (int)targetData.Index.y);
		}
		else
		{
			fprintf(fp,"t 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	//�t�@�C�������
	//----------------------------
	fclose(fp);
}
