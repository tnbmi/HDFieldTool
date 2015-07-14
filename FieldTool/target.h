//*****************************************************************************
//
// target�N���X [target.h]
// Author : KEN MATSUURA
//
//*****************************************************************************

#ifndef _TARGET_H
#define _TARGET_H
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
	TYPE_TARGET_OFF,
	TYPE_GOAL_OFF,
	TYPE_GOAL_ON,
	TYPE_GOAL_CLEAR
}TARGET_TYPE;

// �^�[�Q�b�g���
typedef struct{
	TARGET_TYPE type;
	D3DXVECTOR2 Index;
}TARGET_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CTarget : public CScene2D
{
public:
	CTarget(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CTarget(){};

	static	CTarget* Create(LPDIRECT3DDEVICE9 device, TARGET_DATA data, POINT_TYPE pointType, int page = 0);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// �X�N���[������
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}

	// ���^�[�Q�b�g�|�C���^�Z�b�g����
	void		SetTargetNext(CTarget* next){m_next = next;}
	// ���^�[�Q�b�g�|�C���^�Q�b�g����
	CTarget*	GetTargetNext(void){return m_next;}
	// �O�^�[�Q�b�g�|�C���^�Z�b�g����
	void		SetTargetPrev(CTarget* prev){m_prev = prev;}
	// �O�^�[�Q�b�g�|�C���^�Q�b�g����
	CTarget*	GetTargetPrev(void){return m_prev;}

	bool		GetTargetFrag(void){return m_targetFlag;}
	void		SetTargetFrag(void){m_targetFlag = true;}

	void SetPosDef(D3DXVECTOR2 pos){m_posDef = pos;}
	void SetPosDef(float x, float y){m_posDef = D3DXVECTOR2(x, y);}

	void		SetData(TARGET_DATA data){m_data = data;}
	TARGET_DATA GetData(void){return m_data;}

protected:
	TARGET_DATA	m_data;
	CTarget* m_next;						// ���^�[�Q�b�g�ւ̃|�C���^
	CTarget* m_prev;						// �O�^�[�Q�b�g�ւ̃|�C���^
	bool m_targetFlag;
};

//=============================================================================
#endif