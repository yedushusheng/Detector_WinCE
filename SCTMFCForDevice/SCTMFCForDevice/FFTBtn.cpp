#include "stdafx.h"
//#include "DispPanel.h"
#include "FFTBtn.h"
//#include "MyMemDC.h"
//#include "FFTNew.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFFTBtn

CFFTBtn::CFFTBtn()
{
     //m_pTotalYdata = new double[16384];
	m_bShowTips = TRUE;
    InitData();
}

CFFTBtn::~CFFTBtn()
{
	//ClearPSDMalloc();
	/*if(m_pTotalYdata != NULL)
	{
		delete [] m_pTotalYdata;
        m_pTotalYdata = NULL;
	}*/
}
//
//
BEGIN_MESSAGE_MAP(CFFTBtn, CDispPanel)
	//{{AFX_MSG_MAP(CFFTBtn)
	//ON_WM_LBUTTONDOWN()
	/*ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()*/
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CFFTBtn message handlers
void CFFTBtn::InitData()
{
    m_dataBase.m_pTotalYdata = new double[FFTDATALENGTH];
	m_dataBase.m_TotalLength = FFTDATALENGTH;
	if(m_dataBase.m_pTotalYdata == NULL)
	{
		MessageBox(TEXT("�����ڴ�ʧ�ܣ��ڴ治��"),TEXT("��̬�洢"),MB_OK);
		m_dataBase.m_TotalLength = 0;
	}
}


void CFFTBtn::InitScaleY()
{
	m_dataBase.m_globalMaxY = 0;	m_dataBase.m_globalMinY = 0;
	/*for(int i=0;i<m_CurLength;i++)
	{
		if (m_globalMaxY<m_pCurYdata[i]) m_globalMaxY = m_pCurYdata[i];
		if (m_globalMinY>m_pCurYdata[i]) m_globalMinY = m_pCurYdata[i];
	}*/
	m_dataBase.m_globalMaxY = MaxA(m_dataBase.m_pCurYdata,m_dataBase.m_CurLength);
	/*if (m_dataBase.m_globalMaxY-m_dataBase.m_globalMinY>1e-6)
	{
		double temp = max(m_dataBase.m_globalMaxY,-m_dataBase.m_globalMinY);
		m_dataBase.m_scaleY = m_dataBase.m_GraphRect.Height()/(temp*2);	
	}
	else
	{
		m_dataBase.m_scaleY = 1;
	}*/
	m_dataBase.m_scaleY = m_dataBase.m_GraphRect.Height()/m_dataBase.m_globalMaxY;	
	m_dataBase.m_currentMinY = m_dataBase.m_globalMinY;	
	m_dataBase.m_currentMaxY = m_dataBase.m_globalMaxY;
	m_dataBase.m_globalMinX = 0;	  //��С1kHz
	m_dataBase.m_globalMaxX = m_dataBase.m_TotalLength;//����Ӧ10khz
	m_dataBase.m_currentMinf = m_dataBase.m_globalMinX;	
	m_dataBase.m_currentMaxf = m_dataBase.m_globalMaxX;

}
//
void CFFTBtn::Plotf(CDC *pDC,CRect* pRect)
{
	
	CPen pen1(PS_SOLID,1,RGB(0,0,255));
	CPen* pPen;
	pPen=pDC->SelectObject(&pen1);
	//if(bShowPSD)
	int x0=pRect->left;
	int y0=pRect->bottom;
	
	pDC->MoveTo(x0,y0);

	double tempMin=0,tempMax=0;
	//���ڲ�ͬ���������ݵ���ʾ��������ʾ�ٶȵ����⣬������ͨ�÷���
	if (m_dataBase.m_CurLength > 10*pRect->Width())
	{//�������Ǵ��ڵ�10������
		
		//double nStep = 1.0*m_dataBase.m_CurLength/pRect->Width();
		//for (double x=0,int i=0;i < pRect->Width(); i++,x = (int)(x+nStep)) 
		//{
		//	tempMin = MinA(&m_dataBase.m_pCurYdata[int(x)],int(nStep));
		//	tempMax = MaxA(&m_dataBase.m_pCurYdata[int(x)],int(nStep));
		//	MinAndMax()
		//	if(tempMin < 0) pDC->LineTo(x0+i,(int)(y0-tempMin*m_dataBase.m_scaleY)); 
		//	if(tempMax > 0) pDC->LineTo(x0+i,(int)(y0-tempMax*m_dataBase.m_scaleY)); 
		//	if(tempMin == 0 && tempMax == 0) pDC->LineTo(x0+i,y0); 
		//}
        int nStep = int(m_dataBase.m_CurLength/pRect->Width());
		for (int index_start=0, i=0;i < pRect->Width(); i++,index_start += nStep) 
		{
			//����FFT��˵ ֻ�����ֵ����
			tempMax = MaxA(&m_dataBase.m_pCurYdata[index_start],nStep);
			pDC->LineTo(x0+i,(int)(y0-tempMax*m_dataBase.m_scaleY)); 
		}
	}
	else 
	{//�������Ǵ��ڵļ������ߣ�������С�ڴ��ڳߴ�(���ηŴ�)
		if (!m_dataBase.m_bZoomed && m_dataBase.m_CurLength<pRect->Width())
		{
			for (int i = 0;i < m_dataBase.m_CurLength && i < pRect->Width(); i++) 
			{
				pDC->LineTo((int)(x0+i),(int)(y0-m_dataBase.m_pCurYdata[i]*m_dataBase.m_scaleY)); 
			}
		}
		else
		{
			if(m_dataBase.m_CurLength > 0)
			{
				int nStep = int(m_dataBase.m_CurLength/pRect->Width());
				for (int index_start=0, i=0;i < pRect->Width(); i++,index_start += nStep) 
				{
					tempMax = MaxA(&m_dataBase.m_pCurYdata[index_start],nStep);
					pDC->LineTo(x0+i,(int)(y0-tempMax*m_dataBase.m_scaleY)); 
				}
			}
		}

	}

	pDC->SelectObject(pPen);
}
//
void CFFTBtn::PrepareData()
{
	//׼�������Լ���������
	if (m_dataBase.m_pTotalYdata!=NULL) 
	{
		if(m_dataBase.m_pCurYdata==NULL) 
		{
			m_dataBase.m_pCurYdata = m_dataBase.m_pTotalYdata;
			m_dataBase.m_CurLength= m_dataBase.m_TotalLength;
		}
		/*if(m_dataBase.m_scaleY == 0)
		{*/
			InitScaleY();
		/*}*/
	}	
}

////void CFFTBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
////{
////	CRect ClientRect=lpDrawItemStruct->rcItem;
////	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
////
////	ClientRect.DeflateRect(1,1,1,1);
//////	pDC->DrawFocusRect(&ClientRect);
////	ClearUnits(pDC);
////	m_GraphRect = ClientRect;
////	m_GraphRect.DeflateRect(m_leftMarginX,m_topMarginY,m_rightMarginX,m_bottomMarginY);//���ο���С
////	
////	PrepareData();
////	DrawUnits(pDC,&ClientRect); //������ֵ
////	CMyMemDC* pMemDC = new CMyMemDC(pDC,&m_GraphRect);
////	m_GraphRect = CRect(0,0,m_GraphRect.Width(),m_GraphRect.Height());
////	CBrush hbr;
////	hbr.CreateSolidBrush(RGB(255,255,255));//����ɫ
////	pMemDC->FillRect(&m_GraphRect,&hbr);
////	hbr.DeleteObject();
////	
////	DrawAxis(pMemDC,&m_GraphRect);//��������
////
////	//���Ŵ����
////	if (m_bShowFrame) 	
////		//pMemDC->DrawFocusRect(&CurFrameRect);
////		pMemDC->FrameRect(&m_CurFrameRect,&CBrush(RGB(0,0,0)));
////	//����������
//// 	Plotf(pMemDC,&m_GraphRect);
////	
////	delete pMemDC;
////
////}
//
////void CFFTBtn::OnLButtonDown(UINT nFlags, CPoint point) 
////{
////	// TODO: Add your message handler code here and/or call default
////	if(point.x<leftMarginX) return;
////	if(m_pTotalYdata==NULL) return;
//////	if (!showFrame)
////	{
////		showFrame = true;
////		CurFrameRect.top = point.y-topMarginY;
////		CurFrameRect.bottom = CurFrameRect.top;
////		CurFrameRect.left = point.x-leftMarginX;
////		CurFrameRect.right = CurFrameRect.left;
////		SetCapture();
////	}
//////	else
//////	{
//////		showFrame = false;
//////	}
////	if(!Zoomed)
////	{
////		if (bShowPSD)
////		{
////			lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
////		}
////		else
////		{
////			lastFrameRect = CRect(0,0,TotalLength,0);
////		}
////	}
////	CButton::OnLButtonDown(nFlags, point);
////}
//
////void CFFTBtn::OnMouseMove(UINT nFlags, CPoint point) 
////{
////	// TODO: Add your message handler code here and/or call default
////	if (nFlags==MK_LBUTTON)
////	{
////		if(m_pTotalYdata==NULL) return;
////		if (showFrame)
////		{
////			if (point.x-leftMarginX > CurFrameRect.left)
////				CurFrameRect.right=point.x-leftMarginX;
////			else
////				CurFrameRect.left=point.x-leftMarginX;
////			
////			if (point.y-topMarginY > CurFrameRect.top)
////				CurFrameRect.bottom=point.y-topMarginY;
////			else
////				CurFrameRect.top=point.y-topMarginY;
////			Invalidate(FALSE);
////		}
////	}
////	CButton::OnMouseMove(nFlags, point);
////}
////
////void CFFTBtn::OnLButtonUp(UINT nFlags, CPoint point) 
////{
////	// TODO: Add your message handler code here and/or call default
////	if(m_pTotalYdata==NULL) return;
////	if(CurFrameRect.Width()<2 ||CurFrameRect.Height() < 2) return;
////
////	if (showFrame) 
////	{
////		showFrame = false;
////	}
////	
////	int OffsetBegin,OffsetEnd;
////
////	if (Zoomed||TotalLength>=m_GraphRect.Width())
////	{
////		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left/m_GraphRect.Width()*lastFrameRect.Width());
////		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right/m_GraphRect.Width()*lastFrameRect.Width());
////	}
////	else
////	{//������С�ڴ��ڿ���Ҳ��Ŵ���
////		if(CurFrameRect.left>=TotalLength) return;
////		if(CurFrameRect.right>TotalLength) CurFrameRect.right=TotalLength;
////		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left);
////		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right);
////	}
////	//TRACE("start = %d end = %d\n",OffsetBegin,OffsetEnd);
////	if(OffsetBegin<0) OffsetBegin=0;
////	if(OffsetEnd>TotalLength) OffsetEnd = TotalLength;
////	CurLength = OffsetEnd - OffsetBegin;
////
////	if (bShowPSD)
////	{
////		m_pCurYdata	 = m_pPSDYdata+OffsetBegin;
////		m_currentMinf =OffsetBegin;
////		m_currentMaxf =OffsetEnd;
////	}
////	else
////	{
////		m_pCurYdata	 = m_pTotalYdata+OffsetBegin;
////		m_currentMinX = m_globalMinX + OffsetBegin;
////		m_currentMaxX = m_globalMinX + OffsetEnd;
////	}
////
////	if (CurFrameRect.Height()>1)
////	{
////		scaleY*=1.0*m_GraphRect.Height()/CurFrameRect.Height();
////	}
////	lastFrameRect.left = OffsetBegin;
////	lastFrameRect.right = OffsetEnd;
////	Zoomed = true;
////	Invalidate(FALSE);
////
////	CButton::OnLButtonUp(nFlags, point);
////}
//
////void CFFTBtn::OnRButtonDown(UINT nFlags, CPoint point) 
////{
////	// TODO: Add your message handler code here and/or call default
////	Zoomed = false;
////	m_pCurYdata = NULL;
////	ReleaseCapture();
////	if (bShowPSD)
////	{
////		lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
////		m_currentMinf = 0;
////		m_currentMaxf = 250000;
////	}
////	else
////	{
////		lastFrameRect = CRect(0,0,TotalLength,0);
////		m_currentMinX = 0;
////		m_currentMaxX = TotalLength;
////	}
////	scaleY = 0;
////	Invalidate(FALSE);
////	CButton::OnRButtonDown(nFlags, point);
////}
//
////void CFFTBtn::ClearData()
////{
////	m_pTotalYdata = NULL;
////	m_TotalLength = 0;
////	m_pCurYdata = NULL;
////	m_CurLength = 0;
////	m_pPSDYdata =  NULL;
////	m_bZoomed = false;
////	m_bShowFrame = false;
////	m_bShowFFT = false;
////	m_globalMaxY=0;
////	m_globalMinY=0;
////	m_globalMaxX=0;
////	m_globalMinX=0;
////	m_globalMaxf=0;
////	m_globalMinf=0;
////	m_globalMaxPSD=0;
////	m_currentMaxX=0;
////	m_currentMinX=0;
////	m_currentMaxY=0;
////	m_currentMinY=0;
////	m_currentMaxf=0;
////	m_currentMinf=0;
////	m_scaleY = 0;
////}
//
////void CFFTBtn::GetPSD()
////{
////	if(m_pTotalYdata == NULL) return;
////	ClearPSDMalloc();
////	m_globalMaxPSD = 0;
////	PSDreal = new double[nextPow2(TotalLength)];
////	PSDimag = new double[nextPow2(TotalLength)];
////	
////	FFT(nextPow2(TotalLength),false,m_pTotalYdata,NULL,PSDreal,PSDimag);
//////	RealFFT(nextPow2(TotalLength),m_pTotalYdata,PSDreal,PSDimag);
////	for (int i=0;i<nextPow2(TotalLength)/2;i++) 
////	{
////		PSDreal[i]=PSDreal[i]*PSDreal[i]+PSDimag[i]*PSDimag[i];
////		if (m_globalMaxPSD<PSDreal[i]) m_globalMaxPSD=PSDreal[i];
////	}
////	if(m_globalMaxPSD>1e-6) scaleY = m_GraphRect.Height()/(m_globalMaxPSD);	
////	m_pPSDYdata = PSDreal;
////	m_globalMinf = 0;
////	CurLength = nextPow2(TotalLength)/2;
////	m_currentMinf = 0;
////	m_currentMaxf = 250000;
////}
//
//
////void CFFTBtn::OnRButtonDblClk(UINT nFlags, CPoint point) 
////{
////	if(bShowPSD)
////	{
////		bShowPSD = false;
////	}
////	else 
////	{
////		if(!m_pPSDYdata) GetPSD();
////		bShowPSD = true;
////		m_currentMinf = 0;
////		m_currentMaxf = 250000;
////	}
////	OnRButtonDown(nFlags,point); 
////	CButton::OnRButtonDblClk(nFlags, point);
////}
//
void CFFTBtn::DrawAxis(CDC *pDC, CRect *pRect)   //�����������
{
	int x0=pRect->left+1;
	int y0=0;
	int num=10;

	CPen pen1(PS_SOLID,2,RGB(0,0,0));
	CPen* pOldPen;
	pOldPen=pDC->SelectObject(&pen1);

	pDC->MoveTo(pRect->left+1,pRect->top);		pDC->LineTo(pRect->left+1,pRect->bottom);   //��������
	pDC->MoveTo(pRect->left+1,pRect->top+1);	pDC->LineTo(pRect->right,pRect->top+1);     //ˮƽ�϶���
	pDC->MoveTo(pRect->right-1,pRect->top);		pDC->LineTo(pRect->right-1,pRect->bottom);  //��������
	pDC->MoveTo(pRect->left+1,pRect->bottom-1);	pDC->LineTo(pRect->right,pRect->bottom-1);  //ˮƽ����

	CPen pen2(PS_DOT,1,RGB(30,0,0));
	pDC->SelectObject(&pen2);

	double powerUnit = pow(10,floor(log10(m_dataBase.m_scaleY)));

	y0=(pRect->top + pRect->bottom)/2;
	//������ƽ��������
	for(int i=0;i<5;i++)
	{
		pDC->MoveTo(pRect->left, y0-(pRect->Height()/10)*i);		
		pDC->LineTo(pRect->right,y0-(pRect->Height()/10)*i);//��������
	}

	for(int i=0;i<5;i++)
	{
		pDC->MoveTo(pRect->left, y0+(pRect->Height()/10)*i);		
		pDC->LineTo(pRect->right,y0+(pRect->Height()/10)*i);//��������
	}


	//������ƽ��������
	for(int j=1;j<9;j++)
	{
		pDC->MoveTo(pRect->left+(pRect->Width()/9)*j,pRect->top);		
		pDC->LineTo(pRect->left+(pRect->Width()/9)*j,pRect->bottom);//������
		//pDC->MoveTo(pRect->left+(pRect->Width()/10)*j,pRect->top);		
		//pDC->LineTo(pRect->left+(pRect->Width()/10)*j,pRect->bottom);//�������
	}

	pDC->SelectObject(pOldPen);

}



void CFFTBtn::DrawUnits(CDC *pDC, CRect *pRect)   //�������
{
	int y0;
	pDC->SetBkMode(TRANSPARENT);
	/*pDC->SetTextAlign(TA_RIGHT);*/
	COLORREF color = pDC->SetTextColor(RGB(0,0,0));
	int nScalesY,nScalesX;
	nScalesY=(int)log10(m_dataBase.m_globalMaxY);
	nScalesY=Pow10(nScalesY);
	if(nScalesY<1000) nScalesY=1;
	CString out,strScales;
	out.Format(TEXT("%10.2f"),m_dataBase.m_globalMaxY/nScalesY);
	out.TrimLeft();
	y0 = pRect->bottom-m_dataBase.m_bottomMarginY;    //y 0�������

	MyDrawText(pDC,out,CRect(pRect->left,pRect->top+10,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);  //��y�������ֵ
	//CRect drawRT(pRect->left+leftMarginX-5,pRect->bottom-bottomMarginY,pRect->left+leftMarginX+40,pRect->bottom-bottomMarginY+15);
	int yHeight=(pRect->bottom-m_dataBase.m_bottomMarginY)-(pRect->top+m_dataBase.m_topMarginY);  //y���������߶�
	MyDrawText(pDC,TEXT("0"),CRect(pRect->left,y0-15,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);   //��y��0��
	//////////////////////////////////////////////////////////////////////////
	nScalesX=(int)log10(m_dataBase.m_currentMaxf);
	nScalesX=Pow10(nScalesX);
	if(nScalesX<1000) nScalesX=1;
	int xWidth=(pRect->right-m_dataBase.m_rightMarginX)-(pRect->left+m_dataBase.m_leftMarginX); //x�᷽��ʵ�ʿ��
	int xxWidth = m_dataBase.m_currentMaxf-m_dataBase.m_currentMinf;   //ʵ��������
	for(int xx=1;xx<10;xx++)  //
	{
		//out.Format(TEXT("%10.2lf"),(m_currentMinf+xx*xxWidth/5)/nScalesX);
		out.Format(TEXT("%10.2lf"),xx*1.0);
		out.TrimLeft();
		MyDrawText(pDC,out,CRect(pRect->left+m_dataBase.m_leftMarginX+(xWidth/9)*(xx-1)-8,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->right,pRect->bottom-m_dataBase.m_bottomMarginY+15));
	}
	out.Format(TEXT("%10.2lf"),10*1.0);
	out.TrimLeft();
	//pDC->DrawText(out,&rc,DT_RIGHT);
	MyDrawText(pDC,out,CRect(pRect->right-40,pRect->bottom-m_dataBase.m_bottomMarginY,pRect->right,pRect->bottom-m_dataBase.m_bottomMarginY+15),DT_RIGHT);
	if(nScalesY>1)
	{
		out = DoubleToScientNum(nScalesY*1.0);
		MyDrawText(pDC,out,CRect(pRect->left,pRect->top,pRect->left+m_dataBase.m_leftMarginX,pRect->bottom),DT_RIGHT);
	}
	if(nScalesX>1)
	{
		/*out.Format(TEXT("x %5.0e"),nScalesX*1.0);*/
		out = _T(" ��λ��kHz  ")+DoubleToScientNum(nScalesX*1.0);
		MyDrawText(pDC,out,CRect(pRect->right-100,pRect->bottom-m_dataBase.m_bottomMarginY/2,pRect->right,pRect->bottom),DT_RIGHT);
	}
	//�ļ���
	CString szFileName = _T("�ļ�����")+m_dataBase.m_szFileName;
	MyDrawText(pDC,szFileName,CRect(pRect->left+m_dataBase.m_leftMarginX,pRect->bottom-m_dataBase.m_bottomMarginY/2,pRect->right,pRect->bottom));   
}


