//*****************************************************************************
//
// CCreateクラス [game.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "create.h"
#include "manager.h"

#include "inputKeyboard.h"

#include "scene2D.h"

// マップデータ
#include "listMapData.h"

// 背景
#include "sky.h"
#include "background.h"

// オブジェクト
#include "road.h"
#include "stumbler.h"
#include "target.h"

#include "manager.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCreate::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------
	// デバイス取得
	//----------------------------
	m_device = device;

	//----------------------------
	// オブジェクト
	//----------------------------
	m_page = 0;

	InitObject(device);

	//----------------------------
	// 初期化成功
	//----------------------------
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CCreate::Uninit(void)
{
	//----------------------------
	// オブジェクト
	//----------------------------

	// シーン
	CScene::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CCreate::Update(void)
{
	//----------------------------
	// デバッグコマンド
	//----------------------------
	Debug();

	//----------------------------
	// 更新内容
	//----------------------------
}

//=============================================================================
// 描画
//=============================================================================
void CCreate::Draw(void)
{
}

//=============================================================================
// デバック内容
//=============================================================================
void CCreate::Debug(void)
{
}

//=============================================================================
// オブジェクト初期化
//=============================================================================
void CCreate::InitObject(LPDIRECT3DDEVICE9 device)
{
	// 空
	CSky* sky = CSky::Create(device);

	// グリッド
	CScene2D* grid = CScene2D::Create(device, CImport::GRID, CScene2D::POINT_LEFTTOP, PRIORITY_MAX-1);
	grid->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//=============================================================================
// 背景生成
//=============================================================================
void CCreate::CreateBg(int no, int type)
{
	// 背景生成
	BG_DATA data = {(BG_TYPE)(TYPE_FOREST_01 + type), no};
	CBackground* bg = CBackground::Create(m_device, data, m_page);

	// マップデータに追加
	CListMapData::LinkBg(no, bg);
}

//=============================================================================
// 背景削除
//=============================================================================
void CCreate::DeleteBg(int no)
{
	// マップデータを削除
	CListMapData::DelBg(no);
}

//=============================================================================
// オブジェクト生成
//=============================================================================
void CCreate::CreateObj(int category, int type, int x, int y)
{
	switch(category)
	{
		// 道
		case 0:
		{
			// 道生成
			ROAD_DATA data = {(ROAD_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CRoad* road = CRoad::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// 重なった道を削除
			CRoad** roadChk = new CRoad*;
			if(CListMapData::GridChkRoad(data.Index.x, data.Index.y, roadChk))
			{
				CListMapData::DelRoad(*roadChk);
			}

			// 重なったターゲットを削除
			CTarget** targetChk = new CTarget*;
			if(CListMapData::GridChkTarget(data.Index.x, data.Index.y, targetChk))
			{
				CListMapData::DelTarget(*targetChk);
			}

			// マップデータに追加
			CListMapData::LinkRoad(road);
			break;
		}

		// 障害物
		case 1:
		{
			// 障害物生成
			STUM_DATA data = {(STUM_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CStumbler* stum = CStumbler::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// 重なった障害物を削除
			CStumbler** stumChk = new CStumbler*;
			if(CListMapData::GridChkStum(data.Index.x, data.Index.y, stumChk))
			{
				CListMapData::DelStum(*stumChk);
			}

			// 重なったターゲットを削除
			CTarget** targetChk = new CTarget*;
			if(CListMapData::GridChkTarget(data.Index.x, data.Index.y, targetChk))
			{
				CListMapData::DelTarget(*targetChk);
			}

			// マップデータに追加
			CListMapData::LinkStum(stum);
			break;
		}

		// ターゲット
		case 2:
		{
			// ターゲット生成
			TARGET_DATA data = {(TARGET_TYPE)type, D3DXVECTOR2((float)x + (m_page * 20), (float)y)};
			CTarget* target = CTarget::Create(m_device, data, CScene2D::POINT_LEFTTOP, m_page);

			// 重なったオブジェクトを削除
			DeleteObj(data.Index.x, data.Index.y);

			// マップデータに追加
			CListMapData::LinkTarget(target);
			break;
		}

		default:
		{
			break;
		}
	}
}

//=============================================================================
// オブジェクト削除
//=============================================================================
void CCreate::DeleteObj(int x, int y)
{
	CScene2D** obj = new CScene2D*;
	int category = CListMapData::GridChk(x + (m_page * 20), y, obj);

	switch(category)
	{
		// 道
		case 0:
		{
			// マップデータを削除
			CListMapData::DelRoad((CRoad*)*obj);
			break;
		}

		// 障害物
		case 1:
		{
			// マップデータを削除
			CListMapData::DelStum((CStumbler*)*obj);
			break;
		}

		// ターゲット
		case 2:
		{
			// マップデータを削除
			CListMapData::DelTarget((CTarget*)*obj);
			break;
		}

		default:
		{
			break;
		}
	}
}

//=============================================================================
// スクロール
//=============================================================================
void CCreate::Scroll(float scroll)
{
	// ページ更新
	if(scroll < 0)
	{
		// 戻る
		m_page--;

		// 戻れない時
		if(m_page < 0)
		{
			m_page = 0;
			return;
		}
	}
	else
	{
		// 進む
		m_page++;
	}

	// スクロール更新
	CListMapData::Scroll(scroll);
}

//=============================================================================
// マップ読み込み
//=============================================================================
void CCreate::LoadMap(CManager* manager, const char* filePath, const char* fileName)
{
	CListMapData::LoadMap(manager, filePath, fileName);
}

//=============================================================================
// マップセーブ
//=============================================================================
void CCreate::SaveMap(const char* filePath, const char* fileName)
{
	CListMapData::SaveMap(filePath, fileName);
}
