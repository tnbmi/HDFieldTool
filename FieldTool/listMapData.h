//*****************************************************************************
//
// CListMapDataクラス [listMapData.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_LIST_OBJECT_H
#define _MY_LIST_OBJECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "background.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CBackground;
class CRoad;
class CStumbler;
class CTarget;

class CListMapData
{
public:
	CListMapData();
	~CListMapData(){};

	// 背景
	static void			LinkBg(unsigned int no, CBackground* obj);
	static void			UnlinkBg(CBackground* obj);
	static CBackground* GetBg(unsigned int no);
	static void			DelBg(unsigned int no);

	// 道
	static void	  LinkRoad(unsigned int no, CRoad* obj);
	static void	  UnlinkRoad(CRoad* obj);
	static CRoad* GetRoad(unsigned int no);
	static void	  DelRoad(unsigned int no);

	// 障害物
	static void		  LinkStum(unsigned int no, CStumbler* obj);
	static void		  UnlinkStum(CStumbler* obj);
	static CStumbler* GetStum(unsigned int no);
	static void		  DelStum(unsigned int no);

	// ターゲット
	static void		LinkTarget(unsigned int no, CTarget* obj);
	static void		UnlinkTarget(CTarget* obj);
	static CTarget* GetTarget(unsigned int no);
	static void		DelTarget(unsigned int no);

private:
	// 背景
	static CBackground* m_topBg;	// 先頭ポインタ
	static CBackground* m_curBg;	// 現在終端ポインタ
	static unsigned int m_numBg;	// 個数

	// 道
	static CRoad*		m_topRoad;	// 先頭ポインタ
	static CRoad*		m_curRoad;	// 現在終端ポインタ
	static unsigned int m_numRoad;	// 個数

	// 障害物
	static CStumbler*	m_topStum;	// 先頭ポインタ
	static CStumbler*	m_curStum;	// 現在終端ポインタ
	static unsigned int m_numStum;	// 個数

	// ターゲット
	static CTarget*		m_topTarget;	// 先頭ポインタ
	static CTarget*		m_curTarget;	// 現在終端ポインタ
	static unsigned int m_numTarget;	// 個数
};

//=============================================================================
#endif