//*****************************************************************************
//
// CCreateクラス [game.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_GAME_H
#define _MY_GAME_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer;
class CSky;
class CBackground;
class CScene2D;
class CGoal;

class CManager;

class CCreate : CPhase
{
public:
	CCreate(void){};
	~CCreate(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void CreateBg(int no, int type);
	void DeleteBg(int no);

	void CreateObj(int category, int type, int x, int y);
	void DeleteObj(int x, int y);

	// スクロール
	void Scroll(float scroll);

	// ページ
	int GetPage(void){return m_page;}

	// ファイル処理
	void LoadMap(CManager* manager, const char* filePath, const char* fileName);
	void SaveMap(const char* filePath, const char* fileName);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);
	void Debug(void);

	// ページ数
	int m_page;

	//プレイヤー制御
	CPlayer *m_player;

	// 背景
	CSky*		 m_sky;
	CBackground* m_bg;

	CScene2D* m_version;

	// ゴール(大井川 6/2_12時頃追加)
	CGoal *m_Goal;
};

//=============================================================================
#endif
