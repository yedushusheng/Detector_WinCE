#ifndef __SCT__GLOBAL_sdh_3dsgf_saghj_HHH
#define __SCT__GLOBAL_sdh_3dsgf_saghj_HHH
//#include <WinDef.h>


/***********����������*******/
#define PI  3.14159265358979323846
#define MY_BACKCOLOR  RGB(177,205,181)

#define DATALENGTH      16384    //ԭʼ���ݳ���
#define FFTDATALENGTH   3073     //(16384*10/48-16384/48)  ����ȡ1-10kHz���ȵ�����



#define LEFTMARGIN    33
#define TOPMARGIN     5
#define RIGHTMARGIN   5
#define BOTTOMMARGIN  28






typedef unsigned long DWORD;

/***********����������*******/

/***********ȫ�ֽṹ��������*******/
//typedef struct _Complex{
//	double real;
//	double img;
//}Complex;

typedef struct _WaveData{
	char szFileName[256];
	void* ptr[2];
	//void* ptr_cs;  //�ٽ���ָ��
}WaveData;

////msg�ṹ������
//struct MessageMap{
//	UINT message;
//	LONG (*fun)(HWND,UINT,WPARAM,LPARAM);
//}MESSAGEMAP;

/***********ȫ�ֽṹ��������*******/

/***********ȫ�ֱ���������*******/
//HINSTANCE g_hInst;   //������Ψһʵ��

/***********ȫ�ֱ���������*******/

/***********����������*******/
#define dim(x)     (sizeof(x)/sizeof(x[0]))


/***********ȫ�ֺ���������*******/

double   MedianA(double *pIn,int length);   //�ҵ�������м�ֵ
double   MaxA(double *pIn,int length);     //�ҵ���������ֵ
double   MinA(double *pIn,int length);     //�ҵ������������Сֵ
void     MinAndMax(double *pIn,int length,double &min,double &max);   //�ֱ��ҵ������������Сֵ
int      Comparedouble(const void *pval1, const void *pval2);
CString  DoubleToScientNum(double);
CString  GetFileName(CString szPathName);

long nextPow2(long inputN);
int Pow10(int index);

#endif