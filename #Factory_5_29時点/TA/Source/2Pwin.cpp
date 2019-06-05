#include "2Pwin.h"

CSceneP2win::CSceneP2win(const char* SceneName)
	: CSceneBase(SceneName)
{

}

CSceneP2win::~CSceneP2win()
{
	SAFE_DELETE(Clear);
}

void CSceneP2win::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	//スプライト情報を設定する.
	SPRITE_STATE	ss;
	ss.U = 1.0f;
	ss.V = 1.0f;

	ss.Width = WND_W;
	ss.Height = WND_H;

	//ファイル名.
	LPSTR TexF_Name = nullptr;
	//読込リストNo.
	int ListNo = 0;
	//型を合わせる.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());

	Clear = new cls2DTex;
	Clear->Init(pDevice, pContext, TexF_Name, ss);
	Clear->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Clear->m_Alpha = 1.0f;

}

void CSceneP2win::Control()
{

}

void CSceneP2win::Action(SceneIndex &Scene)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		Scene = SceneIndex::TITLE;
	}

}

void CSceneP2win::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	Clear->Render();
}
