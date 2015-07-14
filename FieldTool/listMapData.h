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

class CListMapData
{
public:
	CListMapData();
	~CListMapData(){};

	// �w�i
	static void			LinkBg(unsigned int no, CBackground* obj);
	static void			UnlinkBg(CBackground* obj);
	static CBackground* GetBg(unsigned int no);
	static void			DelBg(unsigned int no);

	// ��
	static void	  LinkRoad(unsigned int no, CRoad* obj);
	static void	  UnlinkRoad(CRoad* obj);
	static CRoad* GetRoad(unsigned int no);
	static void	  DelRoad(unsigned int no);

	// ��Q��
	static void		  LinkStum(unsigned int no, CStumbler* obj);
	static void		  UnlinkStum(CStumbler* obj);
	static CStumbler* GetStum(unsigned int no);
	static void		  DelStum(unsigned int no);

	// �^�[�Q�b�g
	static void		LinkTarget(unsigned int no, CTarget* obj);
	static void		UnlinkTarget(CTarget* obj);
	static CTarget* GetTarget(unsigned int no);
	static void		DelTarget(unsigned int no);

	// �S�̃X�N���[��
	static void Scroll(float scroll);

private:
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