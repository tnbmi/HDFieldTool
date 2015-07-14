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

class CManager;

class CListMapData
{
public:
	CListMapData();
	~CListMapData(){};

	// 背景
	static void			LinkBg(unsigned int no, CBackground* obj);
	static void			UnlinkBg(CBackground* obj);
	static void			DelBg(unsigned int no);
	static CBackground* GetBg(unsigned int no);

	// 道
	static void	  LinkRoad(CRoad* obj);
	static void	  UnlinkRoad(CRoad* obj);
	static void	  DelRoad(CRoad* obj);
	static CRoad* GetRoad(unsigned int no);

	// 障害物
	static void		  LinkStum(CStumbler* obj);
	static void		  UnlinkStum(CStumbler* obj);
	static void		  DelStum(CStumbler* obj);
	static CStumbler* GetStum(unsigned int no);

	// ターゲット
	static void		LinkTarget(CTarget* obj);
	static void		UnlinkTarget(CTarget* obj);
	static void		DelTarget(CTarget* obj);
	static CTarget* GetTarget(unsigned int no);

	// 全体スクロール
	static void Scroll(float scroll);

	// グリッドオブジェクト探索
	static int GridChk(int x, int y, CScene2D** obj);

	// ファイル処理
	static void LoadMap(CManager* manager, const char* filePath, const char* fileName);
	static void SaveMap(const char* filePath, const char* fileName);

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