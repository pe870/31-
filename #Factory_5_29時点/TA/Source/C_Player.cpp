#include "C_Player.h"
const char	MODEL_NAME[] = "Shader\\Mesh.hlsl";

//�萔.
const int	stop = 0;
const int	attackcntflg = 50;			//�U������.

const float acc = 0.011f;				//�����x.
const float deceleration = 0.2f;		//���C�W��.
const float upper_acclimit = 0.08f;		//�ő�����x.
const float lower_acclimit = -0.08f;	//�ŏ������x.

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
	//�R���g���[�����͏��X�V
	m_tclsDInput->UpdateInputState();

	//���@�ړ� Dx9Mesh�ɗL.
	//�E�Ɉړ�
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_R))
	{
		m_acc.x += acc;
	}
	//���Ɉړ�
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_L))
	{
		m_acc.x -= acc;
	}
	//�~�܂��Ă��鎞
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
	//�O�Ɉړ�
	if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_U))
	{
		m_acc.z += acc;
	}
	//��O�Ɉړ�
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_D))
	{
		m_acc.z -= acc;
	}
	//�~�܂��Ă��鎞
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

	//�R���g���[���[��2�{�^�������͂ł���(�o���R�}���h�FOK).
	if (m_tclsDInput->IsPressKey(enPkey_02) && m_tclsDInput->IsPressKey(enPkey_04))
	{
		MessageBox(NULL, " 2�{�^�������� ", "CHECK", MB_OK);
	}

	//�����x����
	if (m_acc.x >  upper_acclimit) m_acc.x = m_acc.x = upper_acclimit;
	if (m_acc.x <  lower_acclimit) m_acc.x = m_acc.x = lower_acclimit;
	if (m_acc.z >  upper_acclimit) m_acc.z = m_acc.z = upper_acclimit;
	if (m_acc.z <  lower_acclimit) m_acc.z = m_acc.z = lower_acclimit;

	//�����x�𑫂�
	m_vPos.x += m_acc.x;
	//m_vPos.y += m_acc.y;
	m_vPos.z += m_acc.z;

}

void clsPlayer::Action2()
{

	//�R���g���[�����͏��X�V
	m_tclsDInput->UpdateInputState();

	//���@�ړ� Dx9Mesh�ɗL.
	//�E�Ɉړ�
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_RR))
	{
		m_acc.x += acc;
	}
	//���Ɉړ�
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_LR))
	{
		m_acc.x -= acc;
	}
	//�~�܂��Ă��鎞
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
	//�O�Ɉړ�
	if (GetAsyncKeyState(VK_UP) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_UR))
	{
		m_acc.z += acc;
	}
	//��O�Ɉړ�
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || m_tclsDInput->IsPressKey(enPkey_DR))
	{
		m_acc.z -= acc;
	}
	//�~�܂��Ă��鎞
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

	//�����x����
	if (m_acc.x > upper_acclimit) m_acc.x = m_acc.x = upper_acclimit;
	if (m_acc.x < lower_acclimit) m_acc.x = m_acc.x = lower_acclimit;
	if (m_acc.z > upper_acclimit) m_acc.z = m_acc.z = upper_acclimit;
	if (m_acc.z < lower_acclimit) m_acc.z = m_acc.z = lower_acclimit;

	//�����x�𑫂�
	m_vPos.x += m_acc.x;
	//m_vPos.y += m_acc.y;
	m_vPos.z += m_acc.z;

}

//�J����
void clsPlayer::Camera(D3DXVECTOR3 &vLook, D3DXVECTOR3 &vEye, float Yaw)
{
	vLook = vEye =m_vPos;
	Yaw = m_Yaw;
}

