#ifndef PLAY_H
#define PLAY_H

#include <string>
#include <vector>

#include "cCommon.h"

#include "Base.h"
#include "DX9Mesh.h"

#include "Charactor.h"
#include "C_Player.h"
#include "C_Object.h"

//�萔.
const int LIFE_MAX = 20;
const int PlayerMAX = 2;
const int GaugeMax = 100;
// �Q�[�����C���V�[��.
class CSceneGameMain: public CSceneBase
{
public:
	//----------------�G���------------------.
	CSceneGameMain(const char* SceneName);

	virtual ~CSceneGameMain();

	void Load(claResource *setUP, DInput *controal);

	void Load(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	void Control();
	void Action(SceneIndex &Scene);

	void SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw);

	void Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye);
private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11Texture2D*			m_pBackBuffer_DSTex;
	ID3D11DepthStencilView*		m_pBackBuffer_DSTexDSV;

protected:
	//�e�N�X�`�����X�g.
	vector<string> TexList =
	{
		"Data\\Texture\\UI\\HP\\HP_FINE.png",			//HP.
		"Data\\Texture\\UI\\HP\\HP_CAUTION.png",
		"Data\\Texture\\UI\\HP\\HP_DENGER.png",

		"Data\\Texture\\UI\\HP\\P_HPBack.png",			//HP�o�[�̔w�i.

		"Data\\Texture\\UI\\Player\\Player1Name.png",	//�ǂ����UI��.
		"Data\\Texture\\UI\\Player\\Player2Name.png",

		"Data\\Texture\\UI\\Burst\\Burst.png",
		"Data\\Texture\\UI\\Burst\\Gauge.png",

	};

private:
	int HP_P1 , HP_P2;				//�̗�.
	int P1DamageCnt,P2DamageCnt;	//�_���[�W��(��萔�Ń��C�t-1).
	int BurstCnt1P, BurstCnt2P;		//�u�[�X�g�Q�[�W�����p.

	//----------------------------------------.

private:

	//���f�����(������ȍ~�͂����A�֐����Ȃ�public protected��邱��).
	clsPlayer*					P_1P;					//1P.
	clsPlayer*					P_2P;					//2P.

	clsObject*					Ground;					//�n��
	
	//�e�N�X�`�����.

	//HP�̕\��(��Ԑ��ڍ�)
	cls2DTex*					P_1FINE[LIFE_MAX];			//HP�F���C.
	cls2DTex*					P_1CAUTION[LIFE_MAX];		//HP�F��΂�.
	cls2DTex*					P_1DENGER[LIFE_MAX];		//HP�F���ɂ���.
	cls2DTex*					P_2FINE[LIFE_MAX];
	cls2DTex*					P_2CAUTION[LIFE_MAX];
	cls2DTex*					P_2DENGER[LIFE_MAX];

	//UI���ǂ̃L����������.
	cls2DTex*					PlayerName1;
	cls2DTex*					PlayerName2;
	
	//�v���C���[�����K�v�Ȃ���.
	cls2DTex*					P_HPBackGround[PlayerMAX];
	cls2DTex*					BurstGauge[PlayerMAX];		//�w�i����.

	//�u�[�X�g�Q�[�W(�ׂ����̂𑽐��`��).
	cls2DTex*					Boost1P[GaugeMax];			//���̕���.
	cls2DTex*					Boost2P[GaugeMax];			//���̕���.

};
#endif