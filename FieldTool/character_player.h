//=============================================================================
//
// �v���C���[����N���X [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_PLAYER_H
#define _CHARACTER_PLAYER_H
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// �}�N��
//============================================================================
//�v���C����HP�̍ő�l(3�̔{�����D�܂���)
const int PLAYER_HP_MAX                 = 3;

//=============================================================================
// �O���錾
//=============================================================================
//�L�[�{�[�h���͐���N���X
class CInputKeyboard;
//��蕨����N���X
class CVehicle;
//=============================================================================
// �N���X��`
//=============================================================================
class CPlayer : public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CPlayer(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CPlayer(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CPlayer* Create(LPDIRECT3DDEVICE9 device);

	//����������
	//������:�f�o�C�X
	//�߂�l  :�����������ǂ�����HRESULT�^�ŕԂ�
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	//�I������
	void	Uninit(void);

	//�X�V����
	void	Update(void);

	//�`�揈��
	void	Draw(void);

	//�L�[�{�[�h���̃Z�b�g
	void SetKeyboard(CInputKeyboard* keyboard){m_keyboard = keyboard;}

	//�ړ����x�̎擾����
	//�߂�l:�v���C���[�̈ړ���
	D3DXVECTOR2 move_spd_()
	{
		return (m_move_spd);
	}

	//HP�̎擾����
	//�߂�l:�v���C���[��HP
	int HP_()
	{
		return (HP);
	}

	bool isDeth_()
	{
		return (isDeth);
	}

	//HP�̉��Z����
	//������:���Z����l(���Z�������ꍇ��-�̒l�����Ă�������)
	void AddHP(int value);

private:

	//Y�l�I�t�Z�b�g
	D3DXVECTOR2 Offset;

	//�v���C���[��HP
	int HP;
	//�r�[�N���_���[�W�l
	int AssyDamage;
	//�r�[�N���̑ϋv(1�`3)
	int AssyHP;

	//�L�[�{�[�h���i�[�ϐ�
	CInputKeyboard*	m_keyboard;
	//�v���C���[�̈ړ����x
	D3DXVECTOR2 m_move_spd;

	//�W�����v�����ǂ���
	bool isJump;
	//�W�����v�\���ǂ���
	bool canJump;
	//�U�������ǂ���
	bool isAttack;
	//���A�N�V���������ǂ���
	bool isLighting;
	//���A�N�V�������p�����邩�ǂ���
	bool isHoldLighting;
	//���A�N�V�������\���ǂ���
	bool canLighting;

	bool isDeth;

	//���݂̃A�j���[�V�������[�h
	int AnimMode;
	//�A�j���[�V�����̃��[�v�t���O
	bool isRupeAnim;
	//�A�j���[�V������1���I���t���O
	bool isAnimEnd;

	//���݂̃A�j���[�V�����ԍ�
	int nowAnim;
	//�A�j���[�V�����̃J�E���g�p
	int cntAnim;
	//�A�j���[�V�����̍ő�R�}��
	int maxAnim;

	CVehicle* Assy;

	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		Offset.x=0;
		Offset.y=0;

		HP=PLAYER_HP_MAX;
		AssyDamage=HP/3;
		AssyHP=3;
		isDeth=false;
		maxAnim=1;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=-1;
		m_keyboard=NULL;
		Assy=NULL;
		cntAnim=0;
		nowAnim=1;
		m_move_spd=D3DXVECTOR2(0.0f,0.0f);
		isJump=false;
		isAttack=false;
		isLighting=false;
		isHoldLighting=false;
		canJump=true;
		canLighting=true;
	}

	//�ړ�����
	void Move();
	//�U������
	void Attack();
	//�W�����v����
	void moveJump();
	//���A�N�V��������
	void LightAction();
	//�d�͂�������
	void AddGravity();
	//�l�X�ȓ����蔻��
	void Collider();
	//�A�j���[�V�����̍X�V����
	void UpdateAnim();
	//�A�j���[�V�����̃Z�b�g����
	void SetAnimMode(int animID,bool Rupe);
	//HP�̍X�V
	void HPUpdate();

};

#endif

