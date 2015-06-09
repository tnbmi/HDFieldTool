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
	TYPE_MAX
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

	static	CStumbler* Create(LPDIRECT3DDEVICE9 device, STUM_DATA data, POINT_TYPE pointType);

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
	// �Փ˔���
	bool	CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pType);

protected:
	int		m_life;							// ��Q���ϋv�x
};

//=============================================================================
#endif