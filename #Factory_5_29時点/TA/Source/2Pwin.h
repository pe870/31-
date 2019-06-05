#ifndef CLEAR_H
#define CLEAR_H
#include <string>
#include <vector>

#include "cCommon.h"
#include "Base.h"
// タイトルシーン.
class CSceneP2win : public CSceneBase
{
public:
	CSceneP2win(const char* SceneName);
	virtual ~CSceneP2win();

	void Control();

	void Action(SceneIndex &Scene);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);

	void Load(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

protected:
	//テクスチャリスト.
	vector<std::string> TexList =
	{
		 "Data\\Texture\\Scene\\2pwin.bmp",
	};

private:

	cls2DTex*			Clear;
};
#endif