//*****************************************************************************
//
// CBackgroundクラス [background.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_BACKGROUND_H
#define _MY_BACKGROUND_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 画像データ識別
enum BG_TYPE
{
	TYPE_FOREST_01 = 0,
	TYPE_WATERSIDE_01,
	TYPE_DESERT_01,
	TYPE_DESERT_02,
	TYPE_DESERT_03,
	TYPE_GLACIER_01,
	TYPE_GLACIER_02,
	TYPE_GLACIER_03,
	TYPE_GLACIER_04,
	TYPE_GLACIER_05,
	TYPE_SAVANNAH_01,
	TYPE_SAVANNAH_02,
	TYPE_SAVANNAH_03,
	TYPE_SAVANNAH_04,
	TYPE_SAVANNAH_05,
};

// 背景情報
struct BG_DATA
{
	BG_TYPE type;
	int index;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBackground : CScene2D
{
public:
	CBackground(int priority = 1, OBJTYPE objType = OBJTYPE_2D);
	~CBackground(){};

	static CBackground* Create(LPDIRECT3DDEVICE9 device, BG_DATA data, int page = 0);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void Scroll(float scroll){SetPosX(m_pos.x - scroll);}
	void ResetNo(unsigned int no){SetPosX((float)(no * SCREEN_WIDTH));}

	void		 SetBgNext(CBackground* next){m_next = next;}
	CBackground* GetBgNext(void){return m_next;}
	void		 SetBgPrev(CBackground* prev){m_prev = prev;}
	CBackground* GetBgPrev(void){return m_prev;}

	void SetPosDef(D3DXVECTOR2 pos){m_posDef = pos;}
	void SetPosDef(float x, float y){m_posDef = D3DXVECTOR2(x, y);}

	void	SetData(BG_DATA data){m_data = data;}
	BG_DATA GetData(void){return m_data;}

private:
	BG_DATA		 m_data;
	CBackground* m_next;	// 次へのポインタ
	CBackground* m_prev;	// 前へのポインタ
};

//=============================================================================
#endif
