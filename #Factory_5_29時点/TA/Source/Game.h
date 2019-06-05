#ifndef GAME_H
#define GAME_H

#include "cCommon.h"
#include "Global.h"

#include "DInput.h"

#include "Direct3D.h"
#include "SceneManager.h"

#include "DX9Mesh.h"

#include "DebugText.h"

#include "Sound.h"


#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.


//�O���f�[�^.
//���W�ǂݍ��݃f�[�^�\����.
struct ObjectPosList
{
	//float�ō��W��ݒ肵�Ă���̂�float�ɍ��킹��.
	float m_ePosX;
	float m_ePosY;
	float m_ePosZ;
};

struct Data
{
	D3DXVECTOR3 stPos;
	float m_eScalef;
	D3DXVECTOR4 PosSca;
};

//�\����.
//�J�������.
struct CAMERA
{
	D3DXVECTOR3			vEye;					//�J�����ʒu.
	D3DXVECTOR3			vLook;					//�J���������ʒu.
	float				Yaw;					//Y��]��.
	D3DXMATRIX			mRotation;				//��]�s��.
};

class clsGame
{
public:
	clsGame();
	~clsGame();

	void						Loop();

	void						AppMain();

	void						Render();
	//�ŏ��̃f�[�^�Ǎ��p.
	void						LoadData();

	//��׊֐�.
	void						Camera();
	//��ۼު���݊֐�.
	void						Proj();

	//���f�����\�[�X�p.
	claResource*				m_pResource;
	//�V�[��.
	CSceneManager				*pSceneMgr;

	HWND						m_hWnd;
	//�R���g���[���[�ݒ�.
	DInput*						m_pCtrler;
	//Direct3D����.
	clsDirect3D*				m_pDirect3D;

public:
	//�V�[���̏��.
	SceneIndex index = SceneIndex::TITLE;

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	ID3D11SamplerState*			m_pSampleLinear;		//ø����̻���� ø����Ɋe��̨����������.
	ID3D11ShaderResourceView*	m_pTexture;				//ø���.
	CAMERA						m_Camera;				//�J�������.
	D3DXMATRIX					m_mView;				//�r���[(�J�����s��).
	D3DXMATRIX					m_mProj;				//�v���W�F�N�V�����s��.
	D3DXVECTOR3					m_vLight;				//ײĂ̕���.

	clsDx9Mesh*					m_pClsDx9Mesh;			//Dx9ү���׽.

	clsDebugText*				m_ptDebugText;			//�f�o�b�O�e�L�X�g.

};


#endif//#ifndef GAME_H