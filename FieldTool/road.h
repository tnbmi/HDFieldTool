//=============================================================================
//
// Road�N���X [road.h]
// Author : Ken Matsuura
//
//=============================================================================

// �C���N���[�h�K�[�h
#ifndef __ROAD_H__
#define __ROAD_H__

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �摜�f�[�^����
typedef enum{
	TYPE_DIRT = 0,
	TYPE_SAND,
	TYPE_ICE,
	TYPE_GRASSFIELD,
	TYPE_WATER,
	TYPE_MAX,
}ROAD_TYPE;

// �n�ʏ��
typedef struct{
	ROAD_TYPE type;
	D3DXVECTOR2 Index;
}ROAD_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CRoad : public CScene2D
{
public:
	CRoad(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CRoad(){};

	static	CRoad* Create(LPDIRECT3DDEVICE9 device, ROAD_DATA data, POINT_TYPE pointType, int page = 0);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// �����Ԃ�����
	D3DXVECTOR2	ReturnPush(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType);

	// �X�N���[������
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}

	// �����H�|�C���^�Z�b�g����
	void	SetRoadNext(CRoad* next){m_next = next;}
	// �����H�|�C���^�Q�b�g����
	CRoad*	GetRoadNext(void){return m_next;}
	// �O���H�|�C���^�Z�b�g����
	void	SetRoadPrev(CRoad* prev){m_prev = prev;}
	// �O���H�|�C���^�Q�b�g����
	CRoad*	GetRoadPrev(void){return m_prev;}
	// �f�t�H���g�ʒu�Z�b�g����
	void SetPosDef(D3DXVECTOR2 pos){m_posDef = pos;}
	void SetPosDef(float x, float y){m_posDef = D3DXVECTOR2(x, y);}

	void	  SetData(ROAD_DATA data){m_data = data;}
	ROAD_DATA GetData(void){return m_data;}

private:
	ROAD_DATA	m_data;
	CRoad*		m_next;	// �����ւ̃|�C���^
	CRoad*		m_prev;	// �O���ւ̃|�C���^
};


// �C���N���[�h�K�[�h�I��
#endif // __ROAD_H__

// End of File