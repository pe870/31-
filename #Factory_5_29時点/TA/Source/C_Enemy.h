#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include <stdio.h>
#include <math.h>

#include "Global.h"
#include "DX9Mesh.h"
#include "cCommon.h"
#include "Charactor.h"
#include "C_Player.h"


class clsEnemy : public clsChara
{
public:
	clsEnemy();
	virtual ~clsEnemy(){};

	void Init();
	void Action();

	//���S�E���Z�b�g����.
	void EnemyDeadProc();


private:
	clsDx9Mesh*		m_pSearchMesh;		//�G�̍��G�͈�.
	BBOX			m_SearchBBox;		//���G�͈͂̔���.
};



#endif