//*****************************************************************************
//
// targetクラス [target.h]
// Author : KEN MATSUURA
//
//*****************************************************************************

#ifndef _TARGET_H
#define _TARGET_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 画像データ識別
typedef enum{
	TYPE_TARGET_OFF,
	TYPE_GOAL_OFF,
	TYPE_GOAL_ON,
	TYPE_GOAL_CLEAR
}TARGET_TYPE;

// ターゲット情報
typedef struct{
	TARGET_TYPE type;
	D3DXVECTOR2 Index;
}TARGET_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
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

	// スクロール処理
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}

	// 次ターゲットポインタセット処理
	void		SetTargetNext(CTarget* next){m_next = next;}
	// 次ターゲットポインタゲット処理
	CTarget*	GetTargetNext(void){return m_next;}
	// 前ターゲットポインタセット処理
	void		SetTargetPrev(CTarget* prev){m_prev = prev;}
	// 前ターゲットポインタゲット処理
	CTarget*	GetTargetPrev(void){return m_prev;}

	bool		GetTargetFrag(void){return m_targetFlag;}
	void		SetTargetFrag(void){m_targetFlag = true;}

	void SetPosDef(D3DXVECTOR2 pos){m_posDef = pos;}
	void SetPosDef(float x, float y){m_posDef = D3DXVECTOR2(x, y);}

	void		SetData(TARGET_DATA data){m_data = data;}
	TARGET_DATA GetData(void){return m_data;}

protected:
	TARGET_DATA	m_data;
	CTarget* m_next;						// 次ターゲットへのポインタ
	CTarget* m_prev;						// 前ターゲットへのポインタ
	bool m_targetFlag;
};

//=============================================================================
#endif