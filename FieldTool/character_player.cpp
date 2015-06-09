//*****************************************************************************
//
// �v���C���[����N���X [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_player.h"
#include "character_vehicle.h"

#include "inputKeyboard.h"
#include "math_animation.h"
#include "player_config.h"

#include "game.h"
#include "debugproc.h"
#include "fade.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(LPDIRECT3DDEVICE9 device)
{
	
	Assy=CVehicle::Create(device,CImport::ASSY_TRAM);
	Offset.x=-20.0f;
	Offset.y=0;

	//�e�̏�����
	CScene2D::Init(device,CImport::PLAYER_WAIT,POINT_CENTER);

	SetAnimMode(PLAYER_ANIM_WAIT,true);

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CPlayer::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	
	//�A�j���[�V�����̃A�b�v�f�[�g
	UpdateAnim();

	//�t�F�[�h���ł͂Ȃ��Ƃ�
	if(CPhase::GetFade()->GetState() == CFade::FADESTATE_NONE)
	{
		m_posOld = m_pos;
		
		//�ړ�����
		Move();

		//�U������
		Attack();

		//���A�N�V��������
		LightAction();
	}


	//��蕨�j��
	if(m_keyboard->GetTrigger(DIK_T))
	{
		AddHP(1);
	}

	//��蕨�C��
	if(m_keyboard->GetTrigger(DIK_U))
	{
		AddHP(-1);
	}

	//�d�͉��Z
	AddGravity();

	//�X�s�[�h���l���������W�̎Z�o
	m_pos+=m_move_spd;

	//�l�X�ȓ����蔻��
	Collider();

	//�A�b�V�[�̃|�W�V�������Z�b�g
	Assy->SetPos(m_pos.x+(int)Offset.x,m_pos.y+(int)Offset.y);
	
	//���W�̍Čv�Z
	SetVertexPolygon();
	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CPlayer::Draw(void)
{
	//�e�̕`��
	CScene2D::Draw();
}
//=============================================================================
// ����
//=============================================================================
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 device)
{
	CPlayer* scene = new CPlayer;
	scene->Init(device);

	return scene;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move()
{
	if(!isLighting)
	{
		//�E�ړ�
		if(m_keyboard->GetPress(DIK_A))
		{
			m_move_spd.x-=MOVE_SPD;
			Assy->SetAnimMode(1,true);
		}

		//���ړ�
		if(m_keyboard->GetPress(DIK_D))
		{
			m_move_spd.x+=MOVE_SPD;
			Assy->SetAnimMode(1,true);
		}
	}

	//����
	m_move_spd.x*=MOVE_FRICTIONAL_FORCE;

	if(m_keyboard->GetSetDelete(DIK_A)||m_keyboard->GetSetDelete(DIK_D))
	{
		Assy->SetAnimMode(0,true);
	}

	//�W�����v����
	moveJump();
}

//=============================================================================
// HP�X�V����
//=============================================================================
void CPlayer::AddHP(int value)
{
	HP+=value;
	//HP��0�����ɂȂ�Ȃ��悤�ɏ���
	if(HP<=0)
	{
		HP=0;
		isDeth=true;
	}

	//HP��0�����ɂȂ�Ȃ��悤�ɏ���
	if(HP>=PLAYER_HP_MAX)
	{
		HP=PLAYER_HP_MAX;
	}

	if(value<0)
	{
		if(HP<AssyDamage*AssyHP)
		{
			AssyHP--;
			Assy->addRateOfDestruction(1);
		}
	}

	if(value>0)
	{
		if(HP>AssyDamage*AssyHP)
		{
			AssyHP++;
			Assy->addRateOfDestruction(-1);
		}
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::moveJump()
{
	//�X�y�[�X�L�[���������Ƃ�
	if(m_keyboard->GetTrigger(DIK_SPACE)&&canJump&&!isLighting)
	{
		if(!isJump)
		{
			canJump=false;
			isJump=true;
			//�X�s�[�h�̐ݒ�
			m_move_spd.y=JUMP_SPD;
		}
	}
}
//=============================================================================
// �d�͉��Z����
//=============================================================================
void CPlayer::AddGravity()
{
	if(!isLighting)
	{
		m_move_spd.y+=GRAVITY_SPD;
	}

}
//=============================================================================
// �l�X�ȓ����蔻��
//=============================================================================
void CPlayer::Collider()
{
	//�n�ʂƃv���C���̓����蔻��
	if(m_pos.y>=593.0f-Offset.y)
	{
		canJump=true;
		canLighting=true;
		isJump=false;
		m_pos.y=593.0f-Offset.y;
	}

	if(m_pos.x<=0.0f)
	{
		m_pos.x=0.0f;
	}

	if(m_pos.x>=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)*2.f))
	{
		m_pos.x=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)*2.f);
	}

}
//=============================================================================
// �U������
//=============================================================================
void CPlayer::Attack()
{
	if(m_keyboard->GetTrigger(DIK_K)&&!isAttack&&!isLighting)
	{
		SetAnimMode(PLAYER_ANIM_ATACK,false);
	}
}
//=============================================================================
// ���A�N�V��������
//=============================================================================
void CPlayer::LightAction()
{
	if(m_keyboard->GetTrigger(DIK_L)&&!isAttack&&!isLighting&&canLighting)
	{
		
		canLighting=false;
		m_move_spd.y=0.0f;
		SetAnimMode(PLAYER_ANIM_LIGHT,false);
	}

	if(isHoldLighting)
	{
		if(m_keyboard->GetSetDelete(DIK_L))
		{
			isHoldLighting=false;
		}
	}
}
//=============================================================================
//�A�j���[�V�����̍X�V����
//=============================================================================
void CPlayer::UpdateAnim()
{
	switch(AnimMode)
	{
	case PLAYER_ANIM_WAIT:
		if(cntAnim==PLAYER_ANIMSPD_WAIT*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_MOVE:
		if(cntAnim==PLAYER_ANIMSPD_MOVE*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_ATACK:
		if(cntAnim==PLAYER_ANIMSPD_ATACK*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_DAMAGE:
		if(cntAnim==PLAYER_ANIMSPD_DAMAGE*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_LIGHT:
		if(cntAnim==PLAYER_ANIMSPD_LIGHT*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				
				isAnimEnd=true;
				
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;
	}

	if(isAnimEnd&&!isHoldLighting)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim(maxAnim,1,1,1,this);
		}

		else
		{
			isAttack=false;
			isLighting=false;
			SetAnimMode(PLAYER_ANIM_WAIT,true);
		}

		isAnimEnd=false;
	}
}
//=============================================================================
//�A�j���[�V�����̃Z�b�g����
//=============================================================================
void CPlayer::SetAnimMode(int AnimID,bool Rupe)
{
	if(AnimMode==AnimID)
	{
		return;
	}

	switch (AnimID)
	{
	case PLAYER_ANIM_WAIT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_WAIT;
		this->SetTex(CImport::PLAYER_WAIT);
		SetAnim(maxAnim,1,1,1,this);
		break;

	case PLAYER_ANIM_MOVE:

		break;

	case PLAYER_ANIM_ATACK:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_ATACK;
		isAttack=true;
		this->SetTex(CImport::PLAYER_ATTACK);
		SetAnim(maxAnim,1,1,1,this);
		break;

	case PLAYER_ANIM_DAMAGE:

		break;

	case PLAYER_ANIM_LIGHT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_LIGHT;
		isHoldLighting=true;
		isLighting=true;
		this->SetTex(CImport::PLAYER_LIGHT);
		SetAnim(maxAnim,1,1,1,this);
		break;
	}
	
	AnimMode=AnimID;

	isRupeAnim=Rupe;

}
