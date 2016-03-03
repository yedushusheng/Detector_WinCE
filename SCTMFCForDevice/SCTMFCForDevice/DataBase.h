#if !defined(AFX_DATABASE_H__1HWF13HF_SD32F_545SD_SD2425_4DFW553F__INCLUDED_)
#define AFX_DATABASE_H__1HWF13HF_SD32F_545SD_SD2425_4DFW553F__INCLUDED_

#pragma once

class CDataBase
{
public:
	CDataBase(void);
	~CDataBase(void);
public:
	int    m_leftMarginX,m_topMarginY,m_rightMarginX,m_bottomMarginY;   //�������հ�
	double *m_PSDreal,*m_PSDimag;
	bool   m_bZoomed,m_bShowFrame;  //�Ƿ�Ŵ� �Ƿ񻭴����
	bool   m_bShowFFT;    //��־�Ƿ�FFTƵ��ͼ
	double m_scaleY;
    CString m_szFileName;      //�������ĸ��ļ��Ĳ���ͼ
	CRect  m_CurFrameRect,m_lastFrameRect,m_GraphRect;
	int    m_TotalLength,m_CurLength;

	double *m_pTotalYdata,*m_pCurYdata,*m_pPSDYdata;
	double m_globalMaxY,m_globalMinY,m_globalMaxX,m_globalMinX,m_globalMaxf,m_globalMinf,m_globalMaxPSD;
	double m_currentMaxX,m_currentMinX,m_currentMaxY,m_currentMinY,m_currentMaxf,m_currentMinf;
public:
    void ClearPSDMalloc();
	void ClearData();
	void InitData();
	double* GetTotalData();
};


#endif