#ifndef SCENE_BASE
#define SCENE_BASE

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "CResource.h"
#include "2DTex.h"
#include "DInput.h"


// 基底シーンクラス.
class CSceneBase
{

public:
	CSceneBase(const char* SceneName){ strcpy_s(m_SceneName, SceneName); }
	
	virtual ~CSceneBase() {}
	
	virtual void Load(claResource *setUP, DInput *controal) {};

	virtual void Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {};

	virtual void Update(SceneIndex &Scene) 
	{
		Control();
		Action(Scene);
	};

	virtual void SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw) {};

	virtual void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye){}

protected:
	virtual void Control() {}
	virtual void Action(SceneIndex &Scene) {}
	char m_SceneName[64];


};
#endif