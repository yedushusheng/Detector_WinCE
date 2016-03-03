#ifndef __SCT_FFT_H__SJKDGHJKF_SDSDG2F_5FGN34_RETH3__INCLUDED_
#define __SCT_FFT_H__SJKDGHJKF_SDSDG2F_5FGN34_RETH3__INCLUDED_


#include "Global.h"
//#define  PI      3.1415927
#define  M_POWER       14	//数据数目1<<M_POWER 就是相当于这么多个采样点
#define  N_DOTS  1<<M_POWER 

typedef struct _Complex{
	double real;
	double img;
}Complex;

void 	ZeroMean(double* waveData,int len); 
void    ComplexAdd(Complex c1,Complex c2,Complex &cOut);
void    ComplexMulty(Complex c1,Complex c2,Complex &cOut);
void    ComplexMinus(Complex c1,Complex c2,Complex &cOut);
void    ComplexAdjoint(Complex c1,Complex &cOut);
void 	ComplexReplace(Complex *c1,Complex *c2);
void    CalFFT(double* waveData,int len,Complex * complexOut);
void    ReverseComplex(Complex* c,int len);
void    FFT(double* pWaveDataIn,double* pFFTOut,int iLen = DATALENGTH);   //进行FFT变换 滤波 撷取有用部分 输出部分 
void    Firlter(double* pFFTInOut, int iLen = FFTDATALENGTH);                  //滤波方式 适当选择
inline void CalPowerSpectrum(Complex &c,double *pOut);


#endif