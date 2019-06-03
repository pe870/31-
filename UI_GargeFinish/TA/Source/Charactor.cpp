#include "Charactor.h"

clsChara::clsChara()
	:m_pStaticMesh(NULL)
	, m_vPos(0.0f,0.0f,0.0f)
	, m_vRot(0.0f, 0.0f, 0.0f)
	, m_Scale(1.0f)
	, m_ScaleSize(1.0f)

{

}

clsChara::~clsChara()
{

}

void clsChara::Update()
{
	if (m_pStaticMesh == NULL)
	{
		return;
	}
	m_pStaticMesh->m_Scale = m_Scale;
	m_pStaticMesh->m_Yaw = m_vRot.y;
	m_pStaticMesh->m_Pitch = m_vRot.x;
	m_pStaticMesh->m_Roll = m_vRot.z;
	m_pStaticMesh->m_vPos = m_vPos;
}

void clsChara::Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	if (m_pStaticMesh == NULL)
	{
		return;
	}

	//�X�V.
	Update();
	//���b�V���t�@�C���̃����_�����O�֐����Ă�,
	m_pStaticMesh->Render(mView, mProj, vLight, vEye);
}

//���f���f�[�^�󂯓n��(�֘A�t��).
void clsChara::AttachModel(clsDx9Mesh* pModel)
{
	if (pModel != NULL)
	{
		m_pStaticMesh = pModel;
	}
}

//���f���f�[�^�֘A�t������.
void clsChara::DetatchModel()
{
	if (m_pStaticMesh != NULL)
	{
		m_pStaticMesh = NULL;
	}
}

//�o�E���f�B���O�X�t�B�A(����p��)�쐬.
HRESULT clsChara::InitSphere(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;//���_�ޯ̧.
	void*		pVertices = NULL;//���_.
	D3DXVECTOR3	vCenter;	//���S.
	float		Radius;		//���a.

	if (pMesh == NULL){	pMesh = m_pStaticMesh; }

	//���_�ޯ̧���擾.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB))){	return E_FAIL; }
	//ү���̒��_�ޯ̧��ۯ�����.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//ү���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices,pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),	&vCenter,&Radius);

	//��ۯ�.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//���S�Ɣ��a���\���̂ɐݒ�.
	pMesh->m_Sphere.vCenter = vCenter;
	pMesh->m_Sphere.Radius = Radius;

	//����p�ɋL�^.
	m_SSphere.vCenter = pMesh->m_Sphere.vCenter;
	m_SSphere.Radius = pMesh->m_Sphere.Radius;

	return S_OK;
}

//�o�E���f�B���O�{�b�N�X(����p��)�쐬.
HRESULT	clsChara::InitBBox(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 Max, Min;

	if (pMesh == NULL){	pMesh = m_pStaticMesh; }

	//ү���̒��_�o�b�t�@�����b�N����.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		MessageBox(NULL, "���_�o�b�t�@�擾���s", "error", MB_OK);
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		MessageBox(NULL, "���_�o�b�t�@���b�N���s", "error", MB_OK);
		return E_FAIL;

	}
	//���b�V�����̒��_�ʒu�̍ő�ƍŏ�����������
	D3DXComputeBoundingBox((D3DXVECTOR3*)pVertices,	pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),	&Min, &Max);

	pVB->Unlock();//�A�����b�N.
	SAFE_RELEASE(pVB);

	m_BBox.vPosMax = Max;
	m_BBox.vPosMin = Min;

	//���x�N�g���E���̒���(���̏ꍇ�A�{�b�N�X�̊e���a)������������.
	m_BBox.LengthX = (Max.x - Min.x) / 2.0f;
	m_BBox.LengthY = (Max.y - Min.y) / 2.0f;
	m_BBox.LengthZ = (Max.z - Min.z) / 2.0f;

	return S_OK;
}

//�Փ˔���.
bool clsChara::SphereCollision(clsChara* pTarget, SSPHERE *pSSphere)
{
	D3DXVECTOR3 tempPos;
	float		tempRadius = 0.0f;
	if (pSSphere != NULL)
	{
		tempPos = pSSphere->vPos + m_vPos;
		tempRadius = pSSphere->Radius;
	}
	else
	{
		tempPos = m_SSphere.vPos + m_vPos;
		tempRadius = m_SSphere.Radius;
	}
	//�Q�̕��̂̒��S�Ԃ̋��������߂�.
	D3DXVECTOR3 vLength = pTarget->m_vPos - tempPos;

	//�����ɕϊ�����.
	float Length = D3DXVec3Length(&vLength);

	//�Q�̕��̂̋������A�Q�̕��̂̔��a�����������̂�菬�����Ƃ������Ƃ�.
	//�̨����m���d�Ȃ��Ă���(�Փ˂��Ă���)�Ƃ�������.
	if (Length <= tempRadius + pTarget->m_SSphere.Radius)
	{
		return true;//�Փ�.
	}
	return false;//�Փ˂��Ă��Ȃ�.
}

//���Փ˔���.
bool clsChara::BBoxCollision(clsChara* pTarget, BBOX *pBBox)
{
	//�U���p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecAtkMax, vecAtkMin;	//�ő�A�ŏ����_.

	if (pBBox != NULL){
		vecAtkMax = pBBox->vPosMax + m_vPos;
		vecAtkMin = pBBox->vPosMin + m_vPos;
	}
	else{
		vecAtkMax = m_BBox.vPosMax + m_vPos;
		vecAtkMin = m_BBox.vPosMin + m_vPos;
	}

	//�ڕW�p�p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecTrgMax, vecTrgMin;	//�ő�A�ŏ����_.
	vecTrgMax = pTarget->m_BBox.vPosMax + pTarget->m_vPos;
	vecTrgMin = pTarget->m_BBox.vPosMin + pTarget->m_vPos;


	//2�̃��b�V�����ꂼ��̍ő�A�ŏ��ʒu���g��.
	//4�̏�񂪂���΁A�Փ˂����o�ł���.
	if (vecAtkMin.x<vecTrgMax.x &&vecAtkMax.x>vecTrgMin.x
		&&vecAtkMin.y<vecTrgMax.y &&vecAtkMax.y>vecTrgMin.y
		&&vecAtkMin.z<vecTrgMax.z &&vecAtkMax.z>vecTrgMin.z)
	{
		return true;	//�Փ˂��Ă���.
	}
	return false;		//�Փ˂��Ă��Ȃ�.
}


//�����ʒu�̃|���S���̒��_��������.
//(���_���W�̓��[�J�����W)
HRESULT	clsChara::FindVerticesOnPoly(
	LPD3DXMESH	pMeshForRay, DWORD	dwPolyIndex,
	D3DXVECTOR3* pVecVertices)
{
	//���_���̃o�C�g�����擾.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//���_�����擾����.
	DWORD dwVertexAmt = pMeshForRay->GetNumVertices();
	//�ʐ��擾.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = NULL;

	//�C���f�b�N�X�o�b�t�@�����b�N(�Ǎ����[�h)
	pMeshForRay->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = NULL;
	FLOAT* pfVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMeshForRay->GetVertexBuffer(&VB);

	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//�|���S���̒��_�̂ЂƂڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//�|���S���̒��_�̂ӂ��ڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//�|���S���̒��_�݂̂��ڂ��擾.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		//���b�N����.
		pMeshForRay->UnlockIndexBuffer();
		VB->Unlock();

	}

	VB->Release();

	return S_OK;

}
