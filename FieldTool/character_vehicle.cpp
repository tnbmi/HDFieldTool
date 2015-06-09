//*****************************************************************************
//
// ��蕨����N���X [character_vehicle.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_vehicle.h"
#include "vehicle_config.h"

#include "character_player.h"
#include "math_animation.h"

#include "game.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVehicle::CVehicle(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CVehicle::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	//�e�̏�����
	CScene2D::Init(device,texture,POINT_CENTER);

	//�A�j���[�V�����̏�����
	SetAnimMode(VEHICLE_ANIM_WAIT,true);

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CVehicle::Uninit(void)
{
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CVehicle::Update(void)
{
	//�A�j���[�V�����̍X�V
	UpdateAnim();

	//���W�̍Čv�Z
	SetVertexPolygon();
	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CVehicle::Draw(void)
{
	if(isDraw)
	{
		//�e�̕`��
		CScene2D::Draw();
	}
}
//=============================================================================
// ����
//=============================================================================
CVehicle* CVehicle::Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture)
{
	CVehicle* scene = new CVehicle;
	scene->Init(device,texture);

	return scene;
}

//=============================================================================
//�A�j���[�V�����̍X�V����
//=============================================================================
void CVehicle::UpdateAnim()
{
	switch(AnimMode)
	{
	case VEHICLE_ANIM_WAIT:
	
		break;

	case VEHICLE_ANIM_MOVE:
	if(cntAnim==VEHICLE_ANIMSPD_MOVE*nowAnim)
	{
		if(nowAnim==maxAnim.x)
		{
			isAnimEnd=true;
		}

		else
		{
			nowAnim++;
			SetAnim((int)maxAnim.x,nowAnim,(int)maxAnim.y,RateOfDestruction,this);
		}
	}
	cntAnim++;
		break;
	}

	if(isAnimEnd)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
		}

		else
		{
			SetAnimMode(VEHICLE_ANIM_WAIT,true);
		}

		isAnimEnd=false;
	}
}
//=============================================================================
//�A�j���[�V�����̃Z�b�g����
//=============================================================================
void CVehicle::SetAnimMode(int AnimID,bool Rupe)
{
	if(AnimMode==AnimID)
	{
		return;
	}

	switch (AnimID)
	{
	case VEHICLE_ANIM_WAIT:
		cntAnim=0;
		nowAnim=1;
		maxAnim.x=VEHICLE_MAXANIM_X_WAIT;
		maxAnim.y=VEHICLE_MAXANIM_Y_WAIT;
		SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
		break;

	case VEHICLE_ANIM_MOVE:
		cntAnim=0;
		nowAnim=1;
		maxAnim.x=VEHICLE_MAXANIM_X_MOVE;
		maxAnim.y=VEHICLE_MAXANIM_Y_MOVE;
		SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
		break;
	}

	AnimMode=AnimID;
	isRupeAnim=Rupe;
}

//=============================================================================
//��蕨�̔j�󗦉��Z
//=============================================================================
void CVehicle::addRateOfDestruction(int value)
{
	RateOfDestruction+=value;
	//1�ȉ��ɂȂ�̂�h��
	if(RateOfDestruction<=1)
	{
		RateOfDestruction=1;
	}
	//�R�}�ő吔�ȏ�ɂȂ�̂�h��
	if(RateOfDestruction>=maxAnim.y)
	{
		RateOfDestruction=(int)maxAnim.y;
	}

	SetAnim((int)maxAnim.x,1,(int)maxAnim.y,RateOfDestruction,this);
}