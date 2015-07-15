//*****************************************************************************
//
// CListMapData�N���X [listMapData.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_LIST_OBJECT_H
#define _MY_LIST_OBJECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "background.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
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

	// �w�i
	static void			LinkBg(unsigned int no, CBackground* obj);
	static void			UnlinkBg(CBackground* obj);
	static void			DelBg(unsigned int no);
	static CBackground* GetBg(unsigned int no);

	// ��
	static void	  LinkRoad(CRoad* obj);
	static void	  UnlinkRoad(CRoad* obj);
	static void	  DelRoad(CRoad* obj);
	static CRoad* GetRoad(unsigned int no);

	// ��Q��
	static void		  LinkStum(CStumbler* obj);
	static void		  UnlinkStum(CStumbler* obj);
	static void		  DelStum(CStumbler* obj);
	static CStumbler* GetStum(unsigned int no);

	// �^�[�Q�b�g
	static void		LinkTarget(CTarget* obj);
	static void		UnlinkTarget(CTarget* obj);
	static void		DelTarget(CTarget* obj);
	static CTarget* GetTarget(unsigned int no);

	// �S�̃X�N���[��
	static void Scroll(float scroll);

	// �O���b�h�I�u�W�F�N�g�T��
	static int	GridChk(int x, int y, CScene2D** obj);
	static bool	GridChkRoad(int x, int y, CRoad** obj);
	static bool	GridChkStum(int x, int y, CStumbler** obj);
	static bool	GridChkTarget(int x, int y, CTarget** obj);

	// �t�@�C������
	static void LoadMap(CManager* manager, const char* filePath, const char* fileName);
	static void SaveMap(const char* filePath, const char* fileName);

private:
	// �}�b�v�f�[�^�폜
	static void ReleaseAll(void);

	// �w�i
	static CBackground* m_topBg;	// �擪�|�C���^
	static CBackground* m_curBg;	// ���ݏI�[�|�C���^
	static unsigned int m_numBg;	// ��

	// ��
	static CRoad*		m_topRoad;	// �擪�|�C���^
	static CRoad*		m_curRoad;	// ���ݏI�[�|�C���^
	static unsigned int m_numRoad;	// ��

	// ��Q��
	static CStumbler*	m_topStum;	// �擪�|�C���^
	static CStumbler*	m_curStum;	// ���ݏI�[�|�C���^
	static unsigned int m_numStum;	// ��

	// �^�[�Q�b�g
	static CTarget*		m_topTarget;	// �擪�|�C���^
	static CTarget*		m_curTarget;	// ���ݏI�[�|�C���^
	static unsigned int m_numTarget;	// ��
};

//=============================================================================
#endif