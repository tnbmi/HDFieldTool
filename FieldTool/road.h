//=============================================================================
//
// Roadクラス [road.h]
// Author : Ken Matsuura
//
//=============================================================================

// インクルードガード
#ifndef __ROAD_H__
#define __ROAD_H__

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 画像データ識別
typedef enum{
	TYPE_DIRT = 0,
	TYPE_SAND,
	TYPE_ICE,
	TYPE_GRASSFIELD,
	TYPE_WATER,
	TYPE_MAX,
}ROAD_TYPE;

// 地面情報
typedef struct{
	ROAD_TYPE type;
	D3DXVECTOR2 Index;
}ROAD_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
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

	// 押し返し処理
	D3DXVECTOR2	ReturnPush(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType);

	// スクロール処理
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}

	// 次道路ポインタセット処理
	void	SetRoadNext(CRoad* next){m_next = next;}
	// 次道路ポインタゲット処理
	CRoad*	GetRoadNext(void){return m_next;}
	// 前道路ポインタセット処理
	void	SetRoadPrev(CRoad* prev){m_prev = prev;}
	// 前道路ポインタゲット処理
	CRoad*	GetRoadPrev(void){return m_prev;}

	void	  SetData(ROAD_DATA data){m_data = data;}
	ROAD_DATA GetData(void){return m_data;}

private:
	ROAD_DATA	m_data;
	CRoad*		m_next;	// 次道へのポインタ
	CRoad*		m_prev;	// 前道へのポインタ
};


// インクルードガード終了
#endif // __ROAD_H__

// End of File