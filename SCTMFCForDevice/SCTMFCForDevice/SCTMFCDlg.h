// SCTMFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
//#include<windows.h>
// CSCTMFCDlg �Ի���
#include "TabFFTDlg.h"
#include "TabOrgDlg.h"

#include "OrgWaveBtn.h"
#include "FFTBtn.h"



class CSCTMFCDlg : public CDialog
{
// ����
public:
	CSCTMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��
    ~CSCTMFCDlg();	// ��׼��������
// �Ի�������
	enum { IDD = IDD_SCTMFC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��




public:
	void LoadTab();
	void ShowRect(CRect rect);
	//static DWORD WINAPI GetWaveDataThread(LPVOID lpVoid);   //����wave�ļ������߳�
	static DWORD WINAPI FFTAnaylizeThread(LPVOID lpVoid);   //FFT�任�߳�
// ʵ��
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
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	//afx_msg void OnClose();
	
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTaskbar();
	afx_msg void OnOpen();
};
