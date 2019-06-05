#ifndef C_RESOURCE_H
#define C_RESOURCE_H

#include "DX9Mesh.h"

enum enStaticMesh
{
	enStaticMesh_Player1P,		//自機.
	enStaticMesh_Player2P,		//自機.

	enStaticMesh_Ground,		//地面.

	enStaticMesh_Max,			//自動で最大値
	enStaticMesh_Min = 0,		//初期値のため 0 固定

};

class claResource
{
public:
	claResource();
	~claResource();

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11,ID3D11DeviceContext* pContext11);

	HRESULT CreateStaticMesh(int enMesh, LPSTR fileName);

	HRESULT ReleaseStaticMesh(int enMesh);

	clsDx9Mesh*	GetStaticMesh(int enMesh);

	HRESULT LoadStaticMeshAll()
	{
		//読み込むXファイル名のリスト.
		//enStaticMeshで宣言した順に呼ぶ.
		char fileList[enStaticMesh_Max][64] =
		{
			"Data\\Model\\Player\\player1.x",
			"Data\\Model\\Player\\player2.x",
			"Data\\Model\\Ground\\ground.x",
		};

		//順番にXファイルを読込.
		for (int ix = 0; ix < enStaticMesh_Max; ix++)
		{
			CreateStaticMesh(ix, fileList[ix]);
		}

		return S_OK;
	}


private:
	HWND					m_hWnd;
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;

	clsDx9Mesh**			m_ppStaticMesh;

	//範囲内か確認する関数.
	bool CheckRangeMainStaticMesh(int enMesh);
};



#endif