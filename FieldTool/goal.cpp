//*****************************************************************************
//
// goal�N���X [goal.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "goal.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal( int priority , OBJTYPE objtype ) : CScene2D( priority , objtype )
{
}
//=============================================================================
// ����
//=============================================================================
CGoal* CGoal::Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetGoal( pointer );
	return pointer;
}

CGoal* CGoal::Create(LPDIRECT3DDEVICE9 device, const char* texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos )
{
	CGoal* pointer = new CGoal( priority , OBJTYPE_2D );
	pointer->Init(device, texture, pointType);
	pointer->SetPos( pos );
	pointer->SetGoal( pointer );
	return pointer;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CGoal::Init( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType )
{
	CScene2D::Init( device , texture , pointType );
	return S_OK;
}

HRESULT	CGoal::Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	CScene2D::Init( device , texture , pointType );
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGoal::Uninit( void )
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CGoal::Update( void )
{
	//�����蔻��
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CGoal::Draw( void )
{
	CScene2D::Draw();
}
//=============================================================================
// �Փ˔��� (�n���ꂽ���Ǝ����̏����r����(���Y�����p)
//=============================================================================
BOOL CGoal::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// ������4���_�Ƒ����4���_���v�Z
	D3DXVECTOR2 self[4], target[4];

	// �����̒��_�����v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		self[0].x = m_pos.x;				self[0].y = m_pos.y;
		self[1].x = m_pos.x + m_size.x;		self[1].y = m_pos.y;
		self[2].x = m_pos.x + m_size.x;		self[2].y = m_pos.y + m_size.y;
		self[3].x = m_pos.x;				self[3].y = m_pos.y + m_size.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		self[0].x = m_pos.x - m_size.x/2;	self[0].y = m_pos.y - m_size.y/2;
		self[1].x = m_pos.x + m_size.x/2;	self[1].y = m_pos.y - m_size.y/2;
		self[2].x = m_pos.x + m_size.x/2;	self[2].y = m_pos.y + m_size.y/2;
		self[3].x = m_pos.x - m_size.x/2;	self[3].y = m_pos.y + m_size.y/2;
	}

	// �n���ꂽ��񂩂璸�_���v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		target[0].x = pos.x - size.x/2;		target[0].y = pos.y - size.y/2;
		target[1].x = pos.x + size.x/2;		target[1].y = pos.y - size.y/2;
		target[2].x = pos.x + size.x/2;		target[2].y = pos.y + size.y/2;
		target[3].x = pos.x - size.x/2;		target[3].y = pos.y + size.y/2;
	}

	// AABB�Փ˔���
	if( (self[0].x < target[1].x) &&
		(target[0].x < self[1].x) &&
		(self[0].y < target[3].y) &&
		(target[0].y < self[3].y) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//=============================================================================
// �X�N���[������
//=============================================================================
void CGoal::Scroll( float scroll )
{
	m_pos.x -=scroll;
	CScene2D::SetVertexPolygon();
}
