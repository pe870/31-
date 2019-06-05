#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <stdio.h>
#include <math.h>

#include "Global.h"
#include "DX9Mesh.h"
#include "Charactor.h"
#include "DInput.h"
#include "DebugText.h"


class clsPlayer : public clsChara
{
public:
	clsPlayer();
	~clsPlayer(){};

	void Init();

	void Action();
	void Action2();

	void Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float yaw);

	/****************���@����֘A******************/


	//�Q�[���p�b�h������.
	void setgamepad(DInput* p)
	{
		if (p != NULL)
		{
			m_tclsDInput = p;
		}
	}


	//����֘A
	bool						left_key;
	bool						right_key;
	bool						up_key;
	bool						down_key;
	bool						junp_key;
	bool						atk_key;

	bool						m_Ui;					//�������ON/OFF.
	bool						Startbutton;
	int							StartCnt;
	bool						OnSquare;				//�X�N�G�A����ɏ���Ă��鎞true.
	bool						OnSquareM;				//�X�N�G�A����ɏ���Ă��鎞true.
	bool						OnUpDownL;				//�㉺����ɏ���Ă��鎞true.
	bool						OnUpDownR;				//�㉺����ɏ���Ă��鎞true.
	bool						DeadLineReload;			//�X�^�[�g�ʒufalse�A��ɍs����true.


private:


	class DInput*  m_tclsDInput;

protected:

	D3DXVECTOR3					m_acc;		//����
	D3DXVECTOR3					m_old;

};

#endif