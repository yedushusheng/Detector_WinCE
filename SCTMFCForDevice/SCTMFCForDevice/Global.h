#ifndef __SCT__GLOBAL_sdh_3dsgf_saghj_HHH
#define __SCT__GLOBAL_sdh_3dsgf_saghj_HHH
//#include <WinDef.h>


/***********常量定义区*******/
#define PI  3.14159265358979323846
#define MY_BACKCOLOR  RGB(177,205,181)

#define DATALENGTH      16384    //原始数据长度
#define FFTDATALENGTH   3073     //(16384*10/48-16384/48)  这里取1-10kHz长度的数据



#define LEFTMARGIN    33
#define TOPMARGIN     5
#define RIGHTMARGIN   5
#define BOTTOMMARGIN  28






typedef unsigned long DWORD;

/***********常量定义区*******/

/***********全局结构体声明区*******/
//typedef struct _Complex{
//	double real;
//	double img;
//}Complex;

typedef struct _WaveData{
	char szFileName[256];
	void* ptr[2];
	//void* ptr_cs;  //临界区指针
}WaveData;

////msg结构体声明
//struct MessageMap{
//	UINT message;
//	LONG (*fun)(HWND,UINT,WPARAM,LPARAM);
//}MESSAGEMAP;

/***********全局结构体声明区*******/

/***********全局变量声明区*******/
//HINSTANCE g_hInst;   //主程序唯一实例

/***********全局变量声明区*******/

/***********函数定义区*******/
#define dim(x)     (sizeof(x)/sizeof(x[0]))


/***********全局函数定义区*******/

double   MedianA(double *pIn,int length);   //找到数组的中间值
double   MaxA(double *pIn,int length);     //找到数组的最大值
double   MinA(double *pIn,int length);     //找到数组的最大和最小值
void     MinAndMax(double *pIn,int length,double &min,double &max);   //分别找到数组的最大和最小值
int      Comparedouble(const void *pval1, const void *pval2);
CString  DoubleToScientNum(double);
CString  GetFileName(CString szPathName);

long nextPow2(long inputN);
int Pow10(int index);

#endif