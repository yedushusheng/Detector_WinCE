#pragma once
#include "resource.h"

// CTabOrgDlg �Ի���

class CTabOrgDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabOrgDlg)

public:
	CTabOrgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabOrgDlg();
   /* CBrush m_brush;*/
// �Ի�������
	enum { IDD = IDD_DLG_TABORG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    /*afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);*/
	DECLARE_MESSAGE_MAP()
};
