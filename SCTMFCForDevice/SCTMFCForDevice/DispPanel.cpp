// DispPanel.cpp : implementation file
//

#include "stdafx.h"
#include "DispPanel.h"
#include "MyMemDC.h"
//#include "FFTNew.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDispPanel

CDispPanel::CDispPanel()
{
	
    m_hWnd = NULL;
	m_szTips = _T("正在解析数据中，请稍后。。。");
	/* InitData();*/
}

CDispPanel::~CDispPanel()
{
	ClearData();
}


BEGIN_MESSAGE_MAP(CDispPanel, CButton)
	//{{AFX_MSG_MAP(CDispPanel)
	//ON_WM_LBUTTONDOWN()
	/*ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()*/
	//}}AFX_MSG_MAP
	//ON_COMMAND(ID_SUBMENU_OPEN, &CDispPanel::OnOpen)
	ON_MESSAGE(WM_SHOWTIPS, OnShowTips)
   /* ON_MESSAGE(WM_GETDATAERR, OnGetDataErr)*/
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispPanel message handlers



afx_msg LRESULT CDispPanel::OnShowTips(WPARAM, LPARAM)
{
     Invalidate();   //刷新窗口
     return 0;
}

void CDispPanel::InitData()
{
	
}

void CDispPanel::InitScaleY()
{

}

void CDispPanel::Plotf(CDC *pDC,CRect* pRect)
{

}

void CDispPanel::PrepareData()
{

}


void CDispPanel::MyDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)   //数据准备好后画图界面
{
	CRect ClientRect=lpDrawItemStruct->rcItem;
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	ClientRect.DeflateRect(1,1,1,1);
	//	pDC->DrawFocusRect(&ClientRect);
	ClearUnits(pDC);
	m_dataBase.m_GraphRect = ClientRect;
	m_dataBase.m_GraphRect.DeflateRect(m_dataBase.m_leftMarginX+1,m_dataBase.m_topMarginY,m_dataBase.m_rightMarginX,m_dataBase.m_bottomMarginY+1);//矩形框缩小

	PrepareData();
	DrawUnits(pDC,&ClientRect); //画坐标值
	CMyMemDC* pMemDC = new CMyMemDC(pDC,&m_dataBase.m_GraphRect);
	m_dataBase.m_GraphRect = CRect(0,0,m_dataBase.m_GraphRect.Width(),m_dataBase.m_GraphRect.Height());
	CBrush hbr;
	hbr.CreateSolidBrush(RGB(255,255,255));//背景色
	pMemDC->FillRect(&m_dataBase.m_GraphRect,&hbr);
	hbr.DeleteObject();

	DrawAxis(pMemDC,&m_dataBase.m_GraphRect);//画坐标轴

	//画放大矩形
	if (m_dataBase.m_bShowFrame) 	
		//pMemDC->DrawFocusRect(&CurFrameRect);
		pMemDC->FrameRect(&m_dataBase.m_CurFrameRect,&CBrush(RGB(0,0,0)));
	//画数据曲线
	Plotf(pMemDC,&m_dataBase.m_GraphRect);

	delete pMemDC;
}
void CDispPanel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if(m_bShowTips)
	{
        WaitTips(lpDrawItemStruct);   //显示等待界面    
	}else{
        MyDrawItem(lpDrawItemStruct);   //数据准备好后画图界面
	}

}


void CDispPanel::WaitTips(LPDRAWITEMSTRUCT lpDrawItemStruct)   //显示提示信息界面
{
	CRect ClientRect=lpDrawItemStruct->rcItem;
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	ClientRect.DeflateRect(1,1,1,1);
	//	pDC->DrawFocusRect(&ClientRect);
	ClearUnits(pDC);
	pDC->SetBkMode(TRANSPARENT);
    CRect rect;
	rect.left = ClientRect.left+(ClientRect.Width()/2-50)>10?(ClientRect.Width()/2-50):10;
	rect.top = ClientRect.top+(ClientRect.Height()/2-10)>0?(ClientRect.Height()/2-10):0;
	rect.right = ClientRect.right;
	rect.bottom = ClientRect.bottom;
	CString t_szStr = m_szTips;
    MyDrawText(pDC,t_szStr,rect,DT_LEFT);
}
//void CDispPanel::OnLButtonDown(UINT nFlags, CPoint point) 
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

//void CDispPanel::OnMouseMove(UINT nFlags, CPoint point) 
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
//void CDispPanel::OnLButtonUp(UINT nFlags, CPoint point) 
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

//void CDispPanel::OnRButtonDown(UINT nFlags, CPoint point) 
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

void CDispPanel::ClearData()
{
	
}

//void CDispPanel::GetPSD()
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

//void CDispPanel::ClearPSDMalloc()
//{
//	if (m_PSDreal!=NULL)	{delete[] m_PSDreal;m_PSDreal=NULL;}
//	if (m_PSDimag!=NULL)	{delete[] m_PSDimag;m_PSDimag=NULL;}
//}

//void CDispPanel::OnRButtonDblClk(UINT nFlags, CPoint point) 
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

//void CDispPanel::DrawFFTAxis(CDC *pDC, CRect *pRect)   //画FFT坐标框竖线
//{
//	int x0=pRect->left+1;
//	int y0=0;
//	int num=10;
//
//	CPen pen1(PS_SOLID,2,RGB(0,0,0));
//	CPen* pOldPen;
//	pOldPen=pDC->SelectObject(&pen1);
//
//	pDC->MoveTo(pRect->left+1,pRect->top);		pDC->LineTo(pRect->left+1,pRect->bottom);//纵向左轴
//	pDC->MoveTo(pRect->left+1,pRect->top+1);	pDC->LineTo(pRect->right,pRect->top+1);//水平上端轴
//	pDC->MoveTo(pRect->right-1,pRect->top);		pDC->LineTo(pRect->right-1,pRect->bottom);//纵向右轴
//	pDC->MoveTo(pRect->left+1,pRect->bottom-1);	pDC->LineTo(pRect->right,pRect->bottom-1);//水平下轴
//
//	CPen pen2(PS_DOT,1,RGB(30,0,0));
//	pDC->SelectObject(&pen2);
//
//	double powerUnit = pow(10,floor(log10(scaleY)));
//
//	y0=(pRect->top+pRect->bottom)/2;
//	//画纵轴坐标线
//	for(int i=0;i<5;i++)
//	{
//		pDC->MoveTo(pRect->left, y0-(pRect->Height()/10)*i);		
//		pDC->LineTo(pRect->right,y0-(pRect->Height()/10)*i);//纵向左轴
//	}
//
//	for(int i=0;i<5;i++)
//	{
//		pDC->MoveTo(pRect->left, y0+(pRect->Height()/10)*i);		
//		pDC->LineTo(pRect->right,y0+(pRect->Height()/10)*i);//纵向左轴
//	}
//
//
//	//画横轴坐标线
//	for(int j=1;j<10;j++)
//	{
//		pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
//		pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向顶轴
//		pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
//		pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向底轴
//	}
//
//	pDC->SelectObject(pOldPen);
//}

//void CDispPanel::DrawOrgAxis(CDC *pDC, CRect *pRect)   //画原始波形坐标框竖线
//{
//	int x0=pRect->left+1;
//	int y0=0;
//	int num=10;
//
//	CPen pen1(PS_SOLID,2,RGB(0,0,0));
//	CPen* pOldPen;
//	pOldPen=pDC->SelectObject(&pen1);
//
//	pDC->MoveTo(pRect->left+1,pRect->top);		pDC->LineTo(pRect->left+1,pRect->bottom);//纵向左轴
//	pDC->MoveTo(pRect->left+1,pRect->top+1);	pDC->LineTo(pRect->right,pRect->top+1);//水平上端轴
//	pDC->MoveTo(pRect->right-1,pRect->top);		pDC->LineTo(pRect->right-1,pRect->bottom);//纵向右轴
//	pDC->MoveTo(pRect->left+1,pRect->bottom-1);	pDC->LineTo(pRect->right,pRect->bottom-1);//水平下轴
//
//	CPen pen2(PS_DOT,1,RGB(30,0,0));
//	pDC->SelectObject(&pen2);
//
//	double powerUnit = pow(10,floor(log10(scaleY)));
//
//	y0=(pRect->top+pRect->bottom)/2;
//	//画纵轴坐标线
//	for(int i=0;i<5;i++)
//	{
//		pDC->MoveTo(pRect->left, y0-(pRect->Height()/10)*i);		
//		pDC->LineTo(pRect->right,y0-(pRect->Height()/10)*i);//纵向左轴
//	}
//
//	for(int i=0;i<5;i++)
//	{
//		pDC->MoveTo(pRect->left, y0+(pRect->Height()/10)*i);		
//		pDC->LineTo(pRect->right,y0+(pRect->Height()/10)*i);//纵向左轴
//	}
//
//
//	//画横轴坐标线
//	for(int j=1;j<10;j++)
//	{
//		pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
//		pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向顶轴
//		pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
//		pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//横向底轴
//	}
//
//	pDC->SelectObject(pOldPen);
//} 

void CDispPanel::DrawAxis(CDC *pDC, CRect *pRect)   //画坐标框竖线
{

}



void CDispPanel::DrawUnits(CDC *pDC, CRect *pRect)   //画坐标尺
{
	
}

void CDispPanel::ClearUnits(CDC* pDC)
{
	CRect ClientRect;
	::GetClientRect(this->m_hWnd,&ClientRect);
	pDC->FillRect(&ClientRect,&CBrush(MY_BACKCOLOR));
//	CRect temp = CRect(0,0,m_dataBase.m_leftMarginX + 1,ClientRect.bottom - m_dataBase.m_bottomMarginY);
//	pDC->FillRect(&temp,&CBrush(MY_BACKCOLOR));
////	pDC->Rectangle(&temp);
//	temp=CRect(0,ClientRect.bottom-m_dataBase.m_bottomMarginY-1,ClientRect.right,ClientRect.bottom);
//	pDC->FillRect(&temp,&CBrush(MY_BACKCOLOR));
//	pDC->Rectangle(&temp);
}

void CDispPanel::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
	//通过代码实现Owner Draw自绘属性
}

void CDispPanel::MyDrawText(CDC *pCDC,const CString& str,CRect rect,UINT nFormat)
{ 
    pCDC->DrawText(str,&rect,nFormat);
}

void CDispPanel::CreatBtn(CWnd* pRarentWnd,UINT uID,CString szFileName,BOOL bShowTips)   //创建窗口画图的函数
{
	m_dataBase.m_szFileName = szFileName;
	m_bShowTips = bShowTips;
	if(m_hWnd == NULL)
	{
		CRect rect;
        pRarentWnd->GetClientRect(&rect);
		/*rect.DeflateRect(10,10,10,10);*/
		Create(TEXT("原波形按钮"),WS_CHILD|WS_DISABLED|WS_VISIBLE,rect,pRarentWnd,uID);
	}else{
		Invalidate();   //重绘窗口
	}
}


