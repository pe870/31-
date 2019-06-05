#ifndef OVER_H
#define OVER_H

#include <string>
#include <vector>

#include "Base.h"
#include "cCommon.h"

// タイトルシーン.
class CSceneP1win : public CSceneBase
{
public:
	CSceneP1win(const char* SceneName);
	virtual ~CSceneP1win();

	void Control();

	void Action(SceneIndex &Scene);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

	void Load(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

protected:
	//テクスチャリスト.
	vector<string> TexList =
	{
		"Data\\Texture\\Scene\\1pwin.bmp",
	};

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11Texture2D*			m_pBackBuffer_DSTex;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

private:
	cls2DTex*						Over;

};
#endif