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

#include "manager.h"

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
		DelBg(no);
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
// 道リスト追加
//=============================================================================
void CListMapData::LinkRoad(CRoad* obj)
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
// 道リストの任意の物を削除
//=============================================================================
void CListMapData::DelRoad(CRoad* obj)
{
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
		MessageBox(nullptr, "そのオブジェクトは存在しません。", "存在しないオブジェクト", MB_OK);
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
// 障害物リスト追加
//=============================================================================
void CListMapData::LinkStum(CStumbler* obj)
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
// 障害物リストの任意の物を削除
//=============================================================================
void CListMapData::DelStum(CStumbler* obj)
{
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
		MessageBox(nullptr, "そのオブジェクトは存在しません。", "存在しないオブジェクト", MB_OK);
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
// ターゲットリスト追加
//=============================================================================
void CListMapData::LinkTarget(CTarget* obj)
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
// ターゲットリストの任意の物を削除
//=============================================================================
void CListMapData::DelTarget(CTarget* obj)
{
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
		MessageBox(nullptr, "そのオブジェクトは存在しません。", "存在しないオブジェクト", MB_OK);
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

//=============================================================================
// グリッドオブジェクト探索
//=============================================================================
int CListMapData::GridChk(int x, int y, CScene2D** obj)
{
	// 道探索
	CRoad*	  road = nullptr;
	ROAD_DATA roadData;
	for(unsigned int cnt = 0; cnt < m_numRoad; ++cnt)
	{
		road	 = GetRoad(cnt);
		roadData = road->GetData();

		// グリッドが等しい
		if(roadData.Index.x == x && roadData.Index.y == y)
		{
			*obj = road;
			return 0;
		}
	}

	// 障害物探索
	CStumbler*	stum = nullptr;
	STUM_DATA	stumData;
	for(unsigned int cnt = 0; cnt < m_numStum; ++cnt)
	{
		stum	 = GetStum(cnt);
		stumData = stum->GetData();

		// グリッドが等しい
		if(stumData.Index.x == x && stumData.Index.y == y)
		{
			*obj = stum;
			return 1;
		}
	}

	// ターゲット探索
	CTarget*	target = nullptr;
	TARGET_DATA	targetData;
	for(unsigned int cnt = 0; cnt < m_numTarget; ++cnt)
	{
		target	 = GetTarget(cnt);
		targetData = target->GetData();

		// グリッドが等しい
		if(targetData.Index.x == x && targetData.Index.y == y)
		{
			*obj = target;
			return 2;
		}
	}

	return -1;
}

//=============================================================================
// マップ読み込み
//=============================================================================
void CListMapData::LoadMap(CManager* manager, const char* filePath, const char* fileName)
{
	char c;
	int cnt;
	int cate;
	int type;
	D3DXVECTOR2 index;

	//----------------------------
	// ファイル読み込み開始
	//----------------------------
	FILE* fp = fopen(filePath, "rt");

	if(fp == nullptr)
	{
		return;
	}

	//----------------------------
	// データ数取得
	//----------------------------
	fseek(fp, 0, SEEK_SET);
	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'n') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp,
					"%d %d %d %d",
					&m_numBg, &m_numRoad, &m_numStum, &m_numTarget);
		}
	}

	//----------------------------
	// 背景データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'b') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d", &type);

			int typeTop = TYPE_FOREST_01;

			BG_DATA data;
			data.type = (BG_TYPE)(typeTop + type);
			data.index = cnt;

			// 背景生成
			manager->CreateBg(data.index, data.type);

			cnt++;
		}
	}

	//----------------------------
	// 道データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'r') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_DIRT;

			ROAD_DATA data;
			data.type = (ROAD_TYPE)(typeTop + type);
			data.Index = index;
			manager->CreateObj(0, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// 障害物データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 's') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_SIGNBOARD;

			STUM_DATA data;
			data.type = (STUM_TYPE)(typeTop + type);
			data.Index = index;
			manager->CreateObj(1, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// ターゲットデータ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 't') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_TARGET_OFF;

			TARGET_DATA data;
			data.type = (TARGET_TYPE)(typeTop + (type - 1));
			data.Index = index;
			manager->CreateObj(2, data.type, data.Index.x, data.Index.y);

			cnt++;
		}
	}

	//----------------------------
	// ファイルを閉じる
	//----------------------------
	fclose(fp);
}

//=============================================================================
// マップ保存
//=============================================================================
void CListMapData::SaveMap(const char* filePath, const char* fileName)
{
	//----------------------------
	// ファイル読み込み開始
	//----------------------------
	FILE* fp = fopen(filePath, "wt");

	if(fp == nullptr)
	{
		return;
	}

	//----------------------------
	// ヘッダーコメント
	//----------------------------
	fprintf(fp,"*****************************************************************************\n");
	fprintf(fp,"%s\n", fileName);
	fprintf(fp,"*****************************************************************************\n");
	fprintf(fp,"\n");

	//----------------------------
	// 個数
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Num(Bg_Road_Stum_Target)\n");
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"n %d %d %d %d\n", m_numBg, m_numRoad, m_numStum, m_numTarget);
	fprintf(fp,"\n");

	//----------------------------
	// 背景
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Background(Type)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numBg; ++cnt)
	{
		CBackground* bg = GetBg(cnt);
		if(bg != nullptr)
		{
			BG_DATA bgData = bg->GetData();
			fprintf(fp,"b %d\n", bgData.type);
		}
		else
		{
			fprintf(fp,"b 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// 道
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Road(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numRoad; ++cnt)
	{
		CRoad* road = GetRoad(cnt);
		if(road != nullptr)
		{
			ROAD_DATA roadData = road->GetData();
			fprintf(fp,"r %d %d %d\n", roadData.type, (int)roadData.Index.x, (int)roadData.Index.y);
		}
		else
		{
			fprintf(fp,"r 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// 障害物
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Stumbler(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numStum; ++cnt)
	{
		CStumbler* stum = GetStum(cnt);
		if(stum != nullptr)
		{
			STUM_DATA stumData = stum->GetData();
			fprintf(fp,"s %d %d %d\n", stumData.type, (int)stumData.Index.x, (int)stumData.Index.y);
		}
		else
		{
			fprintf(fp,"s 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	// ターゲット
	//----------------------------
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"Target(Type_Index.X_Index.Y)\n");
	fprintf(fp,"=============================================================================\n");
	for(unsigned int cnt = 0; cnt < m_numTarget; ++cnt)
	{
		CTarget* target = GetTarget(cnt);
		if(target != nullptr)
		{
			TARGET_DATA targetData = target->GetData();
			fprintf(fp,"t %d %d %d\n", targetData.type + 1, (int)targetData.Index.x, (int)targetData.Index.y);
		}
		else
		{
			fprintf(fp,"t 0 0 0\n");
		}
	}
	fprintf(fp,"\n");

	//----------------------------
	//ファイルを閉じる
	//----------------------------
	fclose(fp);
}
