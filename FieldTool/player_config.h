//=============================================================================
//
// �v���C���[�̊e��ݒ��� [player_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PLAYER_CONFIG_H
#define _PLAYER_CONFIG_H
//=============================================================================
// �ݒ���
//=============================================================================



//�W�����v��
const float JUMP_SPD                    = -40.0f;
//�ړ��X�s�[�h
const float MOVE_SPD                    = 3.0f;
//�d��
const float GRAVITY_SPD                 = 2.0f;

const int PLAYER_MAXANIM_WAIT           = 4;
const int PLAYER_MAXANIM_MOVE           = 1;
const int PLAYER_MAXANIM_ATACK          = 5;
const int PLAYER_MAXANIM_DAMAGE         = 10;
const int PLAYER_MAXANIM_LIGHT          = 10;

//�A�j���[�V�����X�s�[�h
const int   PLAYER_ANIMSPD_WAIT         = 10;
const int   PLAYER_ANIMSPD_MOVE         = 10;
const int   PLAYER_ANIMSPD_ATACK        = 10;
const int   PLAYER_ANIMSPD_DAMAGE       = 10;
const int   PLAYER_ANIMSPD_LIGHT        = 7;

//�ړ����̖��C��
const float MOVE_FRICTIONAL_FORCE       = 0.8f;

const int   PLAYER_ANIM_WAIT            = 0;
const int   PLAYER_ANIM_MOVE            = 1;
const int   PLAYER_ANIM_ATACK           = 2;
const int   PLAYER_ANIM_DAMAGE          = 3;
const int   PLAYER_ANIM_LIGHT           = 4;


//��蕨���Ƃ̍����I�t�Z�b�g
const float PLAYER_HEGHIT_OFFSET_MARUTA = 25.0f;


#endif

