#if !defined(AFX_FFTBTN_H__SDGHKJC3_SDG325_SGH45_DSGU7334__INCLUDED_)
#define AFX_FFTBTN_H__SDGHKJC3_SDG325_SGH45_DSGU7334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFFTBtn.h : header file
//


#include "DispPanel.h"
/////////////////////////////////////////////////////////////////////////////


class CFFTBtn : public CDispPanel
{
	// Construction
public:
	CFFTBtn();

public:

	//void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);   //����ť����
	void InitData();
	void InitScaleY();        //��ʼ��һЩ����
	void PrepareData();    //׼����ͼ������
	void DrawUnits(CDC *pDC, CRect *pRect);   //������㺯��
	void DrawAxis(CDC* pDC,CRect* pRect);   //�������ͼ����
	void Plotf(CDC *pDC,CRect* pRect);   //������ͼ����
//	//void ClearUnits(CDC* pDC);
//	// Implementation
//	//void GetPSD();
//
	virtual ~CFFTBtn();
//	// Generated message map functions
public:
	//double m_dPower[16384];
protected:
	//{{AFX_MSG(CDispPanel)
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_)
