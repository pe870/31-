#ifndef PLAY_H
#define PLAY_H

#include <string>
#include <vector>

#include "cCommon.h"

#include "Base.h"
#include "DX9Mesh.h"

#include "Charactor.h"
#include "C_Player.h"
#include "C_Object.h"

//定数.
const int LIFE_MAX = 20;
const int PlayerMAX = 2;
const int GaugeMax = 100;
// ゲームメインシーン.
class CSceneGameMain: public CSceneBase
{
public:
	//----------------触るな------------------.
	CSceneGameMain(const char* SceneName);

	virtual ~CSceneGameMain();

	void Load(claResource *setUP, DInput *controal);

	void Load(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	void Control();
	void Action(SceneIndex &Scene);

	void SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);
private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11Texture2D*			m_pBackBuffer_DSTex;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

protected:
	//テクスチャリスト.
	vector<string> TexList =
	{
		"Data\\Texture\\UI\\HP\\HP_FINE.png",			//HP.
		"Data\\Texture\\UI\\HP\\HP_CAUTION.png",
		"Data\\Texture\\UI\\HP\\HP_DENGER.png",

		"Data\\Texture\\UI\\HP\\P_HPBack.png",			//HPバーの背景.

		"Data\\Texture\\UI\\Player\\Player1Name.png",	//どちらのUIか.
		"Data\\Texture\\UI\\Player\\Player2Name.png",

		"Data\\Texture\\UI\\Burst\\Burst.png",
		"Data\\Texture\\UI\\Burst\\Gauge.png",

	};

private:
	int HP_P1 , HP_P2;				//体力.
	int P1DamageCnt,P2DamageCnt;	//ダメージ量(一定数でライフ-1).
	int BurstCnt1P, BurstCnt2P;		//ブーストゲージ増減用.

	//----------------------------------------.

private:

	//モデル情報(これより以降はおｋ、関数作るならpublic protected作ること).
	clsPlayer*					P_1P;					//1P.
	clsPlayer*					P_2P;					//2P.

	clsObject*					Ground;					//地面
	
	//テクスチャ情報.

	//HPの表示(状態推移込)
	cls2DTex*					P_1FINE[LIFE_MAX];			//HP：元気.
	cls2DTex*					P_1CAUTION[LIFE_MAX];		//HP：やばい.
	cls2DTex*					P_1DENGER[LIFE_MAX];		//HP：死にかけ.
	cls2DTex*					P_2FINE[LIFE_MAX];
	cls2DTex*					P_2CAUTION[LIFE_MAX];
	cls2DTex*					P_2DENGER[LIFE_MAX];

	//UIがどのキャラを示す.
	cls2DTex*					PlayerName1;
	cls2DTex*					PlayerName2;
	
	//プレイヤー数分必要なもの.
	cls2DTex*					P_HPBackGround[PlayerMAX];
	cls2DTex*					BurstGauge[PlayerMAX];		//背景部分.

	//ブーストゲージ(細かいのを多数描画).
	cls2DTex*					Boost1P[GaugeMax];			//中の部分.
	cls2DTex*					Boost2P[GaugeMax];			//中の部分.

};
#endif