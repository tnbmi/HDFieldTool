//*****************************************************************************
//
// メイン処理 [main.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_MAIN_H
#define _MY_MAIN_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// メモリーリークチェック準備
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#include <stdlib.h>
#include <crtdbg.h>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) // 警告対策用
#include <dinput.h>
#include "XInput.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// メモリーリークチェック
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ライブラリのリンク
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "XInput.lib")

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// 画面サイズ
//----------------------------
#define MAG				(0.5f)	// 拡大倍率
#define SCREEN_WIDTH	(1280 * MAG)	// ウインドウの幅
#define SCREEN_HEIGHT	(720 * MAG)		// ウインドウの高さ
#define GRID_SIZE		(64 * MAG)		// グリッドのサイズ

//----------------------------
// 分岐マクロ
//----------------------------
#define HRESULT_FUNC(func)	if(FAILED(func)){return E_FAIL;}	// 関数のHRESULTリターン
#define HRESULT_POINTER(p)	if(p==nullptr){return E_FAIL;}			// nullptrのHRESULTリターン

#define SAFE_RELEASE(p)		 if(p!=nullptr){p->Release(); p=nullptr;}			// 開放保護
#define SAFE_DELETE(p)		 if(p!=nullptr){delete p; p=nullptr;}				// 破棄保護
#define SAFE_DELETE_ARRAY(p) if(p!=nullptr){delete[] p; p=nullptr;}				// 配列破棄保護
#define SAFE_UNINIT(p)		 if(p!=nullptr){p->Uninit(); p=nullptr;}			// 終了保護
#define SAFE_END(p)			 if(p!=nullptr){p->Uninit(); delete p; p=nullptr;}	// 最終保護

//----------------------------
// その他共通マクロ
//----------------------------
#define DISTANCE_2D(x,y)	sqrt(x*x + y*y)			// 2次元距離計算
#define SIGN_F(n)			((n) / fabs(n))			// 符号取得(float)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// フォーマット
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
//----------------------------
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//----------------------------
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
//----------------------------
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float		rhw;		// テクスチャのパースペクティブコレクト用
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

//=============================================================================

#endif