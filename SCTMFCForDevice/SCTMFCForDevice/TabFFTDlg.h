#pragma once
#include "resource.h"

// CTabFFT 对话框

class CTabFFTDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabFFTDlg)

public:
	CTabFFTDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabFFTDlg();
   /* CBrush m_brush;*/
// 对话框数据
	enum { IDD = IDD_DLG_TABFFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    /*BOOL OnInitDialog();*/
	/*afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);*/
	DECLARE_MESSAGE_MAP()
};
