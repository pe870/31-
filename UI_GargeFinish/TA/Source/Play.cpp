#include "Play.h"
/*
���e�N�X�`���ǂݍ��݂����������łނ��Ⴍ����d��.
���\�[�X������.
*/

CSceneGameMain::CSceneGameMain(const char* SceneName)
	: CSceneBase(SceneName)
	//���f��.
	, P_1P(nullptr)
	, P_2P(nullptr)
	, Ground(nullptr)
	//�e�N�X�`��.
	, PlayerName1(nullptr)
	, PlayerName2(nullptr)
	//�ϐ�.
	, HP_P1(LIFE_MAX)
	, HP_P2(LIFE_MAX)
	, P1DamageCnt(0)
	, P2DamageCnt(0)
	, BurstCnt1P(0)
	, BurstCnt2P(0)
{
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_1FINE[i] = nullptr;
		P_2FINE[i] = nullptr;
		P_1CAUTION[i] = nullptr;
		P_2CAUTION[i] = nullptr;
		P_1DENGER[i] = nullptr;
		P_2DENGER[i] = nullptr;
	}

	for (int i = 0; i < PlayerMAX; i++)
	{
		P_HPBackGround[i] = nullptr;
		BurstGauge[i] = nullptr;
	}

	for (int i = 0; i < GaugeMax; i++)
	{
		Boost1P[i] = nullptr;
		Boost2P[i] = nullptr;
	}

}

CSceneGameMain::~CSceneGameMain()
{
	//�e�N�X�`���̉��.
	for (int i = 0; i < LIFE_MAX; i++)
	{
		//���C�t.
		SAFE_DELETE(P_1FINE[i]);
		SAFE_DELETE(P_2FINE[i]);
		SAFE_DELETE(P_1CAUTION[i]);
		SAFE_DELETE(P_2CAUTION[i]);
		SAFE_DELETE(P_1DENGER[i]);
		SAFE_DELETE(P_2DENGER[i]);
	}

	for (int i = 0; i < PlayerMAX; i++)
	{
		//���C�t�̔w�i.
		SAFE_DELETE(P_HPBackGround[i]);
		//�u�[�X�g�Q�[�W�g.
		SAFE_DELETE(BurstGauge[i]);

	}
	//�u�[�X�g�Q�[�W.
	for (int i = 0; i < GaugeMax; i++)
	{
		//�Q�[�W�̒��̕�.
		SAFE_DELETE(Boost1P[i]);
		SAFE_DELETE(Boost2P[i]);
	}

	//���O.
	SAFE_DELETE(PlayerName1);
	SAFE_DELETE(PlayerName2);

	//���f���̉��.
	SAFE_DELETE(P_1P);
	SAFE_DELETE(P_2P);
	SAFE_DELETE(Ground);
}

void CSceneGameMain::Control()
{
	P_1P->Action();
	P_2P->Action2();
}

void CSceneGameMain::Action(SceneIndex &Scene)
{
	//���C�t����(����ǉ���ɂ�������).
	if (GetAsyncKeyState(VK_RETURN) & 0x0001){ HP_P1 -= 1; }
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) { HP_P2 -= 1; }

	//���S����.
	if (HP_P1 <= 0) { P_1P->m_DeadFlag = true; }
	if (HP_P2 <= 0) { P_2P->m_DeadFlag = true; }

	//�V�[���ڍs.
	if (P_1P->m_DeadFlag && !P_2P->m_DeadFlag)
	{
		//P1 ���S.
		Scene = SceneIndex::P2WIN;
	}
	else if (!P_1P->m_DeadFlag && P_2P->m_DeadFlag)
	{
		//P2 ���S.
		Scene = SceneIndex::P1WIN;
	}

	//�u�[�X�g�Q�[�W����(1P).
	if (GetAsyncKeyState('B') & 0x8000)
	{
		BurstCnt1P++;
		if (GaugeMax < BurstCnt1P)
		{
			BurstCnt1P = GaugeMax;
		}
	}
	else
	{
		if (0 < BurstCnt1P)
		{
			BurstCnt1P--;
		}
	}

	//�u�[�X�g�Q�[�W����(2P).
	if (GetAsyncKeyState('V') & 0x8000)
	{
		BurstCnt2P++;
		if (GaugeMax < BurstCnt2P)
		{
			BurstCnt2P = GaugeMax;
		}
	}
	else
	{
		if (0 < BurstCnt2P)
		{
			BurstCnt2P--;
		}
	}

}

void CSceneGameMain::Load(claResource *SetUP, DInput *Controll)
{
	
	P_1P = new clsPlayer;
	P_1P->AttachModel(SetUP->GetStaticMesh(enStaticMesh_Player1P));
	P_1P->Init();
	P_1P->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	P_1P->setgamepad(Controll);

	P_2P = new clsPlayer;
	P_2P->AttachModel(SetUP->GetStaticMesh(enStaticMesh_Player2P));
	P_2P->Init();
	P_2P->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	P_2P->setgamepad(Controll);

	Ground = new clsObject;
	Ground->AttachModel(SetUP->GetStaticMesh(enStaticMesh_Ground));
	Ground->SetPosition(D3DXVECTOR3(0.0f, -2.0f, 0.0f));


}

void CSceneGameMain::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{	
	//�t�@�C����.
	LPSTR TexF_Name = nullptr;
	//�Ǎ����X�gNo.
	int ListNo = 0;
	//�^�����킹��.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());

	//�X�v���C�g����ݒ肷��.
	SPRITE_STATE	ss;
	ss.U = 1.0f;
	ss.V = 1.0f;

	//���C�t(�댯�斢�˓�).
	//�����ȉ��ɂȂ�ƐF���ς��.
	ss.Width = 13.0f;
	ss.Height = 30.0f;
	float temp = 14.0f;
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_1FINE[i] = new cls2DTex;
		P_1FINE[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_1FINE[i]->m_vPos = D3DXVECTOR3(76.0f + temp, 5.0f, 0.0f);
		P_1FINE[i]->m_Alpha = 1.0f;

		temp += 14.0f;
	}
	temp = 14.0f;
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_2FINE[i] = new cls2DTex;
		P_2FINE[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_2FINE[i]->m_vPos = D3DXVECTOR3(984.0f + temp, 687.0f,0.0f);
		P_2FINE[i]->m_Alpha = 1.0f;

		temp += 14.0f;
	}
	ListNo++;
	//���C�t�댯��˓��O.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_1CAUTION[i] = new cls2DTex;
		P_1CAUTION[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_1CAUTION[i]->m_vPos = P_1FINE[i]->m_vPos;
		P_1CAUTION[i]->m_Alpha = 1.0f;
	}
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_2CAUTION[i] = new cls2DTex;
		P_2CAUTION[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_2CAUTION[i]->m_vPos = P_2FINE[i]->m_vPos;
		P_2CAUTION[i]->m_Alpha = 1.0f;
	}
	ListNo++;
	//���C�t�댯��˓���.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_1DENGER[i] = new cls2DTex;
		P_1DENGER[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_1DENGER[i]->m_vPos = P_1CAUTION[i]->m_vPos;
		P_1DENGER[i]->m_Alpha = 1.0f;

	}
	for (int i = 0; i < LIFE_MAX; i++)
	{
		P_2DENGER[i] = new cls2DTex;
		P_2DENGER[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_2DENGER[i]->m_vPos = P_2CAUTION[i]->m_vPos;
		P_2DENGER[i]->m_Alpha = 1.0f;
	}
	ListNo++;

	//���C�t�̔w�i(�������ߐݒ�����Ă���).
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	ss.Width = 286.0f;
	ss.Height = 38.0f;
	for (int i = 0; i < PlayerMAX; i++)
	{
		P_HPBackGround[i] = new cls2DTex;
		P_HPBackGround[i]->Init(pDevice, pContext, TexF_Name, ss);
		P_HPBackGround[i]->m_Alpha = 0.8f;
	}
	P_HPBackGround[0]->m_vPos = D3DXVECTOR3(86.0f, 1.0f, 0.0f);
	P_HPBackGround[1]->m_vPos = D3DXVECTOR3(995.0f, 683.0f, 0.0f);
	ListNo++;

	//�e�v���C���[�̖��O(���Ɍ��߂Ȃ����ǂ̃v���C���[�̂��̂��𖾋L).
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	ss.Width = 84.0f;
	ss.Height = 38.0f;
	PlayerName1 = new cls2DTex;
	PlayerName1->Init(pDevice, pContext, TexF_Name, ss);
	PlayerName1->m_vPos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	PlayerName1->m_Alpha = 1.0f;
	ListNo++;

	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	ss.Width = 84.0f;
	ss.Height = 38.0f;
	PlayerName2 = new cls2DTex;
	PlayerName2->Init(pDevice, pContext, TexF_Name, ss);
	PlayerName2->m_vPos = D3DXVECTOR3(910.0f, 683.0f, 0.0f);
	PlayerName2->m_Alpha = 1.0f;
	ListNo++;
	
	//�L�����u�[�X�g�Q�[�W.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	ss.Width = 286.0f;
	ss.Height = 38.0f;
	for (int i = 0; i < PlayerMAX; i++)
	{
		BurstGauge[i] = new cls2DTex;
		BurstGauge[i]->Init(pDevice, pContext, TexF_Name, ss);
		BurstGauge[i]->m_Alpha = 1.0f;
	}
	BurstGauge[0]->m_vPos = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
	BurstGauge[1]->m_vPos = D3DXVECTOR3(994.0f, 644.0f, 0.0f);
	ListNo++;

	//���̃Q�[�W.
	TexF_Name = const_cast<char *>(TexList[ListNo].c_str());
	ss.Width = 2.83f;
	ss.Height = 36.0f;
	float temMp = 1.0f;
	for (int i = 0; i < GaugeMax; i++)
	{
		Boost1P[i] = new cls2DTex;
		Boost1P[i] ->Init(pDevice, pContext, TexF_Name, ss);
		Boost1P[i] ->m_Alpha = 1.0f;
		Boost1P[i] ->m_vPos = D3DXVECTOR3(0.0f + temMp, 41.5f, 0.0f);
		temMp = temMp + 2.83f;
	}

	for (int i = 0; i < GaugeMax; i++)
	{
		Boost2P[i] = new cls2DTex;
		Boost2P[i]->Init(pDevice, pContext, TexF_Name, ss);
		Boost2P[i]->m_Alpha = 1.0f;
		Boost2P[i]->m_vPos = D3DXVECTOR3(711.0f + temMp, 645.5f, 0.0f);
		temMp = temMp + 2.83f;
	}


}

void CSceneGameMain::Draw(D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye)
{
	P_1P->Render(mView, mProj, vLight, vEye);
	P_2P->Render(mView, mProj, vLight, vEye);

	Ground->Render(mView, mProj, vLight, vEye);



	//�e�N�X�`��.
	PlayerName1->Render();
	PlayerName2->Render();

	//���C�t�̕`��ݒ�.
	//20�ȉ��F�΁@10�ȉ��F���F�@5�ȉ��F��.

	//1P�̂��.
	if ( 10 < HP_P1){
		//�ΐF.
		for (int i = 0; i < HP_P1; i++){
			P_1FINE[i]->Render();
		}
	}
	else if (HP_P1 <= 10 &&  3 < HP_P1){
		//���F.
		for (int i = 0; i < HP_P1; i++){

			P_1CAUTION[i]->Render();
		}
	}
	else{
		//�ԐF.
		for (int i = 0; i < HP_P1; i++){
			P_1DENGER[i]->Render();
		}
	}

	//2P.
	if (10 < HP_P2){
		//�ΐF.
		for (int i = 0; i < HP_P2; i++){
			P_2FINE[i]->Render();
		}
	}
	else if (HP_P2 <= 10 && 3 < HP_P2){
		//���F.
		for (int i = 0; i < HP_P2; i++)	{

			P_2CAUTION[i]->Render();
		}
	}
	else{
		//�ԐF.
		for (int i = 0; i < HP_P2; i++){
			P_2DENGER[i]->Render();
		}
	}

	//�u�[�X�g�Q�[�W(���̕�).
	for (int i = 0; i < GaugeMax - BurstCnt1P; i++)
	{
		Boost1P[i]->Render();
	}
	for (int i = 0; i < GaugeMax - BurstCnt2P; i++)
	{
		Boost2P[i]->Render();
	}


	//UI�w�i����.
	for (int i = 0; i < PlayerMAX; i++)
	{
		P_HPBackGround[i]->Render();
		BurstGauge[i]->Render();
	}

	


}

void CSceneGameMain::SetCameraPos(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw)
{
	//�J�����ʒu(���@�̔w�ʂ���)�̐ݒ�.
	P_1P->Camera(vLook, vEye, Yaw);
}
