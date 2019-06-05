#include "1Pwin.h"

CSceneP1win::CSceneP1win(const char* SceneName)
	: CSceneBase(SceneName)
{

}

CSceneP1win::~CSceneP1win()
{
	SAFE_DELETE(Over);
}

void CSceneP1win::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
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

	Over = new cls2DTex;
	Over->Init(pDevice, pContext, TexF_Name, ss);
	Over->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Over->m_Alpha = 1.0f;

}

void CSceneP1win::Control()
{

}

void CSceneP1win::Action(SceneIndex &Scene)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		Scene = SceneIndex::TITLE;
	}
}

void CSceneP1win::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	Over->Render();
}
