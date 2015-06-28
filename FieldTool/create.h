//*****************************************************************************
//
// CCreate�N���X [game.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_GAME_H
#define _MY_GAME_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CPlayer;
class CSky;
class CBackground;
class CScene2D;
class CGoal;

class CCreate : CPhase
{
public:
	CCreate(void){};
	~CCreate(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void CreateObject(int no, int category, int type, int x, int y);

private:
	void InitObject(LPDIRECT3DDEVICE9 device);
	void Debug(void);

	//�v���C���[����
	CPlayer *m_player;

	// �w�i
	CSky*		 m_sky;
	CBackground* m_bg;

	CScene2D* m_version;

	// �S�[��(���� 6/2_12�����ǉ�)
	CGoal *m_Goal;
};

//=============================================================================
#endif
