//*****************************************************************************
//
// CMapData�N���X [mapData.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "mapData.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapData::CMapData(void)
{
	m_bgSize	 = 0;
	m_roadSize	 = 0;
	m_stumSize	 = 0;
	m_targetSize = 0;

	m_bgData	 = nullptr;
	m_roadData	 = nullptr;
	m_stumData	 = nullptr;
	m_targetData = nullptr;
}

//=============================================================================
// ����
//=============================================================================
CMapData* CMapData::Create(const char* file)
{
	CMapData* pointer = new CMapData;
	if(FAILED(pointer->Init(file)))
	{
		MessageBox(NULL, "�}�b�v�f�[�^�t�@�C��������܂���", "MapData", MB_OK);
	}
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CMapData::Init(const char* file)
{
	char c;
	int cnt;
	int cate;
	int type;
	D3DXVECTOR2 index;

	//----------------------------
	// �t�@�C���ǂݍ��݊J�n
	//----------------------------
	FILE* fp = fopen(file, "rt");

	if(fp == nullptr)
	{
		return E_FAIL;
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
					&m_bgSize, &m_roadSize, &m_stumSize, &m_targetSize);
		}
	}

	//----------------------------
	// �f�[�^�������m��
	//----------------------------
	m_bgData	 = new BG_DATA[m_bgSize];
	m_roadData	 = new ROAD_DATA[m_roadSize];
	m_stumData	 = new STUM_DATA[m_stumSize];
	m_targetData = new TARGET_DATA[m_targetSize];

	//----------------------------
	// �w�i�f�[�^�擾
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'b') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %d", &cate, &type);

			int typeTop = 0;
			switch(cate)
			{
			case 0:
				typeTop = TYPE_FOREST_01;
				break;

			case 1:
				typeTop = TYPE_TWON_01;
				break;

			default:
				break;
			}

			m_bgData[cnt].type = (BG_TYPE)(typeTop + type);
			m_bgData[cnt].index = cnt;

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

			m_roadData[cnt].type = (ROAD_TYPE)(typeTop + type);
			m_roadData[cnt].Index = index;

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

			m_stumData[cnt].type = (STUM_TYPE)(typeTop + type);
			m_stumData[cnt].Index = index;

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

			m_targetData[cnt].type = (TARGET_TYPE)(typeTop + type);
			m_targetData[cnt].Index = index;

			cnt++;
		}
	}

	//----------------------------
	// �t�@�C���ǂݍ��ݏI��
	//----------------------------
	// �ǂݍ��݃t�@�C��
	fclose(fp);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CMapData::Uninit(void)
{
	SAFE_DELETE_ARRAY(m_bgData);
	SAFE_DELETE_ARRAY(m_roadData);
	SAFE_DELETE_ARRAY(m_stumData);
	SAFE_DELETE_ARRAY(m_targetData);
}
