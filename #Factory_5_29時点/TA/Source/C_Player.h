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

	/****************自機制御関連******************/


	//ゲームパッド初期化.
	void setgamepad(DInput* p)
	{
		if (p != NULL)
		{
			m_tclsDInput = p;
		}
	}


	//操作関連
	bool						left_key;
	bool						right_key;
	bool						up_key;
	bool						down_key;
	bool						junp_key;
	bool						atk_key;

	bool						m_Ui;					//操作説明ON/OFF.
	bool						Startbutton;
	int							StartCnt;
	bool						OnSquare;				//スクエア足場に乗っている時true.
	bool						OnSquareM;				//スクエア足場に乗っている時true.
	bool						OnUpDownL;				//上下足場に乗っている時true.
	bool						OnUpDownR;				//上下足場に乗っている時true.
	bool						DeadLineReload;			//スタート位置false、上に行くとtrue.


private:


	class DInput*  m_tclsDInput;

protected:

	D3DXVECTOR3					m_acc;		//加速
	D3DXVECTOR3					m_old;

};

#endif