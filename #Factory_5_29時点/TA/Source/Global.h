#ifndef GLOBAL_H	//�ݸٰ�޶ް��.
#define GLOBAL_H

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���. 4005:�Ē�`.
#pragma warning(disable:4005)

#include <Windows.h>
#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3D10.h>

//ײ����.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )


//�萔.
#define WND_W	1280	//����޳��.
#define WND_H	720		//����޳����.

//std::���Ȃ�.
using namespace std;


enum class SceneIndex
{
	Nothing = -1,
	TITLE = 0,
	MANUAL = 1,
	PLAY = 2,
	P1WIN = 3,
	P2WIN = 4,

	Start = TITLE,
	End = P2WIN,
};


#endif//#ifndef GLOBAL_H
