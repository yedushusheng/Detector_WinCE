// TabOrgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TabOrgDlg.h"
#include "Global.h"

// CTabOrgDlg 对话框

IMPLEMENT_DYNAMIC(CTabOrgDlg, CDialog)

CTabOrgDlg::CTabOrgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabOrgDlg::IDD, pParent)
{
    /*m_brush.CreateSolidBrush(MY_BACKCOLOR);*/
}

CTabOrgDlg::~CTabOrgDlg()
{
}

void CTabOrgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabOrgDlg, CDialog)
	/*ON_WM_CTLCOLOR()*/
END_MESSAGE_MAP()


//HBRUSH CTabOrgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
//	//在这加一条是否为对话框的判断语句 
//	//if(nCtlColor == CTLCOLOR_DLG) 
//	return m_brush; //返加红色刷子 
//	return hbr; 
//}

// CTabOrgDlg 消息处理程序
