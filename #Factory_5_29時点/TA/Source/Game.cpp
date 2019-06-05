#pragma warning(disable:4005)
#pragma warning(disable:4305)
#pragma warning(disable:4996)

#include "Game.h"

clsGame::clsGame()
: m_pDevice(nullptr)
, m_pContext(nullptr)
, m_pSampleLinear(nullptr)
, m_pTexture(nullptr)
, m_Camera()
, m_mView()
, m_mProj()
, m_vLight()
, m_pClsDx9Mesh(nullptr)
, m_pResource(nullptr)
, pSceneMgr(nullptr)
{
	m_Camera.vEye = D3DXVECTOR3(0.0f, 3.7f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLight = D3DXVECTOR3(0.3f, 1.2f, -2.0f);
};

clsGame::~clsGame()
{
	SAFE_DELETE(m_ptDebugText);
	//コントローラ情報.
	delete m_pCtrler;
	//シーン情報.
	SAFE_DELETE(pSceneMgr);

	//ﾓﾃﾞﾙの解放.
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);

	//リソースの開放.
	SAFE_DELETE(m_pResource);

	//Direct3Dｵﾌﾞｼﾞｪｸﾄの解放.
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

//触らないで.
void clsGame::Loop()
{
	//3Dの作成.
	m_pDirect3D = new clsDirect3D;
	m_pDirect3D->Create3D(m_hWnd);
	//必要な情報の取得.
	m_pDevice = m_pDirect3D->GetDevice();
	m_pContext = m_pDirect3D->GetDeviceContext();

	m_pResource = new claResource;
	m_pResource->Init(m_hWnd, m_pDevice, m_pContext);
	m_pResource->LoadStaticMeshAll();
	
	pSceneMgr = new CSceneManager();

	LoadData();

	//--------------ﾌﾚｰﾑﾚｰﾄ調整準備.----------------------------//

	float Rate = 0.0f;	//ﾚｰﾄ.
	float FPS = 60.0f;	//FPS値.
	DWORD sync_old = timeGetTime();	//過去時間.
	DWORD sync_now;					//現在時間.
	//時間処理の為、最小単位を1ﾐﾘ秒に変更.
	timeBeginPeriod(1);

	//----------------------------------------------------------//

	//ﾒｯｾｰｼﾞﾙｰﾌﾟ.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		sync_now = timeGetTime();//現在時間を取得.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Rate = 1000.0f / FPS;	//理想時間を算出.
		if (sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;//現在時間に置き換え.

			AppMain();
		}
	}
	//ｱﾌﾟﾘｹｰｼｮﾝの終了.
	timeEndPeriod(1);
}

//ﾒｲﾝ処理.
void clsGame::AppMain()
{
	/////////////////////////////////////
	//*********************************//
	//*		絶　対　触　る　な        *//
	//*********************************//
	/////////////////////////////////////

	//Updateを通ってからindexが変わっていないか確認.
	//変わっていたらフラグを立て、次のシーンへ移行する.
	if (pSceneMgr->CheckingScene == true)
	{
		pSceneMgr->SetNextScene(index);				//入れ替わった先のシーンにする.
		pSceneMgr->TransitionScene();				//今あるシーンを破棄して次のシーンを生成.
		pSceneMgr->Load(m_pResource, m_pCtrler);	//モデル情報の読込.
		pSceneMgr->Load(m_pDevice, m_pContext);		//テクスチャ情報の読込.

		pSceneMgr->CheckingScene = false;
	}

	//本体.
	pSceneMgr->Update((index));
	//カメラ位置の設定.
	pSceneMgr->SetCameraPos(m_Camera.vEye, m_Camera.vLook, m_Camera.Yaw);
	//モデル・テクスチャ描画.
	Render();
}

void clsGame::LoadData()
{
	//モデル情報の読込(起動時の初回読込).
	pSceneMgr->Load(m_pResource, m_pCtrler);
	//テクスチャ情報の読込(起動時の初回読込).
	pSceneMgr->Load(m_pDevice, m_pContext);

#ifdef _DEBUG
	//デバッグテキストの初期化.
	m_ptDebugText = new clsDebugText;
	D3DXVECTOR4 vColor(1.0f, 0.0f, 0.0f, 1.0f);
	if (FAILED(m_ptDebugText->Init(m_pContext, WND_W, WND_H, 50.0f, vColor)))
	{ return; }
#endif

}

void clsGame::Render()
{
	//コメントが追加されてるか確認する.
	//画面ｸﾘｱ.
	m_pDirect3D->SetBuffer();
	//カメラとプロジェクションの設定.
	Camera();
	Proj();
	pSceneMgr->Draw(m_mView, m_mProj, m_vLight, m_Camera.vEye);
	//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞ(色消去).
	m_pDirect3D->SetBlend(true);
	m_pDirect3D->RenderPresent();
}

void clsGame::Camera()
{
	//Y軸回転行列.
	D3DXMatrixRotationY(&m_Camera.mRotation, m_Camera.Yaw);
	//軸ベクトルを用意する.
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);
	//カメラ位置・注視位置を調整.
	m_Camera.vEye -= vecAxisZ * 6.0f;		//自機の背中.
	m_Camera.vLook += vecAxisZ * 3.0f;		//自機の前側.
	//それぞれの高さ調整.
	m_Camera.vEye.y += 3.5f;				//自機の背中.
	m_Camera.vLook.y += 0.1f;				//自機の前側.
	//ﾋﾞｭｰ(ｶﾒﾗ)変換.
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方位置.
	//(out)ﾋﾞｭｰ計算結果.
	D3DXMatrixLookAtLH(&m_mView,&m_Camera.vEye, &m_Camera.vLook, &vUpVec);
}

void clsGame::Proj()
{
	//ﾌﾟﾛｼﾞｪｸｼｮﾝ(射影行列)変換.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,D3DX_PI / 4.0,(FLOAT)WND_W / (FLOAT)WND_H,0.1f,100.0f);
}
