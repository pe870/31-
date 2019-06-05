#ifndef GAME_H
#define GAME_H

#include "cCommon.h"
#include "Global.h"

#include "DInput.h"

#include "Direct3D.h"
#include "SceneManager.h"

#include "DX9Mesh.h"

#include "DebugText.h"

#include "Sound.h"


#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )//「D3DX～」の定義使用時に必要.


//外部データ.
//座標読み込みデータ構造体.
struct ObjectPosList
{
	//floatで座標を設定しているのでfloatに合わせる.
	float m_ePosX;
	float m_ePosY;
	float m_ePosZ;
};

struct Data
{
	D3DXVECTOR3 stPos;
	float m_eScalef;
	D3DXVECTOR4 PosSca;
};

//構造体.
//カメラ情報.
struct CAMERA
{
	D3DXVECTOR3			vEye;					//カメラ位置.
	D3DXVECTOR3			vLook;					//カメラ注視位置.
	float				Yaw;					//Y回転軸.
	D3DXMATRIX			mRotation;				//回転行列.
};

class clsGame
{
public:
	clsGame();
	~clsGame();

	void						Loop();

	void						AppMain();

	void						Render();
	//最初のデータ読込用.
	void						LoadData();

	//ｶﾒﾗ関数.
	void						Camera();
	//ﾌﾟﾛｼﾞｪｸｼｮﾝ関数.
	void						Proj();

	//モデルリソース用.
	claResource*				m_pResource;
	//シーン.
	CSceneManager				*pSceneMgr;

	HWND						m_hWnd;
	//コントローラー設定.
	DInput*						m_pCtrler;
	//Direct3D生成.
	clsDirect3D*				m_pDirect3D;

public:
	//シーンの情報.
	SceneIndex index = SceneIndex::TITLE;

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	ID3D11SamplerState*			m_pSampleLinear;		//ﾃｸｽﾁｬのｻﾝﾌﾟﾗ ﾃｸｽﾁｬに各種ﾌｨﾙﾀをかける.
	ID3D11ShaderResourceView*	m_pTexture;				//ﾃｸｽﾁｬ.
	CAMERA						m_Camera;				//カメラ情報.
	D3DXMATRIX					m_mView;				//ビュー(カメラ行列).
	D3DXMATRIX					m_mProj;				//プロジェクション行列.
	D3DXVECTOR3					m_vLight;				//ﾗｲﾄの方向.

	clsDx9Mesh*					m_pClsDx9Mesh;			//Dx9ﾒｯｼｭｸﾗｽ.

	clsDebugText*				m_ptDebugText;			//デバッグテキスト.

};


#endif//#ifndef GAME_H