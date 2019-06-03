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

	//更新.
	Update();
	//メッシュファイルのレンダリング関数を呼ぶ,
	m_pStaticMesh->Render(mView, mProj, vLight, vEye);
}

//モデルデータ受け渡し(関連付け).
void clsChara::AttachModel(clsDx9Mesh* pModel)
{
	if (pModel != NULL)
	{
		m_pStaticMesh = pModel;
	}
}

//モデルデータ関連付け解除.
void clsChara::DetatchModel()
{
	if (m_pStaticMesh != NULL)
	{
		m_pStaticMesh = NULL;
	}
}

//バウンディングスフィア(判定用球)作成.
HRESULT clsChara::InitSphere(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;//頂点ﾊﾞｯﾌｧ.
	void*		pVertices = NULL;//頂点.
	D3DXVECTOR3	vCenter;	//中心.
	float		Radius;		//半径.

	if (pMesh == NULL){	pMesh = m_pStaticMesh; }

	//頂点ﾊﾞｯﾌｧを取得.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB))){	return E_FAIL; }
	//ﾒｯｼｭの頂点ﾊﾞｯﾌｧをﾛｯｸする.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//ﾒｯｼｭの外接円の中心と半径を計算する.
	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices,pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),	&vCenter,&Radius);

	//ｱﾝﾛｯｸ.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//中心と半径を構造体に設定.
	pMesh->m_Sphere.vCenter = vCenter;
	pMesh->m_Sphere.Radius = Radius;

	//判定用に記録.
	m_SSphere.vCenter = pMesh->m_Sphere.vCenter;
	m_SSphere.Radius = pMesh->m_Sphere.Radius;

	return S_OK;
}

//バウンディングボックス(判定用箱)作成.
HRESULT	clsChara::InitBBox(clsDx9Mesh* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 Max, Min;

	if (pMesh == NULL){	pMesh = m_pStaticMesh; }

	//ﾒｯｼｭの頂点バッファをロックする.
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		MessageBox(NULL, "頂点バッファ取得失敗", "error", MB_OK);
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		MessageBox(NULL, "頂点バッファロック失敗", "error", MB_OK);
		return E_FAIL;

	}
	//メッシュ内の頂点位置の最大と最小を検索する
	D3DXComputeBoundingBox((D3DXVECTOR3*)pVertices,	pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()),	&Min, &Max);

	pVB->Unlock();//アンロック.
	SAFE_RELEASE(pVB);

	m_BBox.vPosMax = Max;
	m_BBox.vPosMin = Min;

	//軸ベクトル・軸の長さ(この場合、ボックスの各半径)を初期化する.
	m_BBox.LengthX = (Max.x - Min.x) / 2.0f;
	m_BBox.LengthY = (Max.y - Min.y) / 2.0f;
	m_BBox.LengthZ = (Max.z - Min.z) / 2.0f;

	return S_OK;
}

//衝突判定.
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
	//２つの物体の中心間の距離を求める.
	D3DXVECTOR3 vLength = pTarget->m_vPos - tempPos;

	//長さに変換する.
	float Length = D3DXVec3Length(&vLength);

	//２つの物体の距離が、２つの物体の半径をたしたものより小さいということは.
	//ｽﾌｨｱ同士が重なっている(衝突している)ということ.
	if (Length <= tempRadius + pTarget->m_SSphere.Radius)
	{
		return true;//衝突.
	}
	return false;//衝突していない.
}

//■衝突判定.
bool clsChara::BBoxCollision(clsChara* pTarget, BBOX *pBBox)
{
	//攻撃用に2つの頂点を用意し初期化する.
	D3DXVECTOR3 vecAtkMax, vecAtkMin;	//最大、最小頂点.

	if (pBBox != NULL){
		vecAtkMax = pBBox->vPosMax + m_vPos;
		vecAtkMin = pBBox->vPosMin + m_vPos;
	}
	else{
		vecAtkMax = m_BBox.vPosMax + m_vPos;
		vecAtkMin = m_BBox.vPosMin + m_vPos;
	}

	//目標用用に2つの頂点を用意し初期化する.
	D3DXVECTOR3 vecTrgMax, vecTrgMin;	//最大、最小頂点.
	vecTrgMax = pTarget->m_BBox.vPosMax + pTarget->m_vPos;
	vecTrgMin = pTarget->m_BBox.vPosMin + pTarget->m_vPos;


	//2つのメッシュそれぞれの最大、最小位置を使う.
	//4つの情報があれば、衝突を検出できる.
	if (vecAtkMin.x<vecTrgMax.x &&vecAtkMax.x>vecTrgMin.x
		&&vecAtkMin.y<vecTrgMax.y &&vecAtkMax.y>vecTrgMin.y
		&&vecAtkMin.z<vecTrgMax.z &&vecAtkMax.z>vecTrgMin.z)
	{
		return true;	//衝突している.
	}
	return false;		//衝突していない.
}


//交差位置のポリゴンの頂点を見つける.
//(頂点座標はローカル座標)
HRESULT	clsChara::FindVerticesOnPoly(
	LPD3DXMESH	pMeshForRay, DWORD	dwPolyIndex,
	D3DXVECTOR3* pVecVertices)
{
	//頂点毎のバイト数を取得.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//頂点数を取得する.
	DWORD dwVertexAmt = pMeshForRay->GetNumVertices();
	//面数取得.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = NULL;

	//インデックスバッファをロック(読込モード)
	pMeshForRay->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = NULL;
	FLOAT* pfVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMeshForRay->GetVertexBuffer(&VB);

	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//ポリゴンの頂点のひとつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//ポリゴンの頂点のふたつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//ポリゴンの頂点のみっつ目を取得.
		pfVertices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		//ロック解除.
		pMeshForRay->UnlockIndexBuffer();
		VB->Unlock();

	}

	VB->Release();

	return S_OK;

}
