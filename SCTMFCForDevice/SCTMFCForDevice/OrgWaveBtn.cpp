#include "stdafx.h"
//#include "DispPanel.h"
#include "OrgWaveBtn.h"
//#include "MyMemDC.h"
//#include "FFTNew.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrgWaveBtn

COrgWaveBtn::COrgWaveBtn()
{
	m_bShowTips = TRUE;  //data准备好 显示等待界面
    InitData();
}

COrgWaveBtn::~COrgWaveBtn()
{
	//ClearPSDMalloc();
}


BEGIN_MESSAGE_MAP(COrgWaveBtn, CDispPanel)
	//{{AFX_MSG_MAP(COrgWaveBtn)
	//ON_WM_LBUTTONDOWN()
	/*ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()*/
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrgWaveBtn message handlers

void COrgWaveBtn::InitData()
{
	m_dataBase.m_pTotalYdata = new double[DATALENGTH];
	m_dataBase.m_TotalLength = DATALENGTH;
    if(m_dataBase.m_pTotalYdata == NULL)
	{
		MessageBox(TEXT("分配内存失败，内存不足"),TEXT("动态存储"),MB_OK);
        m_dataBase.m_TotalLength = 0;
	}
	
}

void COrgWaveBtn::InitScaleY()
{
	m_dataBase.m_globalMaxY = 0;	
	m_dataBase.m_globalMinY = 0;
	/*for(int i=0;i<m_CurLength;i++)
	{
	if (m_globalMaxY<m_pCurYdata[i]) m_globalMaxY = m_pCurYdata[i];
	if (m_globalMinY>m_pCurYdata[i]) m_globalMinY = m_pCurYdata[i];
	}*/
	MinAndMax(m_dataBase.m_pCurYdata,m_dataBase.m_CurLength,m_dataBase.m_globalMinY,m_dataBase.m_globalMaxY);
	if (m_dataBase.m_globalMaxY - m_dataBase.m_globalMinY > 1e-6)
	{
		double temp = max(m_dataBase.m_globalMaxY,-m_dataBase.m_globalMinY);
		m_dataBase.m_scaleY = m_dataBase.m_GraphRect.Height()/(temp*2);	
	}
	else
	{
		m_dataBase.m_scaleY = 1;
	}
	m_dataBase.m_currentMinY = m_dataBase.m_globalMinY;	
	m_dataBase.m_currentMaxY = m_dataBase.m_globalMaxY;
	m_dataBase.m_globalMinX = 0;	//这点 和FFT应该不一样的
	m_dataBase.m_globalMaxX = m_dataBase.m_TotalLength;
	m_dataBase.m_currentMinX = m_dataBase.m_globalMinX;	
	m_dataBase.m_currentMaxX = m_dataBase.m_globalMaxX;

}

void COrgWaveBtn::Plotf(CDC *pDC,CRect* pRect)    //这个函数还要好好改改 
{
	int x0 = pRect->left,i=0;
	double nStep = 0,x=0;
	int y0=0;

	CPen penNew(PS_SOLID,1,RGB(0,0,255));
	CPen* pPenOld;
	pPenOld=pDC->SelectObject(&penNew);

	/*y0=(pRect->top+pRect->bottom)/2;*/
	double t_scaleY = pRect->Height()/(m_dataBase.m_globalMaxY-m_dataBase.m_globalMinY);
	y0 = fabs(m_dataBase.m_globalMinY)*t_scaleY;    //y零点坐标
	y0 = pRect->bottom - y0;

	pDC->MoveTo(x0,y0);
	double tempMin=0,tempMax=0;
	//对于不同数量级数据的显示，出于显示速度的问题，不采用通用方法
	if (m_dataBase.m_CurLength>10*(pRect->Width()))
	{//数据量是窗口的10倍以上

		nStep=1.0*m_dataBase.m_CurLength/(pRect->Width());
		for (x=0,i=0;i<pRect->Width();i++,x=(int)(x+nStep)) 
		{
			MinAndMax(&m_dataBase.m_pCurYdata[int(x)],int(nStep),tempMin,tempMax);
			if(tempMin < 0) pDC->LineTo(x0+i,(int)(y0-tempMin*t_scaleY)); 
			if(tempMax > 0) pDC->LineTo(x0+i,(int)(y0-tempMax*t_scaleY)); 
			if(tempMin == 0 && tempMax == 0) pDC->LineTo(x0+i,y0); 
		}
	}
	else 
	{//数据量是窗口的几倍或者，数据量小于窗口尺寸(波形放大)
		if (!m_dataBase.m_bZoomed && m_dataBase.m_CurLength<pRect->Width())
		{
			for (i=0;i<m_dataBase.m_CurLength&&i<pRect->Width();i++) 
			{
				pDC->LineTo((int)(x0+i),(int)(y0-m_dataBase.m_pCurYdata[i]*t_scaleY)); 
			}
		}
		else
		{
			if(m_dataBase.m_CurLength>0)
			{
				nStep = 1.0*pRect->Width()/m_dataBase.m_CurLength;
				for (i=0;i<m_dataBase.m_CurLength;i++) 
				{
					pDC->LineTo((int)(x0+i*nStep),(int)(y0-m_dataBase.m_pCurYdata[i]*t_scaleY)); 
				}
			}
		}
	}
	pDC->SelectObject(pPenOld);
}

void COrgWaveBtn::PrepareData()
{
	//准备数据以及绘制坐标
	if (m_dataBase.m_pTotalYdata!=NULL) 
	{
		if(m_dataBase.m_pCurYdata==NULL) 
		{
			m_dataBase.m_pCurYdata = m_dataBase.m_pTotalYdata;
			m_dataBase.m_CurLength = m_dataBase.m_TotalLength;
		}
		/*if (m_dataBase.m_scaleY == 0)
		{*/
			InitScaleY();
		/*}*/
	}	
}




//void COrgWaveBtn::OnLButtonDown(UINT nFlags, CPoint point) 
//{
//	// TODO: Add your message handler code here and/or call default
//	if(point.x<leftMarginX) return;
//	if(m_pTotalYdata==NULL) return;
////	if (!showFrame)
//	{
//		showFrame = true;
//		CurFrameRect.top = point.y-topMarginY;
//		CurFrameRect.bottom = CurFrameRect.top;
//		CurFrameRect.left = point.x-leftMarginX;
//		CurFrameRect.right = CurFrameRect.left;
//		SetCapture();
//	}
////	else
////	{
////		showFrame = false;
////	}
//	if(!Zoomed)
//	{
//		if (bShowPSD)
//		{
//			lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
//		}
//		else
//		{
//			lastFrameRect = CRect(0,0,TotalLength,0);
//		}
//	}
//	CButton::OnLButtonDown(nFlags, point);
//}

//void COrgWaveBtn::OnMouseMove(UINT nFlags, CPoint point) 
//{
//	// TODO: Add your message handler code here and/or call default
//	if (nFlags==MK_LBUTTON)
//	{
//		if(m_pTotalYdata==NULL) return;
//		if (showFrame)
//		{
//			if (point.x-leftMarginX > CurFrameRect.left)
//				CurFrameRect.right=point.x-leftMarginX;
//			else
//				CurFrameRect.left=point.x-leftMarginX;
//			
//			if (point.y-topMarginY > CurFrameRect.top)
//				CurFrameRect.bottom=point.y-topMarginY;
//			else
//				CurFrameRect.top=point.y-topMarginY;
//			Invalidate(FALSE);
//		}
//	}
//	CButton::OnMouseMove(nFlags, point);
//}
//
//void COrgWaveBtn::OnLButtonUp(UINT nFlags, CPoint point) 
//{
//	// TODO: Add your message handler code here and/or call default
//	if(m_pTotalYdata==NULL) return;
//	if(CurFrameRect.Width()<2 ||CurFrameRect.Height() < 2) return;
//
//	if (showFrame) 
//	{
//		showFrame = false;
//	}
//	
//	int OffsetBegin,OffsetEnd;
//
//	if (Zoomed||TotalLength>=m_GraphRect.Width())
//	{
//		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left/m_GraphRect.Width()*lastFrameRect.Width());
//		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right/m_GraphRect.Width()*lastFrameRect.Width());
//	}
//	else
//	{//数据量小于窗口宽度且不放大波形
//		if(CurFrameRect.left>=TotalLength) return;
//		if(CurFrameRect.right>TotalLength) CurFrameRect.right=TotalLength;
//		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left);
//		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right);
//	}
//	//TRACE("start = %d end = %d\n",OffsetBegin,OffsetEnd);
//	if(OffsetBegin<0) OffsetBegin=0;
//	if(OffsetEnd>TotalLength) OffsetEnd = TotalLength;
//	CurLength = OffsetEnd - OffsetBegin;
//
//	if (bShowPSD)
//	{
//		m_pCurYdata	 = m_pPSDYdata+OffsetBegin;
//		m_currentMinf =OffsetBegin;
//		m_currentMaxf =OffsetEnd;
//	}
//	else
//	{
//		m_pCurYdata	 = m_pTotalYdata+OffsetBegin;
//		m_currentMinX = m_globalMinX + OffsetBegin;
//		m_currentMaxX = m_globalMinX + OffsetEnd;
//	}
//
//	if (CurFrameRect.Height()>1)
//	{
//		scaleY*=1.0*m_GraphRect.Height()/CurFrameRect.Height();
//	}
//	lastFrameRect.left = OffsetBegin;
//	lastFrameRect.right = OffsetEnd;
//	Zoomed = true;
//	Invalidate(FALSE);
//
//	CButton::OnLButtonUp(nFlags, point);
//}

//void COrgWaveBtn::OnRButtonDown(UINT nFlags, CPoint point) 
//{
//	// TODO: Add your message handler code here and/or call default
//	Zoomed = false;
//	m_pCurYdata = NULL;
//	ReleaseCapture();
//	if (bShowPSD)
//	{
//		lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
//		m_currentMinf = 0;
//		m_currentMaxf = 250000;
//	}
//	else
//	{
//		lastFrameRect = CRect(0,0,TotalLength,0);
//		m_currentMinX = 0;
//		m_currentMaxX = TotalLength;
//	}
//	scaleY = 0;
//	Invalidate(FALSE);
//	CButton::OnRButtonDown(nFlags, point);
//}


//void COrgWaveBtn::GetPSD()
//{
//	if(m_pTotalYdata == NULL) return;
//	ClearPSDMalloc();
//	m_globalMaxPSD = 0;
//	PSDreal = new double[nextPow2(TotalLength)];
//	PSDimag = new double[nextPow2(TotalLength)];
//	
//	FFT(nextPow2(TotalLength),false,m_pTotalYdata,NULL,PSDreal,PSDimag);
////	RealFFT(nextPow2(TotalLength),m_pTotalYdata,PSDreal,PSDimag);
//	for (int i=0;i<nextPow2(TotalLength)/2;i++) 
//	{
//		PSDreal[i]=PSDreal[i]*PSDreal[i]+PSDimag[i]*PSDimag[i];
//		if (m_globalMaxPSD<PSDreal[i]) m_globalMaxPSD=PSDreal[i];
//	}
//	if(m_globalMaxPSD>1e-6) scaleY = m_GraphRect.Height()/(m_globalMaxPSD);	
//	m_pPSDYdata = PSDreal;
//	m_globalMinf = 0;
//	CurLength = nextPow2(TotalLength)/2;
//	m_currentMinf = 0;
//	m_currentMaxf = 250000;
//}


//void COrgWaveBtn::OnRButtonDblClk(UINT nFlags, CPoint point) 
//{
//	if(bShowPSD)
//	{
//		bShowPSD = false;
//	}
//	else 
//	{
//		if(!m_pPSDYdata) GetPSD();
//		bShowPSD = true;
//		m_currentMinf = 0;
//		m_currentMaxf = 250000;
//	}
//	OnRButtonDown(nFlags,point); 
//	CButton::OnRButtonDblClk(nFlags, point);
//}


void COrgWaveBtn::DrawAxis(CDC *pDC, CRect *pRect)   //画坐标框竖线
{
	int x0=pRect->left+1;
	int y0=0;
	int num=10;

	CPen pen1(PS_SOLID,2,RGB(0,0,0));
	CPen* pOldPen;
	pOldPen=pDC->SelectObject(&pen1);

	pDC->MoveTo(pRect->left+1,pRect->top);		pDC->LineTo(pRect->left+1,pRect->bottom);//纵向左轴
	pDC->MoveTo(pRect->left+1,pRect->top+1);	pDC->LineTo(pRect->right,pRect->top+1);//水平上端轴
	pDC->MoveTo(pRect->right-1,pRect->top);		pDC->LineTo(pRect->right-1,pRect->bottom);//纵向右轴
	pDC->MoveTo(pRect->left+1,pRect->bottom-1);	pDC->LineTo(pRect->right,pRect->bottom-1);//水平下轴

	CPen pen2(PS_DOT,1,RGB(30,0,0));
	pDC->SelectObject(&pen2);

	double powerUnit = pow(10,floor(log10(m_dataBase.m_scaleY)));

	/*y0=(pRect->top+pRect->bottom)/2;*/
	y0 = (fabs(m_dataBase.m_globalMinY)/(m_dataBase.m_globalMaxY-m_dataBase.m_globalMinY))*pRect->Height();    //y零点坐标
	y0 = pRect->bottom - y0;
	//画纵轴坐标线
	int i = 0,yHeight = y0;
	while(yHeight > pRect->top)
	{
		pDC->MoveTo(pRect->left, yHeight);		
		pDC->LineTo(pRect->right,yHeight);//纵向左轴
        yHeight = y0-(pRect->Height()/10)*(++i);
	}
    i = 1;
	yHeight = y0+(pRect->Height()/10)*i;
	while(yHeight < pRect->bottom)
	{
		pDC->MoveTo(pRect->left, yHeight);		
		pDC->LineTo(pRect->right,yHeight);//纵向左轴
		yHeight = y0+(pRect->Height()/10)*(i++);
	}


	//画横轴坐标线
	for(int j=1;j<10;j++)
	{
		pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
		pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向顶轴
		//pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
		//pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向底轴
	}

	pDC->SelectObject(pOldPen);
}



void COrgWaveBtn::DrawUnits(CDC *pDC, CRect *pRect)   //画坐标尺
{
	int y0;
	pDC->SetBkMode(TRANSPARENT);
	/*pDC->SetTextAlign(TA_RIGHT);*/
	COLORREF color=pDC->SetTextColor(RGB(0,0,0));
	CString out,strScales;
	int nScalesY,nScalesX;
	//y0=pRect->bottom-m_dataBase.m_bottomMarginY-pRect->Height()/2;    //y零点坐标
	
	//////////////////////////////////////////////////////////////////////////
	//纵轴坐标

	nScalesY=(int)log10(m_dataBase.m_globalMaxY);
	nScalesY=Pow10(nScalesY);
	if(nScalesY<1000) nScalesY=1;
	y0 = (fabs(m_dataBase.m_globalMinY)/(m_dataBase.m_globalMaxY-m_dataBase.m_globalMinY))*(pRect->bottom-m_dataBase.m_bottomMarginY-(pRect->top+m_dataBase.m_topMarginY));    //y零点坐标
	y0 = pRect->bottom-m_dataBase.m_bottomMarginY- y0-18;
	out.Format(TEXT("%10.2f"),m_dataBase.m_globalMaxY/nScalesY);
	out.TrimLeft();
	//最大值 坐标
	/*MyDrawText(pDC,out,CRect(pRect->left+m_dataBase.m_leftMarginX-5,pRect->top+8,pRect->right,pRect->bottom),DT_LEFT); */ 
	MyDrawText(pDC,out,CRect(pRect->left,pRect->top+10,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT); 
	//pDC->DrawText(TEXT("0.0"),&rc,DT_LEFT);
	MyDrawText(pDC,TEXT("0"),CRect(pRect->left,y0+10,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);
	//pDC->TextOut(pRect->left+leftMarginX-5,y0+10,);
	out.Format(TEXT("%10.2f"),m_dataBase.m_globalMinY/nScalesY);//Y轴最小值
    out.TrimLeft();
	//pDC->TextOut(pRect->left+leftMarginX-5,pRect->bottom-bottomMarginY-15,out);
	MyDrawText(pDC,out,CRect(pRect->left,pRect->bottom-m_dataBase.m_bottomMarginY-15,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);

	//////////////////////////////////////////////////////////////////////////
	//横轴坐标
	nScalesX=(int)log10(m_dataBase.m_currentMaxX);
	nScalesX=Pow10(nScalesX);
	if(nScalesX<1000) nScalesX=1;
	//pDC->SetTextAlign(TA_LEFT);
	out.Format(TEXT("%10.2lf"),m_dataBase.m_currentMinX/nScalesX);   //最小值
	out.TrimLeft();
	//pDC->TextOut(pRect->left+leftMarginX,pRect->bottom-bottomMarginY,out);
	MyDrawText(pDC,out,CRect(pRect->left+m_dataBase.m_leftMarginX,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->left+m_dataBase.m_leftMarginX+40,pRect->bottom));
	int xWidth=(pRect->right-m_dataBase.m_rightMarginX)-(pRect->left+m_dataBase.m_leftMarginX);   //屏幕x轴实际宽度
	double xxWidth = m_dataBase.m_currentMaxX-m_dataBase.m_currentMinX;   //波形宽度 采样点个数
	CRect drawRT(pRect->left+m_dataBase.m_leftMarginX,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->right,pRect->bottom-m_dataBase.m_bottomMarginY+15);
	for(int xx=1;xx<5;xx++)
	{
		out.Format(TEXT("%10.2lf"),(m_dataBase.m_currentMinX+xx*xxWidth/5)/nScalesX);
		out.TrimLeft();
		//pDC->TextOut(drawRT.left+(xWidth/5-3)*xx,drawRT.top,out);
		MyDrawText(pDC,out,CRect(drawRT.left+(xWidth/5-3)*xx,drawRT.top,drawRT.right,drawRT.bottom));
	}
	//pDC->SetTextAlign(TA_RIGHT);
	out.Format(TEXT("%10.2lf"),m_dataBase.m_currentMaxX/nScalesX);   //x轴最大值
	out.TrimLeft();
	//pDC->TextOut(pRect->right-rightMarginX,pRect->bottom-bottomMarginY,out);
	/*MyDrawText(pDC,out,CRect(pRect->right-m_dataBase.m_rightMarginX,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->right,pRect->bottom),DT_RIGHT);*/
    MyDrawText(pDC,out,CRect(pRect->right-m_dataBase.m_rightMarginX-20,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->right,pRect->bottom),DT_RIGHT);
	if(nScalesY>1)
	{
		/*out.Format(TEXT("%.0g"),nScalesY*1.0);
		out.TrimLeft();*/
		out = DoubleToScientNum(nScalesY*1.0);
		//pDC->TextOut(pRect->left+leftMarginX-5,pRect->top-2,out);
		MyDrawText(pDC,out,CRect(pRect->left,pRect->top,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);
	}
	if(nScalesX>1)
	{
		/*out.Format(TEXT("%.0g"),nScalesX*1.0);
		out.TrimLeft();*/
		out = DoubleToScientNum(nScalesX*1.0);
		//pDC->TextOut(pRect->right-rightMarginX,pRect->bottom-bottomMarginY/2,out);
		MyDrawText(pDC,out,CRect(pRect->right-m_dataBase.m_rightMarginX-50,pRect->bottom-m_dataBase.m_bottomMarginY/2,pRect->right,pRect->bottom),DT_RIGHT);
	}
	//文件名
	CString szFileName = _T("文件名：")+m_dataBase.m_szFileName;
    MyDrawText(pDC,szFileName,CRect(pRect->left+m_dataBase.m_leftMarginX,pRect->bottom-m_dataBase.m_bottomMarginY/2,pRect->right,pRect->bottom));   
}


