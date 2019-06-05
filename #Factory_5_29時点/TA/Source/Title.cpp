#include "Title.h"

CSceneTitle::CSceneTitle(const char* SceneName)
	: CSceneBase(SceneName)
{
}

CSceneTitle::~CSceneTitle()
{
	SAFE_DELETE(Title);
}

void CSceneTitle::Load(ID3D11Device* pDevice,ID3D11DeviceContext* pContext)
{
	//スプライト情報を設定する.
	SPRITE_STATE ss;
	ss.U = 1.0f;
	ss.V = 1.0f;
	ss.Width = WND_W;
	ss.Height = WND_H;

	//ファイル名.
	LPSTR TexF_Name = nullptr;
	//読込リストNo.
	int ListNo = 0;
	//型を合わせてリスト順で読ませる.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());

	Title = new cls2DTex;
	Title->Init(pDevice, pContext, TexF_Name, ss);
	Title->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Title->m_Alpha = 1.0f;

}

void CSceneTitle::Control()
{

}

void CSceneTitle::Action(SceneIndex &Scene)
{

	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		Scene = SceneIndex::MANUAL;
	}
}

void CSceneTitle::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	Title->Render();
}

