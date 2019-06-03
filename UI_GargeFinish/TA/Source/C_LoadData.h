#ifndef C_LOADDATA_H
#define	C_LOADDATA_H

#pragma warning(disable:4996)


#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Charactor.h"

class clsLoadData : public clsChara
{
public:
	//ファイル名と行数.
	D3DXVECTOR3 LoadData(LPCTSTR fileName,int Line);
	D3DXVECTOR4 LoadDataScale(LPCTSTR fileName, int Line);
protected:
	D3DXVECTOR3 Convert_float(float x, float y, float z);
	D3DXVECTOR4 Convert_float(float x, float y, float z,float w);

private:

};

#endif //#ifndef C_LOADDATA_H
