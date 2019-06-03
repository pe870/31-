#include "SceneManager.h"
#include <crtdbg.h>

CSceneBase* CreateScene(SceneIndex index)
{
	_ASSERT_EXPR(SceneIndex::Start <= index && index <= SceneIndex::End, L"設定されたシーン以外を設定した");

	switch (index) 
	{
	case SceneIndex::TITLE:
		return new CSceneTitle("Title");
	case SceneIndex::MANUAL:
		return new CSceneManual("Play Manual");
	case SceneIndex::PLAY:
		return new CSceneGameMain("GameMain");
	case SceneIndex::P1WIN:
		return new CSceneP1win("P1win");
	case SceneIndex::P2WIN:
		return new CSceneP2win("P2win");
	default:
		return nullptr;
	}
}


CSceneManager::CSceneManager()
	: m_pScene(nullptr)
	, m_NowScnene(SceneIndex::Nothing)
	, m_NextScene(SceneIndex::TITLE)
{
	TransitionScene();
}

CSceneManager::~CSceneManager()
{
	if (m_pScene != nullptr) 
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
//モデル読込.
void CSceneManager::Load(claResource *SetUP, DInput *Controll)
{
	m_pScene->Load(SetUP, Controll);
}
//テクスチャ読込.
void CSceneManager::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pScene->Load(pDevice,pContext);
}

void CSceneManager::SetNextScene(SceneIndex index)
{
	m_NextScene = index;
}

void CSceneManager::SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw)
{
	m_pScene->SetCameraPos(vLook, vEye, Yaw);

}

void CSceneManager::Update(SceneIndex &Scene)
{
	SceneIndex temp = Scene;
	m_pScene->Update(Scene);
	if (temp != Scene)
	{
		CheckingScene = true;
	}
}

void CSceneManager::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	m_pScene->Draw(mView,mProj,vLight,vEye);
};

void CSceneManager::TransitionScene()
{
	if (m_NowScnene != m_NextScene)
	{
		if (m_pScene != nullptr)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		m_pScene = CreateScene(m_NextScene);
		m_NowScnene = m_NextScene;
	}
}

