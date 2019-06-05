#include "C_LoadData.h"

//�傫�����S�ē�����.
D3DXVECTOR3 clsLoadData::LoadData(LPCTSTR fileName, int Line)
{
	FILE *fp;
	D3DXVECTOR3 PosS = {0,0,0};
	error_status_t err;
	err = fopen_s(&fp, fileName, "r");

	//�G���[�`�F�b�N.
	if (err != 0)
	{
		MessageBox(NULL, "�f�[�^�Ǎ����s", "error", MB_OK);
	}

	//�s��̓ǂݍ���.
	for (int i = 0; i < Line; i++)
	{
		if (fscanf(fp, "%f,%f,%f", &PosS.x, &PosS.y, &PosS.z) == EOF)
		{
			MessageBox(NULL, "�f�[�^�擾���s", "error", MB_OK);

		}
		//�ǂݍ��񂾂�D3DXVECTOR3����float�֕ϊ�����.
		Convert_float(PosS.x, PosS.y, PosS.z);
	}

	//�J�����t�@�C�������.
	fclose(fp);


	return PosS;
}

//�z�u�ꏊ�ɂ���đ傫�����ς�����.
D3DXVECTOR4 clsLoadData::LoadDataScale(LPCTSTR fileName, int Line)
{
	FILE *fp;
	D3DXVECTOR4 PosS = { 0, 0, 0 ,0 };
	error_status_t err;
	err = fopen_s(&fp, fileName, "r");

	//�G���[�`�F�b�N.
	if (err != 0)
	{
		MessageBox(NULL, "�f�[�^�Ǎ����s", "error", MB_OK);
	}

	//�s��̓ǂݍ���.
	for (int i = 0; i < Line; i++)
	{
		if (fscanf(fp, "%f,%f,%f,%f", &PosS.x, &PosS.y, &PosS.z,&PosS.w) == EOF)
		{
			MessageBox(NULL, "�f�[�^�擾���s", "error", MB_OK);

		}
		//�ǂݍ��񂾂�D3DXVECTOR3����float�֕ϊ�����.
		Convert_float(PosS.x, PosS.y, PosS.z,PosS.w);
	}

	//�J�����t�@�C�������.
	fclose(fp);


	return PosS;
}

//���l�ϊ��@(float�^).
D3DXVECTOR3 clsLoadData::Convert_float(float x, float y, float z)
{
	//����f�[�^.
	D3DXVECTOR3 tempData;

	tempData.x = x;
	tempData.y = y;
	tempData.z = z;

	return tempData;
}

//���l�ϊ��@(float�^���W+float�^�傫��).
D3DXVECTOR4 clsLoadData::Convert_float(float x, float y, float z,float w)
{
	//����f�[�^.
	D3DXVECTOR4 tempData;

	tempData.x = x;
	tempData.y = y;
	tempData.z = z;
	tempData.w = w;
	return tempData;
}
