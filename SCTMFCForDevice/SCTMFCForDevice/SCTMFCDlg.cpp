// SCTMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SCTMFC.h"
#include "SCTMFCDlg.h"
#include "Global.h"

//#include "FFTBtn.h"
#include "FileManager.h"
#include "FFT.h"
#include "Sipapi.h"
//#include <aygshell.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSCTMFCDlg 对话框
//static CRITICAL_SECTION CSCTMFCDlg::m_cs = {};
CSCTMFCDlg::CSCTMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCTMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	/*InitializeCriticalSection(&m_cs);*/
	/*m_hWndTabFFTWave = NULL;
	m_hWndTabOrgWave = NULL;*/
}

CSCTMFCDlg::~CSCTMFCDlg()
{
	HWND hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);
	::ShowWindow(hTaskBar,SW_SHOWNORMAL);
	/*DeleteCriticalSection(&m_cs);*/
}

void CSCTMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabMain);
}

BEGIN_MESSAGE_MAP(CSCTMFCDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_SUBMENU_EXIT, &CSCTMFCDlg::OnExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CSCTMFCDlg::OnTcnSelchangeTabMain)
	ON_COMMAND(ID_SUBMENU_TASKBAR, &CSCTMFCDlg::OnTaskbar)
	ON_COMMAND(ID_SUBMENU_OPEN, &CSCTMFCDlg::OnOpen)
END_MESSAGE_MAP()


// CSCTMFCDlg 消息处理程序

BOOL CSCTMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	HINSTANCE hInst = AfxGetResourceHandle();
	HWND hwndCB = CommandBar_Create(hInst,this->GetSafeHwnd(),1);
	if(hwndCB == NULL)
	{
		TRACE0("Failed   to   create   CommandBar/n");
	}
	if(!CommandBar_InsertMenubar(hwndCB,hInst,IDR_MENU_MAIN,3))
	{
		TRACE0("Failed   Insert   Menu   to   CommandBar/n");
	}
    //LoadMyMenu();
    
    LoadTab();

	HWND hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);
	::ShowWindow(hTaskBar,SW_HIDE);

	m_bShowTaskBar = false;
    /*SipShowIM(SIPF_OFF);*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CSCTMFCDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_SCTMFC_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_SCTMFC_DIALOG));
	}
}
#endif


//加载tab控件
void CSCTMFCDlg::LoadTab()
{
	m_tabMain.InsertItem(0,TEXT("原始波形"));
    m_tabMain.InsertItem(1,TEXT("频谱图"));
	m_tab_org.Create(IDD_DLG_TABORG,GetDlgItem(IDC_TAB_MAIN));
    m_tab_fft.Create(IDD_DLG_TABFFT,GetDlgItem(IDC_TAB_MAIN));
	
	CRect rc;
	this->GetClientRect(&rc);    //top下移是为了不盖着menu菜单
	rc.DeflateRect(1,23,1,1);
	m_tabMain.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),SW_SHOWNORMAL);
	m_tabMain.GetClientRect(&rc);
	rc.DeflateRect(3,23,3,3);   //top下移是为了不盖着切换tab页
    m_tab_org.MoveWindow(rc);
	
	m_tab_fft.MoveWindow(rc);
    m_tab_org.ShowWindow(true);
	m_tab_fft.ShowWindow(false);
    m_tabMain.SetCurSel(0);
}


void CSCTMFCDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
    int curSel = m_tabMain.GetCurSel();
	switch(curSel)
	{
	case 0:
		{         
            m_tab_fft.ShowWindow(false);
			m_tab_org.ShowWindow(true);
			break;
		}
	case 1:
		{
			m_tab_fft.ShowWindow(true);
			m_tab_org.ShowWindow(false);
			break;
		}
	default:
		break;
	}

}


void CSCTMFCDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	//CDialog::EndDialog(0);
	CDialog::EndDialog(0);
}



//隐藏或者显示系统状态栏
void CSCTMFCDlg::OnTaskbar()
{
	// TODO: 在此添加命令处理程序代码
	HWND hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);
	if(m_bShowTaskBar)    //如果之前的状态为显示 就隐藏
	{
	    ::ShowWindow(hTaskBar,SW_HIDE);
		m_bShowTaskBar = false;
	}else{
        ::ShowWindow(hTaskBar,SW_SHOWNORMAL);
		m_bShowTaskBar = true;
	}
}


DWORD WINAPI CSCTMFCDlg::FFTAnaylizeThread(LPVOID lpVoid)   //FFT变换线程
{
	WaveData* pData = (WaveData*)lpVoid;
	CString filename(pData->szFileName);
	COrgWaveBtn *waveBtn = (COrgWaveBtn *)pData->ptr[0];
    CFFTBtn     *FFTBtn = (CFFTBtn *)pData->ptr[1];
	delete pData;
	pData = NULL;
    int dataLen = GetData(filename,waveBtn->m_dataBase.GetTotalData());
	if(dataLen == -1)
	{
		waveBtn->m_szTips = _T("数据解析错误，请重新加载！");
		waveBtn->m_bShowTips = TRUE;  //显示提示信息
		waveBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //刷新窗口消息
        FFTBtn->m_szTips = _T("数据解析错误，请重新加载！");
		FFTBtn->m_bShowTips = TRUE;  //显示提示信息
		FFTBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //刷新窗口消息
		return 0;
	}	 
	waveBtn->m_bShowTips = FALSE;  //显示数据   画图
	waveBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //刷新窗口消息
	FFT(waveBtn->m_dataBase.GetTotalData(),FFTBtn->m_dataBase.GetTotalData());   //进行fft变换 显示fft	
	FFTBtn->m_bShowTips = FALSE;  //显示数据   画图
	FFTBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //刷新窗口消息

	return 0;
}

void CSCTMFCDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	/*SipShowIM(SIPF_OFF);*/
	CFileDialog FileDlg(true,TEXT("wav"),NULL,
		OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		TEXT("wav files(*.wav)|*.wav||"));
	FileDlg.m_ofn.nMaxFile = 200 * MAX_PATH;  
	FileDlg.m_ofn.lpstrFile = new TCHAR[FileDlg.m_ofn.nMaxFile]; 
	ZeroMemory(FileDlg.m_ofn.lpstrFile, sizeof(TCHAR) * FileDlg.m_ofn.nMaxFile); 
	if(IDCANCEL == FileDlg.DoModal())
         return;
	SipShowIM(SIPF_OFF);
	POSITION pos_file;
	pos_file = FileDlg.GetStartPosition();
	CStringArray filenames;
	while(pos_file != NULL)
		filenames.Add(FileDlg.GetNextPathName(pos_file));
    //从这里开始就可以使用多线程了 防止阻塞用户界面
    for(int i = 0;i<filenames.GetSize();++i)
	{
        m_btnOrg.m_szTips = _T("正在解析数据中，请稍后。。。");
		m_btnOrg.CreatBtn(&m_tab_org,ID_OWERDRAW_BTN+2*i,GetFileName(filenames[i]));
		m_btnFFT.m_szTips = _T("正在解析数据中，请稍后。。。");
		m_btnFFT.CreatBtn(&m_tab_fft,ID_OWERDRAW_BTN+2*i+1,GetFileName(filenames[i]));

		HANDLE hFFTThreat;
		DWORD  dwFFTThreat;
       /* WaveData *pOrg = new WaveData;*/
        WaveData *pFFT = new WaveData;
        USES_CONVERSION;
        strcpy(pFFT->szFileName,T2A(filenames[i]));
        pFFT->ptr[0] = (void *)&m_btnOrg;
        pFFT->ptr[1] =  (void *)&m_btnFFT;
        hFFTThreat = CreateThread(NULL,0,FFTAnaylizeThread,(LPVOID)pFFT,0,&dwFFTThreat);
		CloseHandle(hFFTThreat);
	}

    delete []FileDlg.m_ofn.lpstrFile;
	FileDlg.m_ofn.lpstrFile = NULL;
}

void CSCTMFCDlg::ShowRect(CRect rect)
{
	CString s;
	s.Format(_T("rect.left = %d; rect.top = %d; rect.width = %d; rect.height = %d\n"),
		rect.left,rect.top,rect.Width(),rect.Height());
	MessageBox(s,_T("矩形"),MB_OK);
}


