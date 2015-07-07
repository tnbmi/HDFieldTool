//=============================================================================
//
// target_manager�N���X [target_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// �C���N���[�h�K�[�h
#ifndef __TARGET_MANAGER_H__
#define __TARGET_MANAGER_H__

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2D.h"
class CTarget;

//=============================================================================
// �N���X��`
//=============================================================================
class CTargetManager
{
public:
	CTargetManager();
	~CTargetManager(){};
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Update(void);
	void	Scroll(float f);
	CTarget*	CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	bool	CheckHitGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	static	CTargetManager* Create(LPDIRECT3DDEVICE9 device);
	// ���X�g����
	void	UnLinkTarget(CTarget* cur);
private:
	CTarget* m_list_top;		// ��Q�����X�g�擪
	CTarget* m_list_cur;		// ��Q�����X�g����
};

// �C���N���[�h�K�[�h�I��
#endif // __STUM_MANAGER_H__

// End of File