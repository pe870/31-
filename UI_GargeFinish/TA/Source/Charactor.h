#ifndef CHARACTOR_H
#define CHARACTOR_H

#include "DX9Mesh.h"
#include "DebugText.h"
#include "Global.h"


//�L�����N���X.
class clsChara
{
public:
	clsChara();
	virtual ~clsChara();

	//�g�����]�ȂǍ��W�̒l�����f���f�[�^�ɔ��f.
	void Update();

	//----------------���f���֘A-----------------.
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);
	//���f���f�[�^�󂯓n��(�֘A�t��).
	void AttachModel(clsDx9Mesh* pModel);
	//���f���f�[�^�֘A�t������.
	void DetatchModel();
	//------------------------------------------.

	//-----------------�����蔻��-------------------.
	//���Փ˔���.
	bool SphereCollision(clsChara* pTarget, SSPHERE *pSSphere = NULL);
	//���Փ˔���.
	bool BBoxCollision(clsChara* pTarget, BBOX *pBBox = NULL);

	//---------------------------------------------.

	HRESULT	FindVerticesOnPoly(LPD3DXMESH pMeshForRay, DWORD dwPolyIndex, D3DXVECTOR3* pVecVertices);

	//Init�EAction�͊e�I�u�W�F�N�g�Ɋ��蓖�Ă�.
	virtual void Init() = 0;
	virtual void Action() = 0;

	virtual void Init_NotColl() {};
	virtual void Action2(){};

public:

	/********�ݒ�֐�*********/
	//���W�ݒ�.
	void SetPosition(D3DXVECTOR3 &vPos){ m_vPos = vPos; }
	//�傫���ݒ�.
	void SetScale(float Scale){ m_Scale = Scale; }
	//��]�l�ݒ�.
	void SetRot(D3DXVECTOR3 &vRot){ m_vRot = vRot; }

	/********�擾�֐�*********/
	clsDx9Mesh* GetStaicMesh(){ return m_pStaticMesh; }

	//�ʂłق����Ƃ���GetPos().x or y or z�łƂ��.
	D3DXVECTOR3 GetPos(){ return m_vPos; }

	float GetScale(){ return m_Scale; }

	float GetYaw(){ return m_Yaw; }



	//���̑����ʍ���.
	bool m_DeadFlag = false;

public:
	//�̨��쐬.
	HRESULT InitSphere(clsDx9Mesh* pMesh = NULL);

	//�޳��ިݸ��ޯ���쐬.
	HRESULT	InitBBox(clsDx9Mesh* pMesh = NULL);

	D3DXVECTOR3 m_vPos;

	float		m_ScaleSize;			//�f�[�^�ǂݍ��ݎ��̃��f���T�C�Y����p.

protected:

	clsDx9Mesh*	m_pStaticMesh;

	D3DXVECTOR3 m_vRot;			//��]�l�̐ݒ�.
	float		m_Scale;		//�傫��.
	SSPHERE		m_SSphere;		//���萶���p.
	BBOX		m_BBox;			//����.

	D3DXVECTOR3 m_vAxis;		//��]��.

	float		m_Yaw;			//Intersect�֐��Ŏg�p.
	float		m_Pitch;		//Intersect�֐��Ŏg�p.



};



#endif