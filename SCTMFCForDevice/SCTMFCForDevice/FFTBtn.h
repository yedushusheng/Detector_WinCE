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

	//void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);   //画按钮函数
	void InitData();
	void InitScaleY();        //初始化一些数据
	void PrepareData();    //准备画图的数据
	void DrawUnits(CDC *pDC, CRect *pRect);   //画坐标点函数
	void DrawAxis(CDC* pDC,CRect* pRect);   //画坐标框图函数
	void Plotf(CDC *pDC,CRect* pRect);   //画波形图函数
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
