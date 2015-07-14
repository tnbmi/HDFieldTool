//*****************************************************************************
//
// CListMapDataクラス [listMapData.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "listMapData.h"

#include "background.h"
#include "road.h"
#include "stumbler.h"
#include "target.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 背景
CBackground* CListMapData::m_topBg = nullptr;
CBackground* CListMapData::m_curBg = nullptr;
unsigned int CListMapData::m_numBg = 0;

// 道
CRoad*		 CListMapData::m_topRoad = nullptr;
CRoad*		 CListMapData::m_curRoad = nullptr;
unsigned int CListMapData::m_numRoad = 0;

// 障害物
CStumbler*	 CListMapData::m_topStum = nullptr;
CStumbler*	 CListMapData::m_curStum = nullptr;
unsigned int CListMapData::m_numStum = 0;

// ターゲット
CTarget*	 CListMapData::m_topTarget = nullptr;
CTarget*	 CListMapData::m_curTarget = nullptr;
unsigned int CListMapData::m_numTarget = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CListMapData::CListMapData()
{
	// 背景
	m_topBg = nullptr;
	m_curBg = nullptr;
	m_numBg = 0;

	// 道
	m_topRoad = nullptr;
	m_curRoad = nullptr;
	m_numRoad = 0;

	// 障害物
	m_topStum = nullptr;
	m_curStum = nullptr;
	m_numStum = 0;

	// ターゲット
	m_topTarget = nullptr;
	m_curTarget = nullptr;
	m_numTarget = 0;
}

//=============================================================================
// 背景リスト追加
//=============================================================================
void CListMapData::LinkBg(unsigned int no, CBackground* obj)
{
	//----------------------------
	// 既存チェック
	//----------------------------
	CBackground* objChk = GetBg(no);
	if(objChk != nullptr)
	{
		// 既にあったら削除
		UnlinkBg(obj);

		// 全体カウント
		m_numBg--;
	}

	//----------------------------
	// 新規追加
	//----------------------------
	// 先頭チェック
	if(m_topBg == nullptr)
	{
		m_topBg = obj;
		obj->SetBgPrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_curBg->SetBgNext(obj);
		obj->SetBgPrev(m_curBg);
	}

	// 次オブジェクト初期化
	obj->SetBgNext(nullptr);
	// 終端アドレス設定
	m_curBg = obj;

	// 全体カウント
	m_numBg++;
}

//=============================================================================
// 背景リストから破棄
//=============================================================================
void CListMapData::UnlinkBg(CBackground* obj)
{
	CBackground* prev = obj->GetBgPrev();
	CBackground* next = obj->GetBgNext();

	if(prev != nullptr)
	{
		prev->SetBgNext(next);
	}
	else // Topだった場合
	{
		m_topBg = next;

		if(m_topBg != nullptr)
		{
			m_topBg->SetBgPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetBgPrev(prev);
	}
	else // Curだった場合
	{
		m_curBg = prev;

		if(m_curBg != nullptr)
		{
			m_curBg->SetBgNext(nullptr);
		}
	}
}

//=============================================================================
// 背景リストから任意の物を取得
//=============================================================================
CBackground* CListMapData::GetBg(unsigned int no)
{
	CBackground* obj = m_topBg;

	// 任意の数まで進む
	for(unsigned int cnt = 0; cnt < m_numBg; ++cnt)
	{
		if(obj->GetData().index == no)
		{
			return obj;
		}

		obj = obj->GetBgNext();
	}

	return nullptr;
}

//=============================================================================
// 背景リストの任意の物を削除
//=============================================================================
void CListMapData::DelBg(unsigned int no)
{
	CBackground* obj = GetBg(no);

	if(obj != nullptr)
	{
		// リストから破棄
		UnlinkBg(obj);

		// シーンを削除
		obj->Uninit();

		// 全体カウント
		m_numBg--;
	}
	else
	{
		MessageBox(nullptr, "その番号は存在しません。", "存在しないオブジェクト", MB_OK);
	}
}

//=============================================================================
// 道リスト追加
//=============================================================================
void CListMapData::LinkRoad(unsigned int no, CRoad* obj)
{
	// 先頭チェック
	if(m_topRoad == nullptr)
	{
		m_topRoad = obj;
		obj->SetRoadPrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_curRoad->SetRoadNext(obj);
		obj->SetRoadPrev(m_curRoad);
	}

	// 次オブジェクト初期化
	obj->SetRoadNext(nullptr);
	// 終端アドレス設定
	m_curRoad = obj;

	// 全体カウント
	m_numRoad++;
}

//=============================================================================
// 道リストから破棄
//=============================================================================
void CListMapData::UnlinkRoad(CRoad* obj)
{
	CRoad* prev = obj->GetRoadPrev();
	CRoad* next = obj->GetRoadNext();

	if(prev != nullptr)
	{
		prev->SetRoadNext(next);
	}
	else // Topだった場合
	{
		m_topRoad = next;

		if(m_topRoad != nullptr)
		{
			m_topRoad->SetRoadPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetRoadPrev(prev);
	}
	else // Curだった場合
	{
		m_curRoad = prev;

		if(m_curRoad != nullptr)
		{
			m_curRoad->SetRoadNext(nullptr);
		}
	}
}

//=============================================================================
// 道リストから任意の物を取得
//=============================================================================
CRoad* CListMapData::GetRoad(unsigned int no)
{
	CRoad* obj = m_topRoad;

	// 任意の数まで進む
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetRoadNext();
	}

	return obj;
}

//=============================================================================
// 道リストの任意の物を削除
//=============================================================================
void CListMapData::DelRoad(unsigned int no)
{
	CRoad* obj = GetRoad(no);

	if(obj != nullptr)
	{
		// リストから破棄
		UnlinkRoad(obj);

		// シーンを削除
		obj->Uninit();

		// 全体カウント
		m_numRoad--;
	}
	else
	{
		MessageBox(nullptr, "その番号は存在しません。", "存在しないオブジェクト", MB_OK);
	}
}

//=============================================================================
// 障害物リスト追加
//=============================================================================
void CListMapData::LinkStum(unsigned int no, CStumbler* obj)
{
	// 先頭チェック
	if(m_topStum == nullptr)
	{
		m_topStum = obj;
		obj->SetStumPrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_curStum->SetStumNext(obj);
		obj->SetStumPrev(m_curStum);
	}

	// 次オブジェクト初期化
	obj->SetStumNext(nullptr);
	// 終端アドレス設定
	m_curStum = obj;

	// 全体カウント
	m_numStum++;
}

//=============================================================================
// 障害物リストから破棄
//=============================================================================
void CListMapData::UnlinkStum(CStumbler* obj)
{
	CStumbler* prev = obj->GetStumPrev();
	CStumbler* next = obj->GetStumNext();

	if(prev != nullptr)
	{
		prev->SetStumNext(next);
	}
	else // Topだった場合
	{
		m_topStum = next;

		if(m_topStum != nullptr)
		{
			m_topStum->SetStumPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetStumPrev(prev);
	}
	else // Curだった場合
	{
		m_curStum = prev;

		if(m_curStum != nullptr)
		{
			m_curStum->SetStumNext(nullptr);
		}
	}
}

//=============================================================================
// 障害物リストから任意の物を取得
//=============================================================================
CStumbler* CListMapData::GetStum(unsigned int no)
{
	CStumbler* obj = m_topStum;

	// 任意の数まで進む
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetStumNext();
	}

	return obj;
}

//=============================================================================
// 障害物リストの任意の物を削除
//=============================================================================
void CListMapData::DelStum(unsigned int no)
{
	CStumbler* obj = GetStum(no);

	if(obj != nullptr)
	{
		// リストから破棄
		UnlinkStum(obj);

		// シーンを削除
		obj->Uninit();

		// 全体カウント
		m_numStum--;
	}
	else
	{
		MessageBox(nullptr, "その番号は存在しません。", "存在しないオブジェクト", MB_OK);
	}
}

//=============================================================================
// ターゲットリスト追加
//=============================================================================
void CListMapData::LinkTarget(unsigned int no, CTarget* obj)
{
	// 先頭チェック
	if(m_topTarget == nullptr)
	{
		m_topTarget = obj;
		obj->SetTargetPrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_curTarget->SetTargetNext(obj);
		obj->SetTargetPrev(m_curTarget);
	}

	// 次オブジェクト初期化
	obj->SetTargetNext(nullptr);
	// 終端アドレス設定
	m_curTarget = obj;

	// 全体カウント
	m_numTarget++;
}

//=============================================================================
// ターゲットリストから破棄
//=============================================================================
void CListMapData::UnlinkTarget(CTarget* obj)
{
	CTarget* prev = obj->GetTargetPrev();
	CTarget* next = obj->GetTargetNext();

	if(prev != nullptr)
	{
		prev->SetTargetNext(next);
	}
	else // Topだった場合
	{
		m_topTarget = next;

		if(m_topTarget != nullptr)
		{
			m_topTarget->SetTargetPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetTargetPrev(prev);
	}
	else // Curだった場合
	{
		m_curTarget = prev;

		if(m_curTarget != nullptr)
		{
			m_curTarget->SetTargetNext(nullptr);
		}
	}
}

//=============================================================================
// ターゲットリストから任意の物を取得
//=============================================================================
CTarget* CListMapData::GetTarget(unsigned int no)
{
	CTarget* obj = m_topTarget;

	// 任意の数まで進む
	for(unsigned int cnt = 0; cnt < no; ++cnt)
	{
		obj = obj->GetTargetNext();
	}

	return obj;
}

//=============================================================================
// ターゲットリストの任意の物を削除
//=============================================================================
void CListMapData::DelTarget(unsigned int no)
{
	CTarget* obj = GetTarget(no);

	if(obj != nullptr)
	{
		// リストから破棄
		UnlinkTarget(obj);

		// シーンを削除
		obj->Uninit();

		// 全体カウント
		m_numTarget--;
	}
	else
	{
		MessageBox(nullptr, "その番号は存在しません。", "存在しないオブジェクト", MB_OK);
	}
}

//=============================================================================
// スクロール
//=============================================================================
void CListMapData::Scroll(float scroll)
{
	// 背景
	CBackground* bg = m_topBg;
	while(bg)
	{
		bg->Scroll(scroll);
		bg = bg->GetBgNext();
	}

	// 道
	CRoad* road = m_topRoad;
	while(road)
	{
		road->Scroll(scroll);
		road = road->GetRoadNext();
	}

	// 障害物
	CStumbler* stum = m_topStum;
	while(stum)
	{
		stum->Scroll(scroll);
		stum = stum->GetStumNext();
	}

	// ターゲット
	CTarget* target = m_topTarget;
	while(target)
	{
		target->Scroll(scroll);
		target = target->GetTargetNext();
	}
}
