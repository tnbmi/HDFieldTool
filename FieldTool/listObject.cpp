//*****************************************************************************
//
// CListObjectクラス [listObject.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "listObject.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 静的変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CScene* CListObject::m_updateTop = nullptr;
CScene* CListObject::m_updateCur = nullptr;
CScene* CListObject::m_drawTop[PRIORITY_MAX] = {nullptr};
CScene* CListObject::m_drawCur[PRIORITY_MAX] = {nullptr};

//=============================================================================
// 更新
//=============================================================================
void CListObject::Update(void)
{
	CScene* cur = m_updateTop;
	CScene* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetUpdateNext();

		if(cur->GetDelete())
		{
			cur->UnLinkScene();
			delete cur;
		}

		cur = next;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CListObject::Draw(void)
{
	CScene* cur;

	for(int cnt = 0; cnt < PRIORITY_MAX; ++cnt)
	{
		cur = m_drawTop[cnt];

		while(cur)
		{
			cur->Draw();

			cur = cur->GetDrawNext();
		}
	}
}

//=============================================================================
// リスト追加
//=============================================================================
void CListObject::LinkObj(CScene* obj, int priority)
{
	// 更新リスト
	LinkUpdate(obj);

	// 描画リスト
	LinkDraw(obj, priority);
}

//=============================================================================
// リストから破棄
//=============================================================================
void CListObject::UnlinkObj(CScene* obj)
{
	// 更新リスト
	UnlinkUpdate(obj);

	// 描画リスト
	UnlinkDraw(obj);
}

//=============================================================================
// 更新リスト追加
//=============================================================================
void CListObject::LinkUpdate(CScene* obj)
{
	// 先頭チェック
	if(m_updateTop == nullptr)
	{
		m_updateTop = obj;
		obj->SetUpdatePrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_updateCur->SetUpdateNext(obj);
		obj->SetUpdatePrev(m_updateCur);
	}

	// 次オブジェクト初期化
	obj->SetUpdateNext(nullptr);
	// 終端アドレス設定
	m_updateCur = obj;
}

//=============================================================================
// 更新リストから破棄
//=============================================================================
void CListObject::UnlinkUpdate(CScene* obj)
{
	CScene* prev = obj->GetUpdatePrev();
	CScene* next = obj->GetUpdateNext();

	if(prev != nullptr)
	{
		prev->SetUpdateNext(next);
	}
	else // Topだった場合
	{
		m_updateTop = next;

		if(m_updateTop != nullptr)
		{
			m_updateTop->SetUpdatePrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetUpdatePrev(prev);
	}
	else // Curだった場合
	{
		m_updateCur = prev;

		if(m_updateTop != nullptr)
		{
			m_updateCur->SetUpdateNext(nullptr);
		}
	}
}

//=============================================================================
// 描画リスト追加
//=============================================================================
void CListObject::LinkDraw(CScene* obj, int priority)
{
	// 先頭チェック
	if(m_drawTop[priority] == nullptr)
	{
		m_drawTop[priority] = obj;
		obj->SetDrawPrev(nullptr);
	}
	else
	{
		// 前オブジェクトから連結
		m_drawCur[priority]->SetDrawNext(obj);
		obj->SetDrawPrev(m_drawCur[priority]);
	}

	// 次オブジェクト初期化
	obj->SetDrawNext(nullptr);
	// 終端アドレス設定
	m_drawCur[priority] = obj;
}

//=============================================================================
// 描画リストから破棄
//=============================================================================
void CListObject::UnlinkDraw(CScene* obj)
{
	CScene* prev = obj->GetDrawPrev();
	CScene* next = obj->GetDrawNext();
	int priority = obj->GetPriority();

	if(prev != nullptr)
	{
		prev->SetDrawNext(next);
	}
	else // Topだった場合
	{
		m_drawTop[priority] = next;

		if(m_drawTop[priority] != nullptr)
		{
			m_drawTop[priority]->SetDrawPrev(nullptr);
		}
	}

	if(next != nullptr)
	{
		next->SetDrawPrev(prev);
	}
	else // Curだった場合
	{
		m_drawCur[priority] = prev;

		if(m_drawTop[priority] != nullptr)
		{
			m_drawCur[priority]->SetDrawNext(nullptr);
		}
	}
}
