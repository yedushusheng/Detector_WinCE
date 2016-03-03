#if !defined(AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_)
#define AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispPanel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDispPanel window
#include "DataBase.h"


#define WM_SHOWTIPS       (WM_USER+1)
//#define WM_GETDATAERR        (WM_USER+2)

class CDispPanel : public CButton
{
// Construction
public:
	CDispPanel();
public:
	static int Comparedouble(const void *pval1, const void *pval2);   //����Ϊdouble�����������

// Attributes
public:
	
	
	
	
    //void   ClearPSDMalloc();
	void   ClearData();
	//void DrawOrgAxis(CDC *pDC, CRect *pRect);   //��ԭʼ�������������
	//void DrawFFTAxis(CDC *pDC, CRect *pRect);   //��FFT�������������
	
// Operations
public:
    CDataBase    m_dataBase;
	BOOL         m_bShowTips;
	CString      m_szTips;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDispPanel)
public:
	virtual void InitData();   //������ʼ������
	virtual void CreatBtn(CWnd* pRarentWnd,UINT uID,CString szFileName,BOOL bShowTips = TRUE);
	void         MyDrawText(CDC *pCDC,const CString& str,CRect rect,UINT nFormat = DT_LEFT);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);   //����ť����
	virtual void WaitTips(LPDRAWITEMSTRUCT lpDrawItemStruct);   //��ʾ�ȴ�����
    virtual void MyDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);   //����׼���ú�ͼ����
	virtual void InitScaleY();        //��ʼ��һЩ����
	virtual void PrepareData();    //׼����ͼ������
	virtual void DrawUnits(CDC *pDC, CRect *pRect);   //������㺯��
	virtual void DrawAxis(CDC* pDC,CRect* pRect);   //�������ͼ����
	virtual void Plotf(CDC *pDC,CRect* pRect);   //������ͼ����
	virtual void ClearUnits(CDC* pDC);
	
	//}}AFX_VIRTUAL

// Implementation

	
	//void DrawFFTUnits(CDC *pDC, CRect *pRect);
	//void DrawOrgUnits(CDC *pDC, CRect *pRect);
	//void GetPSD();
	
	virtual ~CDispPanel();
    virtual void PreSubclassWindow();
	// Generated message map functions
protected:
	//{{AFX_MSG(CDispPanel)
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
    afx_msg LRESULT OnShowTips(WPARAM, LPARAM);
    /*afx_msg LRESULT OnGetDataErr(WPARAM, LPARAM);*/
	DECLARE_MESSAGE_MAP()
public:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_)
