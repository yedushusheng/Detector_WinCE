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
//��������
void ComplexAdjoint(Complex c1,Complex  &cOut)
{
 	cOut.real=c1.real;
 	cOut.img= -c1.img;
}
//��������������ֵ
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
	 //wn_compl: ��ת����
	
	 //Complex *c_mid;
	 //layer:fft�任������
	 //data_gap�����ݼ��,
	 //p����ת����ָ��;
	 //rotation_count:��ת���ӵĸ�����
	 /*zeroMean(waveData,len);*/
	 for(int i = 0;i < len; i++)
	 {
	 	complexOut[i].real = waveData[i];
		complexOut[i].img = 0;
	 }
	 ReverseComplex(complexOut,len);   //����ԭλ����
	 int m_power = M_POWER; 	 //m_power�����ݵ�1<<m_power == ����len
	 for(int layer = 1;layer <= m_power; layer++)
	 {
	 	 int data_gap = 1<< (layer - 1);     //���ݼ��
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

 //����FFT�任 �˲� ߢȡ���ò��� ������� 
void  FFT(double* pWaveDataIn,double* pFFTOut,int iLen)
{
    Complex* pComplexOut = new Complex[DATALENGTH];
    if(pComplexOut == NULL)
	{
		MessageBox(NULL,TEXT("�����ڴ�ʧ�ܣ��ڴ治��"),TEXT("��̬�洢"),MB_OK);
        return;
	}
    CalFFT(pWaveDataIn,iLen,pComplexOut);
    
	for(int i = 341; i < 3414; i++) //ֻ����1K��10KƵ��;16438*(1/48~10/48)
	{ 
		//double real = pComplexOut[i].real*pComplexOut[i].real;
	 //   double img = pComplexOut[i].img*pComplexOut[i].img;
	 //   pFFTOut[i-341] = (real + img)/DATALENGTH; //sqrt(m+n)/;
        CalPowerSpectrum(pComplexOut[i],pFFTOut+i-341);  //�����������ܶ�
	}
	if(pComplexOut != NULL)
	{
		delete [] pComplexOut;
		pComplexOut = NULL;
	}
	int t_iFilterTimes = 5;
	while(t_iFilterTimes--)    //5���˲�
    Firlter(pFFTOut);
}

//�˲���ʽ �ʵ�ѡ�� ������С�����˲����� �Ժ���˵
void  Firlter(double* pFFTInOut, int iLen)
{
	for(int i=4;i<iLen-4;i++)   //9�㻬��ƽ��
		pFFTInOut[i]=((-21)*pFFTInOut[i-4]+14*pFFTInOut[i-3]+39*pFFTInOut[i-2]+54*pFFTInOut[i-1]+59*pFFTInOut[i]+54*pFFTInOut[i+1]+39*pFFTInOut[i+2]+14*pFFTInOut[i+1]+(-21)*pFFTInOut[i+2])/231;
}

inline void CalPowerSpectrum(Complex &c,double *pOut)
{
	//����DATALENGTHֻ������̫�����С�����
	/*double real = c.real/DATALENGTH;
    double img =  c.img/DATALENGTH;
    *pOut = real*real + img*img;*/
	*pOut = (c.real*c.real + c.img*c.img)/DATALENGTH;
}
