#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H


#include "Base.h"
#include "Title.h"
#include "Manual.h"
#include "Play.h"
#include "1Pwin.h"
#include "2Pwin.h"

//-------------------
//enum・構造体.
//-------------------
	//シーン内訳.

// シーンマネージャ.
class CSceneManager
{
public:
	CSceneManager();

	~CSceneManager();
	void Load(claResource *SetUP, DInput *Controll);
	void Load(ID3D11Device* pDevice,ID3D11DeviceContext* pContext);
	void Update(SceneIndex &Scene);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);
	void SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw);
	void SetNextScene(SceneIndex index);
	void TransitionScene();

	bool CheckingScene = false;

private:

	CSceneBase*		m_pScene;

	CSceneTitle*	m_pS_Title;
	SceneIndex		m_NowScnene;
	SceneIndex		m_NextScene;


};


#endif