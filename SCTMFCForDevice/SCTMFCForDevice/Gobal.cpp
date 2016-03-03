#include "stdafx.h"
#include "Global.h"



long nextPow2(long inputN)
{
	long result=0;
	if(inputN<=0) return 0;
	result=(long)(log((double)(inputN+0.5))/log((double)2));
	return (long)(pow((double)2,(int)result));
}

int Pow10(int index)
{
	int res=1;
	int i;
	if(index==0) return 1;
	if(index>0)
	{
		for(i=0;i<index;i++)
		{
			res*=10;
		}
	}
	return res;
}

double MinA(double *pIn,int length)
{
	double result=0;
	for (int i=0;i<length;i++) 
	{
		if (result>pIn[i]) result = pIn[i];
	}
	//	TRACE("min = %lf\n",result);
	return result;
}
double MaxA(double *pIn,int length)
{
	double result=0;
	for (int i=0;i<length;i++) 
	{
		if (result<pIn[i]) result = pIn[i];
	}
	//	TRACE("max = %lf\n",result);
	return result;
}

void MinAndMax(double *pIn,int length,double &min,double &max)
{
	//double result=0;
	min = max = 0;
	for (int i=0; i<length; i++) 
	{
		if(max < pIn[i]) max = pIn[i];
		if(min > pIn[i]) min = pIn[i];
	}
}

int Comparedouble(const void *pval1, const void *pval2)
{
	return (int)( (*(double*)pval1)-(*(double*)pval2));
}

double MedianA(double *pIn, int length)  //找到数组的中间值
{
	double result=0;
	double *pTemp= new double[length];
	memcpy(pTemp,pIn,sizeof(double)*length);
	qsort(pTemp,length,sizeof(double),Comparedouble);
	result = pTemp[length/2];
	delete[] pTemp;
	return result;
}

CString  DoubleToScientNum(double num)   //不适用一个小于1的很小的数 会出错输出结果0e0
{
	int flag = 1;
	if(num<-1e-6) {
		flag = -1;
		num = -1*num;
	}
	int exponent = 0;
	int pre = 0;
	while(true)
	{
       if(fabs(num)< 10)
	   {
           pre = int(fabs(num));
		   break;
	   }else{
		   exponent++;
		   num = num/10;
	   }
	}
    CString _str;
	_str.Format(_T("%d%c%+d"),flag*pre,'e',exponent);
	return _str;
}

CString GetFileName(CString szPathName)   //从路径名截取文件名
{
     int index = szPathName.ReverseFind('\\');
	 if(index == -1)
		 return _T("");
	 else 
	 {
		 return szPathName.Mid(index+1);
	 }
}