// TabFFT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabFFTDlg.h"
#include "Global.h"

// CTabFFT �Ի���

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
//	//�����һ���Ƿ�Ϊ�Ի�����ж���� 
//	//if(nCtlColor == CTLCOLOR_DLG) 
//		return m_brush; //���Ӻ�ɫˢ�� 
//	return hbr; 
//
//}

BEGIN_MESSAGE_MAP(CTabFFTDlg, CDialog)
	/*ON_WM_CTLCOLOR()*/
END_MESSAGE_MAP()


// CTabFFT ��Ϣ�������
