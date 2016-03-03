// SCTMFCDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
//#include<windows.h>
// CSCTMFCDlg 对话框
#include "TabFFTDlg.h"
#include "TabOrgDlg.h"

#include "OrgWaveBtn.h"
#include "FFTBtn.h"



class CSCTMFCDlg : public CDialog
{
// 构造
public:
	CSCTMFCDlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CSCTMFCDlg();	// 标准析构函数
// 对话框数据
	enum { IDD = IDD_SCTMFC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持




public:
	void LoadTab();
	void ShowRect(CRect rect);
	//static DWORD WINAPI GetWaveDataThread(LPVOID lpVoid);   //解析wave文件数据线程
	static DWORD WINAPI FFTAnaylizeThread(LPVOID lpVoid);   //FFT变换线程
// 实现
protected:
	HICON m_hIcon;
	CMenu m_menu;
	BOOL  m_bShowTaskBar;
    
public:
    /*CRITICAL_SECTION m_cs;*/

	CTabCtrl   m_tabMain;
	//HWND m_hWndTabOrgWave,m_hWndTabFFTWave;
	CTabOrgDlg m_tab_org;
	CTabFFTDlg m_tab_fft;
	COrgWaveBtn m_btnOrg;
	CFFTBtn    m_btnFFT;
    //CMenu* m_pMenu;
	
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	//afx_msg void OnClose();
	
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTaskbar();
	afx_msg void OnOpen();
};
