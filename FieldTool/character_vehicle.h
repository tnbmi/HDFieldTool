//=============================================================================
//
// ��蕨����N���X [character_vehicle.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_VEHICLE_H
#define _CHARACTER_VEHICLE_H
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// �}�N��
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CVehicle : public CScene2D
{
public:
	//�R���X�g���N�^
	//������:�v���C�I���e�B(�ő��PRIORITY_MAX�A�������͂��Ȃ���PRIORITY_MAX - 2�ɐݒ�)
	//������:�I�u�W�F�N�g�^�C�v(�������͂��Ȃ���OBJTYPE_NONE�ɐݒ�)
	CVehicle(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//�f�X�g���N�^
	~CVehicle(){};

	//�N���G�C�g
	//������:�f�o�C�X
	//������:�e�N�X�`�����
	//�߂�l  :�C���X�^���X�̃|�C���^
	static CVehicle* Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//����������
	//������:�f�o�C�X
	//������:�e�N�X�`�����
	//�߂�l  :�����������ǂ�����HRESULT�^�ŕԂ�
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//�I������
	void	Uninit(void);

	//�X�V����
	void	Update(void);

	//�`�揈��
	void	Draw(void);

	//��蕨�̉���擾(�傫���Ȃ�ɂ�ĉ��Ă���)
	//�߂�l:��蕨�̔j��
	int RateOfDestruction_()
	{
		return (RateOfDestruction);
	}
	
	//��蕨�̔j�󗦉��Z
	//������:���Z�������l(���Z�������ꍇ��-�̒l�����Ă�������)
	void addRateOfDestruction(int value);
	//�A�j���[�V�����̃Z�b�g����
	void SetAnimMode(int animID,bool Rupe);
	//�`���ON,OFF�؂�ւ�
	//������:�`�悷�邩���Ȃ���
	void SetisDraw(bool value)
	{
		isDraw=value;
	}

private:
	//���݂̃A�j���[�V�������[�h
	int AnimMode;
	//�A�j���[�V�����̃��[�v�t���O
	bool isRupeAnim;
	//�A�j���[�V������1���I���t���O
	bool isAnimEnd;
	//�`��t���O
	bool isDraw;

	//���݂̃A�j���[�V�����ԍ�
	int nowAnim;
	//�A�j���[�V�����̃J�E���g�p
	int cntAnim;
	//�A�j���[�V�����̍ő�R�}��
	D3DXVECTOR2 maxAnim;
	//�j��
	int RateOfDestruction;

	//�ϐ���NULL���ߏ���
	void NullSetVariable(void)
	{
		RateOfDestruction=1;
		isDraw=true;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=99;
		cntAnim=0;
		nowAnim=1;
		maxAnim.x=1;
		maxAnim.y=1;
	}

	//�A�j���[�V�����̍X�V����
	void UpdateAnim();
};

#endif

