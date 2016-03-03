#include "stdafx.h"
#include "FFT.h"


void ZeroMean(double* waveData,int len)
{
	double ave = 0;
	int i;
	for(i = 0;i < len;i++)
	{
		ave = ave + waveData[i];
		//xprintf("%d",waveData[i]);
	}
	ave = ave/len;
	for(i = 0;i < len;i++)
	{
		waveData[i] = waveData[i] - ave;
	}
}

void ComplexAdd(Complex c1,Complex c2,Complex &cOut)
{
	cOut.real = c1.real + c2.real;
	cOut.img = c1.img + c2.img;
}


void ComplexMulty(Complex c1,Complex c2,Complex &cOut)
{
 	cOut.real= c1.real*c2.real - c1.img*c2.img;
 	cOut.img= c1.real*c2.img + c1.img*c2.real;
}

void ComplexMinus(Complex c1,Complex c2,Complex &cOut)
{
 	cOut.real=c1.real-c2.real;
 	cOut.img=c1.img-c2.img;
}
//复数共轭
void ComplexAdjoint(Complex c1,Complex  &cOut)
{
 	cOut.real=c1.real;
 	cOut.img= -c1.img;
}
//交换两个复数的值
void 	ComplexReplace(Complex *c1,Complex *c2)
{
	Complex temp;
	temp.real = c1->real;
	temp.img = c1->img;
	c1->real = c2->real;
	c1->img = c2->img;
	c2->real = temp.real;		   
	c2->img = temp.img;
}

void  CalFFT(double* waveData,int len,Complex * complexOut)
{
	/* Complex c_final[N_DOTS];*/
	 //wn_compl: 旋转因子
	
	 //Complex *c_mid;
	 //layer:fft变换级数，
	 //data_gap：数据间隔,
	 //p：旋转因子指数;
	 //rotation_count:旋转因子的个数，
	 /*zeroMean(waveData,len);*/
	 for(int i = 0;i < len; i++)
	 {
	 	complexOut[i].real = waveData[i];
		complexOut[i].img = 0;
	 }
	 ReverseComplex(complexOut,len);   //进行原位运算
	 int m_power = M_POWER; 	 //m_power：数据的1<<m_power == 数据len
	 for(int layer = 1;layer <= m_power; layer++)
	 {
	 	 int data_gap = 1<< (layer - 1);     //数据间隔
		 for(int rotation_count = 0;rotation_count<= (data_gap -1);rotation_count++)
		 {
		 	int p = rotation_count*(1<<(m_power - layer));
			double theta = 2*PI*p/len;
            Complex wn_compl;
			wn_compl.real = cos(theta);
			wn_compl.img = -sin(theta);
			for(int k = rotation_count;k<= (len-1); k += 1<< layer)
			{
				int j = k + data_gap;
				Complex temp_compl;
				ComplexMulty(complexOut[j],wn_compl,temp_compl);
				ComplexMinus(complexOut[k], temp_compl,complexOut[j]);
			 	ComplexAdd(complexOut[k], temp_compl,complexOut[k]);
			}
		 }
	 }
	/* return c_final;*/
}

void  ReverseComplex(Complex* c,int len)
{
	int i,j,n1,k,n;
	//Complex temp;
	int times = 0;
	n1 = len -1;
	n = len;
	
	for(j = 0,i = 0;i < n1;i++)
	{
		times++;
		if(i < j)
		{
			ComplexReplace(&c[i],&c[j]);
		}
		k = n>>1;
		while(k<(j+1))
		{
			j = j - k;
			k = k>>1;
		}
		j = j + k;
	}
	//return c;
}

 //进行FFT变换 滤波 撷取有用部分 输出部分 
void  FFT(double* pWaveDataIn,double* pFFTOut,int iLen)
{
    Complex* pComplexOut = new Complex[DATALENGTH];
    if(pComplexOut == NULL)
	{
		MessageBox(NULL,TEXT("分配内存失败，内存不足"),TEXT("动态存储"),MB_OK);
        return;
	}
    CalFFT(pWaveDataIn,iLen,pComplexOut);
    
	for(int i = 341; i < 3414; i++) //只计算1K到10K频谱;16438*(1/48~10/48)
	{ 
		//double real = pComplexOut[i].real*pComplexOut[i].real;
	 //   double img = pComplexOut[i].img*pComplexOut[i].img;
	 //   pFFTOut[i-341] = (real + img)/DATALENGTH; //sqrt(m+n)/;
        CalPowerSpectrum(pComplexOut[i],pFFTOut+i-341);  //计算能量谱密度
	}
	if(pComplexOut != NULL)
	{
		delete [] pComplexOut;
		pComplexOut = NULL;
	}
	int t_iFilterTimes = 5;
	while(t_iFilterTimes--)    //5次滤波
    Firlter(pFFTOut);
}

//滤波方式 适当选择 先用最小二乘滤波好了 以后再说
void  Firlter(double* pFFTInOut, int iLen)
{
	for(int i=4;i<iLen-4;i++)   //9点滑动平滑
		pFFTInOut[i]=((-21)*pFFTInOut[i-4]+14*pFFTInOut[i-3]+39*pFFTInOut[i-2]+54*pFFTInOut[i-1]+59*pFFTInOut[i]+54*pFFTInOut[i+1]+39*pFFTInOut[i+2]+14*pFFTInOut[i+1]+(-21)*pFFTInOut[i+2])/231;
}

inline void CalPowerSpectrum(Complex &c,double *pOut)
{
	//除以DATALENGTH只是数据太大想变小点而已
	/*double real = c.real/DATALENGTH;
    double img =  c.img/DATALENGTH;
    *pOut = real*real + img*img;*/
	*pOut = (c.real*c.real + c.img*c.img)/DATALENGTH;
}
