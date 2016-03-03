#include "StdAfx.h"
#include "DataBase.h"
#include "Global.h"

CDataBase::CDataBase(void)
{
	InitData();
}

CDataBase::~CDataBase(void)
{
	ClearData();
    ClearPSDMalloc();
}

void CDataBase::ClearData()
{
	
	m_scaleY=0;
	//m_pTotalYdata = NULL;	
	m_TotalLength = 0;
	m_pCurYdata = NULL;		m_CurLength = 0;
	m_pPSDYdata = NULL;
	m_PSDreal=NULL;	m_PSDimag=NULL;	

	m_CurFrameRect = CRect(0,0,0,0);
	m_lastFrameRect = CRect(0,0,m_TotalLength,0);
	m_bZoomed = false;
	m_bShowFrame = false;
	m_bShowFFT = false;
	m_leftMarginX	= LEFTMARGIN;
	m_topMarginY	= TOPMARGIN;
	m_rightMarginX	= RIGHTMARGIN;
	m_bottomMarginY	= BOTTOMMARGIN;
	m_szFileName = _T("");
	m_globalMaxY = 0;
	m_globalMinY = 0;
	m_globalMaxX = 0;
	m_globalMinX = 0;
	m_globalMaxf = 0;
	m_globalMinf = 0;
	m_globalMaxPSD = 0;
	m_currentMaxX = 0;
	m_currentMinX = 0;
	m_currentMaxY = 0;
	m_currentMinY = 0;
	m_currentMaxf = 0;
	m_currentMinf =0;
	if(m_pTotalYdata != NULL)
	{
		delete []m_pTotalYdata;
		m_pTotalYdata = NULL;
	}
}

void CDataBase::InitData()
{
	m_pTotalYdata = NULL;
	/*if(m_pTotalYdata == NULL)
	{
		MessageBox(NULL,TEXT("∑÷≈‰ ß∞‹"),TEXT("∂ØÃ¨∑÷≈‰"),MB_OK);
	}*/
	m_TotalLength = 0;
	m_pCurYdata = NULL;
	m_CurLength = 0;
	m_pPSDYdata =  NULL;
	m_CurFrameRect = CRect(0,0,0,0);

	m_lastFrameRect = CRect(0,0,m_TotalLength,0);
	m_bZoomed = false;
	m_bShowFrame = false;
	m_bShowFFT = false;
	m_leftMarginX	= LEFTMARGIN;
	m_topMarginY	= TOPMARGIN;
	m_rightMarginX	= RIGHTMARGIN;
	m_bottomMarginY	= BOTTOMMARGIN;
	m_szFileName = _T("");
	m_globalMaxY=0;
	m_globalMinY=0;
	m_globalMaxX=0;
	m_globalMinX=0;
	m_globalMaxf=0;
	m_globalMinf=0;
	m_globalMaxPSD=0;
	m_currentMaxX=0;
	m_currentMinX=0;
	m_currentMaxY=0;
	m_currentMinY=0;
	m_currentMaxf=0;
	m_currentMinf=0;
	m_scaleY = 0;
}

void CDataBase::ClearPSDMalloc()
{
	if (m_PSDreal!=NULL)	{delete[] m_PSDreal;m_PSDreal=NULL;}
	if (m_PSDimag!=NULL)	{delete[] m_PSDimag;m_PSDimag=NULL;}
}


double* CDataBase::GetTotalData()
{
	return m_pTotalYdata;
}