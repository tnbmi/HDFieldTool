//*****************************************************************************
//
// stumbler�N���X [stumbler.h]
// Author : KEN MATSUURA
//
//*****************************************************************************

#ifndef _STUMBLER_H
#define _STUMBLER_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �摜�f�[�^����
typedef enum{
	TYPE_SIGNBOARD = 0,
	TYPE_LION,
	TYPE_ROCK,
	TYPE_LOG_LEFT,
	TYPE_LOG_CENTER,
	TYPE_LOG_RIGHT,
	TYPE_BIRD,
	TYPE_DUSTBOX,
	TYPE_BARRICADE,
	TYPE_CUCTUS,
	TYPE_ICEBERG,
	TYPE_ICICLE,
	TYPE_NUTS,
	TYPE_NUTS_REVERSE,
	TYPE_SANDSTONE,
	TYPE_BEE,
	TYPE_HUNEYCOMB,
}STUM_TYPE;

// ��Q�����
typedef struct{
	STUM_TYPE type;
	D3DXVECTOR2 Index;
}STUM_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CStumbler : public CScene2D
{
public:
	CStumbler(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CStumbler(){};

	static	CStumbler* Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType, int page = 0);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// �X�N���[������
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}
	// HP�Z�b�g����
	void	SetHP(int life){m_life = life;}
	// HP�Q�b�g����
	int		GetHP(void){return m_life;}
	// �U�����󂯂��ꍇ��HP���Z����
	void	Attack(int damage){m_life -= damage;}
	// �����`�F�b�N
	bool	LivingCheck(void);
	// ����Q���|�C���^�Z�b�g����
	void		SetStumNext(CStumbler* next){m_next = next;}
	// ����Q���|�C���^�Q�b�g����
	CStumbler*	GetStumNext(void){return m_next;}
	// �O��Q���|�C���^�Z�b�g����
	void		SetStumPrev(CStumbler* prev){m_prev = prev;}
	// �O��Q���|�C���^�Q�b�g����
	CStumbler*	GetStumPrev(void){return m_prev;}
	// ��Q���^�C�v�Z�b�g����
	void		SetStumType(STUM_TYPE type){m_type = type;}
	// �f�t�H���g�ʒu�Z�b�g����
	void		SetDefPos(D3DXVECTOR2 pos){m_defpos = pos;}
	// �����t���O
	void		SetFall(void){m_fallFrag = true;}
	// �����`�F�b�N
	void		CheckFall(D3DXVECTOR2 pos);
	// ��Q���폜�t���O�I��
	void		SetStumDelete(void){m_stumDelete = true;}
	// ��Q���폜�t���O��Ԏ擾
	bool		GetStumDelete(void){return m_stumDelete;}
	// �ړ��l�Z�b�g
	void		SetStumMove(D3DXVECTOR2 v){m_move = v;}

	void SetPosDef(D3DXVECTOR2 pos){m_posDef = pos;}
	void SetPosDef(float x, float y){m_posDef = D3DXVECTOR2(x, y);}

	void	  SetData(STUM_DATA data){m_data = data;}
	STUM_DATA GetData(void){return m_data;}

protected:
	STUM_DATA	m_data;
	int			m_life;						// ��Q���ϋv�x
	CStumbler*	m_next;						// ����Q���ւ̃|�C���^
	CStumbler*	m_prev;						// �O��Q���ւ̃|�C���^
	STUM_TYPE	m_type;						// ��Q���^�C�v
	D3DXVECTOR2	m_move;						// �ړ��l
	D3DXVECTOR2	m_defpos;					// �����ʒu
	int			m_texAnim;					// �e�N�X�`���A�j���[�V�����p�^�C�}
	bool		m_fallFrag;					// �����t���O
	bool		m_stumDelete;				// ��Q���폜�t���O��
};

//=============================================================================
#endif