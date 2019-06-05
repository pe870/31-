#ifndef MANUAL_H
#define MANUAL_H

#include <string>
#include <vector>


#include "Base.h"
#include "cCommon.h"

// タイトルシーン.
class CSceneManual : public CSceneBase
{
public:
	CSceneManual(const char* SceneName);

	virtual ~CSceneManual();

	void Load(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	void Control();

	void Action(SceneIndex &Scene);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

protected:
	//テクスチャリスト.
	vector<std::string> TexList =
	{
		"Data\\Texture\\Scene\\manual.bmp",
		//"Data\\Texture\\UI\\P_HP1.png",
	};

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11Texture2D*			m_pBackBuffer_DSTex;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

private:
	cls2DTex*						PlayManual;



};
#endif