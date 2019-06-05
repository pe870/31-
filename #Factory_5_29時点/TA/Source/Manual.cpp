#include "Manual.h"

CSceneManual::CSceneManual(const char* SceneName)
	: CSceneBase(SceneName)
{
}

CSceneManual::~CSceneManual()
{
	SAFE_DELETE(PlayManual);
}

void CSceneManual::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	//�X�v���C�g����ݒ肷��.
	SPRITE_STATE	ss;
	ss.U = 1.0f;
	ss.V = 1.0f;
	ss.Width = WND_W;
	ss.Height = WND_H;

	//�t�@�C����.
	LPSTR TexF_Name = nullptr;
	//�Ǎ����X�gNo.
	int ListNo = 0;
	//�^�����킹��.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());

	PlayManual = new cls2DTex;
	PlayManual->Init(pDevice, pContext, TexF_Name, ss);
	PlayManual->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PlayManual->m_Alpha = 1.0f;

}

void CSceneManual::Control()
{

}

void CSceneManual::Action(SceneIndex &Scene)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		Scene = SceneIndex::PLAY;
	}

}

void CSceneManual::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	PlayManual->Render();
}
