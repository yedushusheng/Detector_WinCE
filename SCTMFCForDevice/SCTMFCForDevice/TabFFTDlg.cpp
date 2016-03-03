// TabFFT.cpp : 实现文件
//

#include "stdafx.h"
#include "TabFFTDlg.h"
#include "Global.h"

// CTabFFT 对话框

IMPLEMENT_DYNAMIC(CTabFFTDlg, CDialog)

CTabFFTDlg::CTabFFTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabFFTDlg::IDD, pParent)
{
    /* m_brush.CreateSolidBrush(MY_BACKCOLOR);*/
}

CTabFFTDlg::~CTabFFTDlg()
{
}

void CTabFFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


//BOOL CTabFFTDlg::OnInitDialog()
//{
//	
//	CDialog::OnInitDialog();
//	return TRUE;
//}

//HBRUSH CTabFFTDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
//	//在这加一条是否为对话框的判断语句 
//	//if(nCtlColor == CTLCOLOR_DLG) 
//		return m_brush; //返加红色刷子 
//	return hbr; 
//
//}

BEGIN_MESSAGE_MAP(CTabFFTDlg, CDialog)
	/*ON_WM_CTLCOLOR()*/
END_MESSAGE_MAP()


// CTabFFT 消息处理程序
