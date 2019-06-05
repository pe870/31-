#ifndef CHARACTOR_H
#define CHARACTOR_H

#include "DX9Mesh.h"
#include "DebugText.h"
#include "Global.h"


//キャラクラス.
class clsChara
{
public:
	clsChara();
	virtual ~clsChara();

	//拡張や回転など座標の値をモデルデータに反映.
	void Update();

	//----------------モデル関連-----------------.
	void Render(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);
	//モデルデータ受け渡し(関連付け).
	void AttachModel(clsDx9Mesh* pModel);
	//モデルデータ関連付け解除.
	void DetatchModel();
	//------------------------------------------.

	//-----------------当たり判定-------------------.
	//●衝突判定.
	bool SphereCollision(clsChara* pTarget, SSPHERE *pSSphere = NULL);
	//■衝突判定.
	bool BBoxCollision(clsChara* pTarget, BBOX *pBBox = NULL);

	//---------------------------------------------.

	HRESULT	FindVerticesOnPoly(LPD3DXMESH pMeshForRay, DWORD dwPolyIndex, D3DXVECTOR3* pVecVertices);

	//Init・Actionは各オブジェクトに割り当てる.
	virtual void Init() = 0;
	virtual void Action() = 0;

	virtual void Init_NotColl() {};
	virtual void Action2(){};

public:

	/********設定関数*********/
	//座標設定.
	void SetPosition(D3DXVECTOR3 &vPos){ m_vPos = vPos; }
	//大きさ設定.
	void SetScale(float Scale){ m_Scale = Scale; }
	//回転値設定.
	void SetRot(D3DXVECTOR3 &vRot){ m_vRot = vRot; }

	/********取得関数*********/
	clsDx9Mesh* GetStaicMesh(){ return m_pStaticMesh; }

	//個別でほしいときはGetPos().x or y or zでとれる.
	D3DXVECTOR3 GetPos(){ return m_vPos; }

	float GetScale(){ return m_Scale; }

	float GetYaw(){ return m_Yaw; }



	//その他共通項目.
	bool m_DeadFlag = false;

public:
	//ｽﾌｨｱ作成.
	HRESULT InitSphere(clsDx9Mesh* pMesh = NULL);

	//ﾊﾞｳﾝﾃﾞｨﾝｸﾞﾎﾞｯｸｽ作成.
	HRESULT	InitBBox(clsDx9Mesh* pMesh = NULL);

	D3DXVECTOR3 m_vPos;

	float		m_ScaleSize;			//データ読み込み時のモデルサイズ代入用.

protected:

	clsDx9Mesh*	m_pStaticMesh;

	D3DXVECTOR3 m_vRot;			//回転値の設定.
	float		m_Scale;		//大きさ.
	SSPHERE		m_SSphere;		//判定生成用.
	BBOX		m_BBox;			//同上.

	D3DXVECTOR3 m_vAxis;		//回転軸.

	float		m_Yaw;			//Intersect関数で使用.
	float		m_Pitch;		//Intersect関数で使用.



};



#endif