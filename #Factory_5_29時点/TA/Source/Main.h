#pragma warning(disable:4005)
#pragma warning(disable:4996)

#include <Windows.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3D10.h>
#include "Game.h"
#include "cCommon.h"
#include "Direct3D.h"

//�萔.
#define WND_TITLE	"B-Adventure"
#define APP_NAME	"B-Adventure"



/*************************************************
*	Ҳݸ׽.
**/
class clsMain : public clsGame
{
public:
	clsMain();
	~clsMain(){};

	//����޳�������֐�.
	HRESULT InitWindow(HINSTANCE hInstance,
		INT iX, INT iY, INT iWidth, INT iHeight,LPSTR WindowName);

	LRESULT MsgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam);
private:

};