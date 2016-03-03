//#include "stdafx.h"
//#include "FFT.h"
//
//#include "monitor.h"
//�Բ������ݾ�ֵ��
//void zeroMean(double* waveData,int len)
//{
//	double ave = 0;
//	int i;
//	for(i = 0;i < len;i++)
//	{
//		ave = ave + waveData[i];
//		//xprintf("%d",waveData[i]);
//	}
//	ave = ave/len;
//	for(i = 0;i < len;i++)
//	{
//		waveData[i] = waveData[i] - ave;
//	}
//}
//
//Complex complexAdd(Complex c1,Complex c2)
//{
//	Complex c3;
//	c3.real = c1.real + c2.real;
//	c3.img = c1.img + c2.img;
//	return c3;
//}
//
//
//Complex complexMulty(Complex c1,Complex c2)
//{
// 	Complex c;
// 	c.real= c1.real*c2.real - c1.img*c2.img;
// 	c.img= c1.real*c2.img + c1.img*c2.real;
// 	return c;
//}
//
//Complex complexMinus(Complex c1,Complex c2)
//{
// 	Complex c;
// 	c.real=c1.real-c2.real;
// 	c.img=c1.img-c2.img;
// 	return c;
//}
////��������
//Complex complexAdjoint(Complex c1 )
//{
// 	Complex c;
// 	c.real=c1.real;
// 	c.img= -c1.img;
// 	return c;
//}
////��������������ֵ
//void 	complexReplace(Complex *c1,Complex *c2)
//{
//	Complex temp;
//	temp.real = c1->real;
//	temp.img = c1->img;
//	c1->real = c2->real;
//	c1->img = c2->img;
//	c2->real = temp.real;		   
//	c2->img = temp.img;
//}
//
//void  calFFT(double* waveData,int len,Complex * complexOut)
//{
//	/* Complex c_final[N_DOTS];*/
//	 int i,layer,m_power,data_gap,p,k,j,rotation_count;
//	 double theta;
//	 Complex temp_compl;
//	 //wn_compl: ��ת����
//	 Complex wn_compl;
//	 //Complex *c_mid;
//	 //layer:fft�任������
//	 //data_gap�����ݼ��,
//	 //p����ת����ָ��;
//	 //rotation_count:��ת���ӵĸ�����
//	 /*zeroMean(waveData,len);*/
//	 for(i = 0;i < len; i++)
//	 {
//	 	complexOut[i].real = waveData[i];
//		complexOut[i].img = 0;
//	 }
//	 reverseComplex(complexOut,len);
//	 m_power = M_POWER; 	 //m_power�����ݵ�1<<m_power == ����len
//	 for( layer = 1;layer <= m_power; layer++)
//	 {
//	 	 data_gap = 1<< (layer - 1);     //���ݼ��
//		 for(rotation_count = 0;rotation_count<= (data_gap -1);rotation_count++)
//		 {
//		 	p = rotation_count*(1<<(m_power - layer));
//			theta = 2*PI*p/len;
//			wn_compl.real = cos(theta);
//			wn_compl.img = -sin(theta);
//			for(k = rotation_count;k<= (len-1); k += 1<< layer)
//			{
//				j = k + data_gap;
//				temp_compl = complexMulty(complexOut[j],wn_compl);
//				complexOut[j] = complexMinus(complexOut[k], temp_compl);
//			 	complexOut[k] = complexAdd(complexOut[k], temp_compl);
//			}
//		 }
//	 }
//	/* return c_final;*/
//}
//
//void  reverseComplex(Complex* c,int len)
//{
//	int i,j,n1,k,n;
//	//Complex temp;
//	int times = 0;
//	n1 = len -1;
//	n = len;
//	
//	for(j = 0,i = 0;i < n1;i++)
//	{
//		times++;
//		if(i < j)
//		{
//			complexReplace(&c[i],&c[j]);
//		}
//		k = n>>1;
//		while(k<(j+1))
//		{
//			j = j - k;
//			k = k>>1;
//		}
//		j = j + k;
//	}
//	//return c;
//}
