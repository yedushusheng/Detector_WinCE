#pragma once
#include "resource.h"

// CTabFFT �Ի���

class CTabFFTDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabFFTDlg)

public:
	CTabFFTDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabFFTDlg();
   /* CBrush m_brush;*/
// �Ի�������
	enum { IDD = IDD_DLG_TABFFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    /*BOOL OnInitDialog();*/
	/*afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);*/
	DECLARE_MESSAGE_MAP()
};
