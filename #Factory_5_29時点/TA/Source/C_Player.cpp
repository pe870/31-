#include "C_Player.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

//定数.
const int	stop = 0;
const int	attackcntflg = 50;			//攻撃時間.

const float acc = 0.011f;				//加速度.
const float deceleration = 0.2f;		//摩擦係数.
const float upper_acclimit = 0.08f;		//最大加速度.
const float lower_acclimit = -0.08f;	//最小加速度.

clsPlayer::clsPlayer()
: left_key(false)
, right_key(false)
, up_key(false)
, down_key(false)
, junp_key(false)
, atk_key(false)
, OnSquare(false)
, OnSquareM(false)
, OnUpDownL(false)
, OnUpDownR(false)
, DeadLineReload(false)
, m_Ui(true)
, Startbutton(false)
{

}

void clsPlayer::Init()
{
	//SetPosition(D3DXVECTOR3(2.7f, 0.5f, -5.7f));
	m_DeadFlag = false;
	//InitBBox();
	//InitSphere();
}

void clsPlayer::Action()
{
	//コントロール入力情報更新
	m_tclsDInput->UpdateInputState();

	//自機移動 Dx9Meshに有.
	//右に移動
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_R))
	{
		m_acc.x += acc;
	}
	//左に移動
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_L))
	{
		m_acc.x -= acc;
	}
	//止まっている時
	else if (m_acc.x >= stop)
	{
		m_acc.x -= m_acc.x * deceleration;
		if (m_acc.x < stop) m_acc.x = stop;
	}
	else if (m_acc.x <= stop)
	{
		m_acc.x -= m_acc.x * deceleration;
		if (m_acc.x > stop) m_acc.x = stop;
	}
	//前に移動
	if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_U))
	{
		m_acc.z += acc;
	}
	//手前に移動
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_D))
	{
		m_acc.z -= acc;
	}
	//止まっている時
	else if (m_acc.z >= stop)
	{
		m_acc.z -= m_acc.z * deceleration;
		if (m_acc.z < stop) m_acc.z = stop;
	}
	else if (m_acc.z <= stop)
	{
		m_acc.z -= m_acc.z * deceleration;
		if (m_acc.z > stop) m_acc.z = stop;
	}

	//コントローラーで2ボタン押しはできる(覚醒コマンド：OK).
	if (m_tclsDInput->IsPressKey(enPkey_02) && m_tclsDInput->IsPressKey(enPkey_04))
	{
		MessageBox(NULL, " 2つボタン押した ", "CHECK", MB_OK);
	}

	//加速度処理
	if (m_acc.x >  upper_acclimit) m_acc.x = m_acc.x = upper_acclimit;
	if (m_acc.x <  lower_acclimit) m_acc.x = m_acc.x = lower_acclimit;
	if (m_acc.z >  upper_acclimit) m_acc.z = m_acc.z = upper_acclimit;
	if (m_acc.z <  lower_acclimit) m_acc.z = m_acc.z = lower_acclimit;

	//加速度を足す
	m_vPos.x += m_acc.x;
	//m_vPos.y += m_acc.y;
	m_vPos.z += m_acc.z;

}

void clsPlayer::Action2()
{

	//コントロール入力情報更新
	m_tclsDInput->UpdateInputState();

	//自機移動 Dx9Meshに有.
	//右に移動
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_RR))
	{
		m_acc.x += acc;
	}
	//左に移動
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_LR))
	{
		m_acc.x -= acc;
	}
	//止まっている時
	else if (m_acc.x >= stop)
	{
		m_acc.x -= m_acc.x * deceleration;
		if (m_acc.x < stop) m_acc.x = stop;
	}
	else if (m_acc.x <= stop)
	{
		m_acc.x -= m_acc.x * deceleration;
		if (m_acc.x > stop) m_acc.x = stop;
	}
	//前に移動
	if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_UR))
	{
		m_acc.z += acc;
	}
	//手前に移動
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_DR))
	{
		m_acc.z -= acc;
	}
	//止まっている時
	else if (m_acc.z >= stop)
	{
		m_acc.z -= m_acc.z * deceleration;
		if (m_acc.z < stop) m_acc.z = stop;
	}
	else if (m_acc.z <= stop)
	{
		m_acc.z -= m_acc.z * deceleration;
		if (m_acc.z > stop) m_acc.z = stop;
	}

	//加速度処理
	if (m_acc.x > upper_acclimit) m_acc.x = m_acc.x = upper_acclimit;
	if (m_acc.x < lower_acclimit) m_acc.x = m_acc.x = lower_acclimit;
	if (m_acc.z > upper_acclimit) m_acc.z = m_acc.z = upper_acclimit;
	if (m_acc.z < lower_acclimit) m_acc.z = m_acc.z = lower_acclimit;

	//加速度を足す
	m_vPos.x += m_acc.x;
	//m_vPos.y += m_acc.y;
	m_vPos.z += m_acc.z;

}

//カメラ
void clsPlayer::Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw)
{
	vLook = vEye =m_vPos;
	Yaw = m_Yaw;
}

