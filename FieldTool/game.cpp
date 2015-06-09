//*****************************************************************************
//
// CGame�N���X [game.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "game.h"
#include "manager.h"
#include "fade.h"

#include "result.h"

#include "inputKeyboard.h"

//�v���C���[���䏈��
#include "character_player.h"

// �w�i
#include "sky.h"
#include "background.h"

#include "goal.h"

#include "stumbler.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ROAD_SIZE	(64.0f)
#define ROAD_NUM	(SCREEN_WIDTH / ROAD_SIZE)
#define ROAD_POS	(SCREEN_HEIGHT - ROAD_SIZE)

#define SCREEN_HALF	(640)	// 1280 / 2

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------
// ��Q���֘A�i��ŏ����Ă�
CStumbler* g_stumbler[10];

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// �f�o�C�X�擾
	//----------------------------
	m_device = device;

	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	InitObject(device);

	//----------------------------
	// �t�F�[�h
	//----------------------------
	m_fade = CFade::Create(device);
	m_fade->Start(CFade::FADESTATE_IN, 1, 1.0f, 1.0f, 1.0f, 1.0f);

	//----------------------------
	// �o�[�W�����\��
	//----------------------------
	m_version = CScene2D::Create(device, CImport::VERSION, CScene2D::POINT_LEFTTOP);
	m_version->SetSize(206.0f, 65);
	m_version->SetPos(SCREEN_WIDTH - 206.0f, SCREEN_HEIGHT - 65.0f);

	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	//----------------------------
	// �I�u�W�F�N�g
	//----------------------------
	// ��
	SAFE_END(m_sky);

	SAFE_END(m_bg);

	// �V�[��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V
//=============================================================================
void CGame::Update(void)
{
	if(m_fade->GetState() == CFade::FADESTATE_NONE)
	{
		//----------------------------
		// �f�o�b�O�R�}���h
		//----------------------------
		Debug();

		//----------------------------
		// �X�V���e
		//----------------------------
		// ��̍X�V�i�X�N���[���j
		m_sky->Update();

		// �v���C���[�̍��W�擾
		D3DXVECTOR2 playerPos = m_player->GetPos();

		// �X�N���[������(�v���C���[����ʔ������z������)
		if(playerPos.x >= SCREEN_HALF)
		{
			float scroll = playerPos.x - SCREEN_HALF;

			// �v���C���[�͉�ʐ^�񒆂�
			m_player->SetPosX(SCREEN_HALF);

			// ��̃X�N���[��
			m_sky->Scroll(scroll * 0.01f);

			// �w�i�̃X�N���[��
			m_bg->Scroll(scroll);

			//----------------------------------------
			// ��Q���֘A�i��ŏ����Ă�
			for(int loop = 0; loop < 10; loop++)
			{
				g_stumbler[loop]->Scroll(scroll);
			}

			//�S�[���̃X�N���[��(���� 6/2_12�����ǉ�)
			m_Goal->Scroll( scroll );
		}
		else if(playerPos.x < 0)
		{
			float scroll = 0 - playerPos.x;

			// �v���C���[�͉�ʍ��[��
			m_player->SetPosX(0);

			// ��̃X�N���[��
			m_sky->Scroll(scroll * 0.01f);

			// �w�i�̃X�N���[��
			m_bg->Scroll(scroll);

			//----------------------------------------
			// ��Q���֘A�i��ŏ����Ă�
			for(int loop = 0; loop < 10; loop++)
			{
				g_stumbler[loop]->Scroll(scroll);
			}
		}

		//�����u��
		if( m_Goal->CheckCollisionAABB( m_player->GetPos() , m_player->GetSize()*0.5f , CScene2D::POINT_CENTER ) )
		{
			m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_fade->GetState() == CFade::FADESTATE_OUTEND)
	{
		CManager::SetNextPhase((CPhase*)new CResult);
	}
}

//=============================================================================
// �`��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �f�o�b�N���e
//=============================================================================
void CGame::Debug(void)
{
	//----------------------------
	// ��ʑJ��
	//----------------------------
	if(m_keyboard->GetTrigger(DIK_RETURN))
	{
		m_fade->Start(CFade::FADESTATE_OUT, 1, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// �I�u�W�F�N�g������
//=============================================================================
void CGame::InitObject(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// �w�i
	//----------------------------
	// ��
	m_sky = CSky::Create(device);

	// �w�i
	m_bg = CBackground::Create(device, CBackground::FOREST);

	//----------------------------
	// ��
	//----------------------------
	CScene2D* road;
	for(int cnt = 0; cnt < ROAD_NUM; ++cnt)
	{
		road = CScene2D::Create(device, CImport::DIRT, CScene2D::POINT_LEFTTOP);
		road->SetSize(ROAD_SIZE, ROAD_SIZE);
		road->SetPos(ROAD_SIZE * cnt, ROAD_POS);
	}

	//----------------------------
	// �L�����N�^�[
	//----------------------------
	//�v���C���[�̐���
	m_player=CPlayer::Create(device);
	m_player->SetPos(120.0f,300.0f);
	m_player->SetKeyboard(m_keyboard);


	//----------------------------------------
	// ��Q���֘A�i��ŏ����Ă�
	STUM_DATA data[] = {
		{TYPE_BARRICADE,
		D3DXVECTOR2(13,2)},
		{TYPE_ROCK,
		D3DXVECTOR2(27,5)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(40,4)},
		{TYPE_LION,
		D3DXVECTOR2(55,7)},
		{TYPE_BIRD,
		D3DXVECTOR2(67,1)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(74,3)},
		{TYPE_SIGNBOARD,
		D3DXVECTOR2(89,2)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(99,4)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(124,6)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(40,4)},
	};

	for(int loop = 0; loop < 10; loop++)
	{
		g_stumbler[loop] = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
	}

	//goal(���� 6/9_AM_10�����ύX)
	m_Goal = m_Goal->Create( device , CImport::GOAL_ON , CScene2D::POINT_CENTER , 2 , D3DXVECTOR2( 1000.0f , 500.0f ) );
}
