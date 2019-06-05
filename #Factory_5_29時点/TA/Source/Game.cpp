#pragma warning(disable:4005)
#pragma warning(disable:4305)
#pragma warning(disable:4996)

#include "Game.h"

clsGame::clsGame()
: m_pDevice(nullptr)
, m_pContext(nullptr)
, m_pSampleLinear(nullptr)
, m_pTexture(nullptr)
, m_Camera()
, m_mView()
, m_mProj()
, m_vLight()
, m_pClsDx9Mesh(nullptr)
, m_pResource(nullptr)
, pSceneMgr(nullptr)
{
	m_Camera.vEye = D3DXVECTOR3(0.0f, 3.7f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLight = D3DXVECTOR3(0.3f, 1.2f, -2.0f);
};

clsGame::~clsGame()
{
	SAFE_DELETE(m_ptDebugText);
	//�R���g���[�����.
	delete m_pCtrler;
	//�V�[�����.
	SAFE_DELETE(pSceneMgr);

	//���ق̉��.
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);

	//���\�[�X�̊J��.
	SAFE_DELETE(m_pResource);

	//Direct3D��޼ު�Ẳ��.
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

//�G��Ȃ���.
void clsGame::Loop()
{
	//3D�̍쐬.
	m_pDirect3D = new clsDirect3D;
	m_pDirect3D->Create3D(m_hWnd);
	//�K�v�ȏ��̎擾.
	m_pDevice = m_pDirect3D->GetDevice();
	m_pContext = m_pDirect3D->GetDeviceContext();

	m_pResource = new claResource;
	m_pResource->Init(m_hWnd, m_pDevice, m_pContext);
	m_pResource->LoadStaticMeshAll();
	
	pSceneMgr = new CSceneManager();

	LoadData();

	//--------------�ڰ�ڰĒ�������.----------------------------//

	float Rate = 0.0f;	//ڰ�.
	float FPS = 60.0f;	//FPS�l.
	DWORD sync_old = timeGetTime();	//�ߋ�����.
	DWORD sync_now;					//���ݎ���.
	//���ԏ����ׁ̈A�ŏ��P�ʂ�1�ؕb�ɕύX.
	timeBeginPeriod(1);

	//----------------------------------------------------------//

	//ү����ٰ��.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		sync_now = timeGetTime();//���ݎ��Ԃ��擾.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Rate = 1000.0f / FPS;	//���z���Ԃ��Z�o.
		if (sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;//���ݎ��Ԃɒu������.

			AppMain();
		}
	}
	//���ع���݂̏I��.
	timeEndPeriod(1);
}

//Ҳݏ���.
void clsGame::AppMain()
{
	/////////////////////////////////////
	//*********************************//
	//*		��@�΁@�G�@��@��        *//
	//*********************************//
	/////////////////////////////////////

	//Update��ʂ��Ă���index���ς���Ă��Ȃ����m�F.
	//�ς���Ă�����t���O�𗧂āA���̃V�[���ֈڍs����.
	if (pSceneMgr->CheckingScene == true)
	{
		pSceneMgr->SetNextScene(index);				//����ւ������̃V�[���ɂ���.
		pSceneMgr->TransitionScene();				//������V�[����j�����Ď��̃V�[���𐶐�.
		pSceneMgr->Load(m_pResource, m_pCtrler);	//���f�����̓Ǎ�.
		pSceneMgr->Load(m_pDevice, m_pContext);		//�e�N�X�`�����̓Ǎ�.

		pSceneMgr->CheckingScene = false;
	}

	//�{��.
	pSceneMgr->Update((index));
	//�J�����ʒu�̐ݒ�.
	pSceneMgr->SetCameraPos(m_Camera.vEye, m_Camera.vLook, m_Camera.Yaw);
	//���f���E�e�N�X�`���`��.
	Render();
}

void clsGame::LoadData()
{
	//���f�����̓Ǎ�(�N�����̏���Ǎ�).
	pSceneMgr->Load(m_pResource, m_pCtrler);
	//�e�N�X�`�����̓Ǎ�(�N�����̏���Ǎ�).
	pSceneMgr->Load(m_pDevice, m_pContext);

#ifdef _DEBUG
	//�f�o�b�O�e�L�X�g�̏�����.
	m_ptDebugText = new clsDebugText;
	D3DXVECTOR4 vColor(1.0f, 0.0f, 0.0f, 1.0f);
	if (FAILED(m_ptDebugText->Init(m_pContext, WND_W, WND_H, 50.0f, vColor)))
	{ return; }
#endif

}

void clsGame::Render()
{
	//�R�����g���ǉ�����Ă邩�m�F����.
	//��ʸر.
	m_pDirect3D->SetBuffer();
	//�J�����ƃv���W�F�N�V�����̐ݒ�.
	Camera();
	Proj();
	pSceneMgr->Draw(m_mView, m_mProj, m_vLight, m_Camera.vEye);
	//��̧������(�F����).
	m_pDirect3D->SetBlend(true);
	m_pDirect3D->RenderPresent();
}

void clsGame::Camera()
{
	//Y����]�s��.
	D3DXMatrixRotationY(&m_Camera.mRotation, m_Camera.Yaw);
	//���x�N�g����p�ӂ���.
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);
	//�J�����ʒu�E�����ʒu�𒲐�.
	m_Camera.vEye -= vecAxisZ * 6.0f;		//���@�̔w��.
	m_Camera.vLook += vecAxisZ * 3.0f;		//���@�̑O��.
	//���ꂼ��̍�������.
	m_Camera.vEye.y += 3.5f;				//���@�̔w��.
	m_Camera.vLook.y += 0.1f;				//���@�̑O��.
	//�ޭ�(���)�ϊ�.
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//����ʒu.
	//(out)�ޭ��v�Z����.
	D3DXMatrixLookAtLH(&m_mView,&m_Camera.vEye, &m_Camera.vLook, &vUpVec);
}

void clsGame::Proj()
{
	//��ۼު����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,D3DX_PI / 4.0,(FLOAT)WND_W / (FLOAT)WND_H,0.1f,100.0f);
}
