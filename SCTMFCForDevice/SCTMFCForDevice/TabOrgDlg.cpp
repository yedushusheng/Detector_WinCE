// TabOrgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabOrgDlg.h"
#include "Global.h"

// CTabOrgDlg �Ի���

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
//	//�����һ���Ƿ�Ϊ�Ի�����ж���� 
//	//if(nCtlColor == CTLCOLOR_DLG) 
//	return m_brush; //���Ӻ�ɫˢ�� 
//	return hbr; 
//}

// CTabOrgDlg ��Ϣ�������
