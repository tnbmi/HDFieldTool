//*****************************************************************************
//
// �A�j���[�V�����֘A�̌v�Z [math_animation.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "math_animation.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�ő�l�A�ŏ��l���l���������ݒl�̎Z�o����
static float MapValues(float x,float inMin,float inMax,float outMin,float outMax);

//=============================================================================
// �|���S���Ɏw�肵���R�}��\��t���鏈��(�c�������ꂽ���̂ɂ͔�Ή�)
//=============================================================================
void SetAnim(int maxTex_X,int nowTex_X,int maxTex_Y,int nowTex_Y,CScene2D* pol)
{
	
	D3DXVECTOR2 uvOffset;
	uvOffset.x=MapValues(1.0f,0,(float)maxTex_X,0,1.0f);
	uvOffset.y=MapValues(1.0f,0,(float)maxTex_Y,0,1.0f);

	D3DXVECTOR2 cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X-1),uvOffset.y*(float)(nowTex_Y-1));
	pol->SetCord(0,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X),uvOffset.y*(float)(nowTex_Y-1));
	pol->SetCord(1,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X-1),uvOffset.y*(float)(nowTex_Y));
	pol->SetCord(2,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X),uvOffset.y*(float)(nowTex_Y));
	pol->SetCord(3,cord);

}
//=============================================================================
// �ő�l�A�ŏ��l���l���������ݒl�̎Z�o
//=============================================================================
float MapValues(float x,float inMin,float inMax,float outMin,float outMax)
{
	return ((x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin);
}