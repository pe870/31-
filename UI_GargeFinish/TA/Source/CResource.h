#ifndef C_RESOURCE_H
#define C_RESOURCE_H

#include "DX9Mesh.h"

enum enStaticMesh
{
	enStaticMesh_Player1P,		//���@.
	enStaticMesh_Player2P,		//���@.

	enStaticMesh_Ground,		//�n��.

	enStaticMesh_Max,			//�����ōő�l
	enStaticMesh_Min = 0,		//�����l�̂��� 0 �Œ�

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
		//�ǂݍ���X�t�@�C�����̃��X�g.
		//enStaticMesh�Ő錾�������ɌĂ�.
		char fileList[enStaticMesh_Max][64] =
		{
			"Data\\Model\\Player\\player1.x",
			"Data\\Model\\Player\\player2.x",
			"Data\\Model\\Ground\\ground.x",
		};

		//���Ԃ�X�t�@�C����Ǎ�.
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

	//�͈͓����m�F����֐�.
	bool CheckRangeMainStaticMesh(int enMesh);
};



#endif