//*****************************************************************************
//
// CScene2D�N���X [scene2D.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define POLIGON_SIZE (128.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int priority, OBJTYPE objType) : CScene(priority, objType)
{
	m_localTex	= false;
	m_texture	= NULL;
	m_vtxBuff	= NULL;

	m_rot	= 0.0f;
	m_pos	= D3DXVECTOR2(0.0f, 0.0f);
	m_size	= D3DXVECTOR2(POLIGON_SIZE, POLIGON_SIZE);
	m_color	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR2 half = D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);
	m_length = DISTANCE_2D(half.x, half.y);
	m_angle	 = atan2f(half.x, half.y);

	m_coord[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_coord[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_coord[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_coord[3] = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// ����
//=============================================================================
CScene2D* CScene2D::Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType, int priority)
{
	CScene2D* pointer = new CScene2D(priority);
	pointer->Init(device, texture, pointType);
	return pointer;
}

CScene2D* CScene2D::Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	CScene2D* pointer = new CScene2D;
	pointer->Init(device, texture, pointType);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CScene2D::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
{
	//----------------------------
	// �f�o�C�X�擾
	//----------------------------
	m_device = device;

	//----------------------------
	// �|�C���g�̃^�C�v�擾
	//----------------------------
	m_pointType = pointType;

	//----------------------------
	// �|���S��������
	//----------------------------
	// �������m��
	HRESULT_FUNC(m_device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
											  D3DUSAGE_WRITEONLY,
											  FVF_VERTEX_2D,
											  D3DPOOL_MANAGED,
											  &m_vtxBuff,
											  NULL))

	// ���_���ݒ�
	SetVertexPolygon();

	// �e�N�X�`���擾
	m_texture = CImport::GetTexture(texture);
	m_localTex = false;

	// �����蔻��T�C�Y
	m_hitSize = m_size;

	// �����蔻��p���W
	m_hitPos = m_pos;

	// �����蔻����W�I�t�Z�b�g
	m_hitOffset = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

HRESULT CScene2D::Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType)
{
	//----------------------------
	// �f�o�C�X�擾
	//----------------------------
	m_device = device;

	//----------------------------
	// �|�C���g�̃^�C�v�擾
	//----------------------------
	m_pointType = pointType;

	//----------------------------
	// �|���S��������
	//----------------------------
	// �������m��
	HRESULT_FUNC(m_device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
											  D3DUSAGE_WRITEONLY,
											  FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
											  D3DPOOL_MANAGED,
											  &m_vtxBuff,				// ���_���
											  NULL))

	// ���_���ݒ�
	SetVertexPolygon();

	// �e�N�X�`���擾
	D3DXCreateTextureFromFile(device, texture, &m_texture);
	m_localTex = true;
	
	//----------------------------
	// ����������
	//----------------------------
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CScene2D::Uninit(void)
{
	if(m_localTex)
	{
		SAFE_RELEASE(m_texture);
	}

	// ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_vtxBuff);

	// �J��
	CScene::Delete();
}

//=============================================================================
// �X�V
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �`��
//=============================================================================
void CScene2D::Draw(void)
{
	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	m_device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_device->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	m_device->SetTexture(0, m_texture);

	//�`��ݒ�
	m_device->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�`����
							0,						//
							2);						//�|���S���̐�
}

//=============================================================================
// ���_���ݒ�
//=============================================================================
void CScene2D::SetVertexPolygon(void)
{
	VERTEX_2D* vtx;
	D3DXVECTOR2	work[4];

	// ���W�ݒ�
	switch(m_pointType)
	{
	case POINT_LEFTTOP:
		{
			// �e���_�̍��W�v�Z
			work[0].x = m_pos.x;
			work[0].y = m_pos.y;
			work[1].x = m_pos.x + m_size.x;
			work[1].y = m_pos.y;
			work[2].x = m_pos.x;
			work[2].y = m_pos.y + m_size.y;
			work[3].x = m_pos.x + m_size.x;
			work[3].y = m_pos.y + m_size.y;
			break;
		}

	case POINT_CENTER:
		{
			// ���_�����E�p�x�X�V
			D3DXVECTOR2 half = D3DXVECTOR2(m_size.x / 2.0f, m_size.y / 2.0f);
			m_length = DISTANCE_2D(half.x, half.y);
			m_angle	 = atan2f(half.x, half.y);

			// �e���_�̍��W�v�Z
			work[0].x = m_pos.x - sinf(m_angle - m_rot) * m_length;
			work[0].y = m_pos.y - cosf(m_angle - m_rot) * m_length;
			work[1].x = m_pos.x + sinf(m_angle + m_rot) * m_length;
			work[1].y = m_pos.y - cosf(m_angle + m_rot) * m_length;
			work[2].x = m_pos.x - sinf(m_angle + m_rot) * m_length;
			work[2].y = m_pos.y + cosf(m_angle + m_rot) * m_length;
			work[3].x = m_pos.x + sinf(m_angle - m_rot) * m_length;
			work[3].y = m_pos.y + cosf(m_angle - m_rot) * m_length;
			break;
		}
	}

	// �J�n
	m_vtxBuff->Lock(0, 0, (void **)&vtx, 0);

	// ���W
	vtx[0].vtx = D3DXVECTOR3(work[0].x, work[0].y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(work[1].x, work[1].y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(work[2].x, work[2].y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(work[3].x, work[3].y, 0.0f);

	// 1.0f�Œ�
	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	// ���ˌ�
	vtx[0].diffuse = m_color;
	vtx[1].diffuse = m_color;
	vtx[2].diffuse = m_color;
	vtx[3].diffuse = m_color;

	// �e�N�X�`�����W
	vtx[0].tex = D3DXVECTOR2(m_coord[0].x, m_coord[0].y);
	vtx[1].tex = D3DXVECTOR2(m_coord[1].x, m_coord[1].y);
	vtx[2].tex = D3DXVECTOR2(m_coord[2].x, m_coord[2].y);
	vtx[3].tex = D3DXVECTOR2(m_coord[3].x, m_coord[3].y);

	// �I��
	m_vtxBuff->Unlock();
}

//=============================================================================
// �Փ˔��� (�n���ꂽ���Ǝ����̏����r����
//=============================================================================
bool CScene2D::CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// ������4���_�Ƒ����4���_���v�Z
	D3DXVECTOR2 self[4], target[4], temp;

	temp = (m_size - m_hitSize)/2;

	// �����̒��_�����v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
	}

	// �n���ꂽ��񂩂璸�_���v�Z
	if(pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(pointType == POINT_CENTER)	// ���S���_�̏ꍇ
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
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// �����蔻��{�b�N�X�̕`��
//=============================================================================
void CScene2D::DrawHitBox(void)
{
	// �����̒��_�����v�Z
	D3DXVECTOR2 self[4], temp;

	temp = (m_size - m_hitSize)/2;

	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
	}

	// ���_���W
	m_hitBox[0].vtx = D3DXVECTOR3(self[0].x, self[0].y, 0);
	m_hitBox[1].vtx = D3DXVECTOR3(self[1].x, self[1].y, 0);
	m_hitBox[2].vtx = D3DXVECTOR3(self[3].x, self[3].y, 0);
	m_hitBox[3].vtx = D3DXVECTOR3(self[2].x, self[2].y, 0);

	// �e�N�X�`�����W
	m_hitBox[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_hitBox[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_hitBox[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_hitBox[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �F���
	for(int cnt = 0; cnt < 4; cnt++)
	{
		m_hitBox[cnt].diffuse	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f);
		m_hitBox[cnt].rhw		= 1.0f;
	}

	//���_�t�H�[�}�b�g�̐ݒ�
	m_device->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	m_device->SetTexture(0, NULL);

	//�`��ݒ�
	m_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
								2,
								m_hitBox,
								sizeof(VERTEX_2D));
}