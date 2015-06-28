//=============================================================================
//
// road_manager�N���X [road_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// �C���N���[�h�K�[�h
#ifndef __ROAD_MANAGER_H__
#define __ROAD_MANAGER_H__

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene2D.h"
class CRoad;

//=============================================================================
// �N���X��`
//=============================================================================
class CRoadManager
{
public:
	CRoadManager();
	~CRoadManager(){};
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Update(void);
	void	Scroll(float f);
	bool	CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	static	CRoadManager* Create(LPDIRECT3DDEVICE9 device);
private:
	CRoad* m_list_top;		// ��Q�����X�g�擪
	CRoad* m_list_cur;		// ��Q�����X�g����
};

// �C���N���[�h�K�[�h�I��
#endif // __ROAD_MANAGER_H__
// End of File