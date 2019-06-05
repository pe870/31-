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

	//€–SEƒŠƒZƒbƒgˆ—.
	void EnemyDeadProc();


private:
	clsDx9Mesh*		m_pSearchMesh;		//“G‚Ìõ“G”ÍˆÍ.
	BBOX			m_SearchBBox;		//õ“G”ÍˆÍ‚Ì”»’è.
};



#endif