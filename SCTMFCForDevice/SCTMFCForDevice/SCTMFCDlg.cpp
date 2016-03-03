// SCTMFCDlg.cpp : ʵ���ļ�
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

// CSCTMFCDlg �Ի���
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


// CSCTMFCDlg ��Ϣ�������

BOOL CSCTMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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


//����tab�ؼ�
void CSCTMFCDlg::LoadTab()
{
	m_tabMain.InsertItem(0,TEXT("ԭʼ����"));
    m_tabMain.InsertItem(1,TEXT("Ƶ��ͼ"));
	m_tab_org.Create(IDD_DLG_TABORG,GetDlgItem(IDC_TAB_MAIN));
    m_tab_fft.Create(IDD_DLG_TABFFT,GetDlgItem(IDC_TAB_MAIN));
	
	CRect rc;
	this->GetClientRect(&rc);    //top������Ϊ�˲�����menu�˵�
	rc.DeflateRect(1,23,1,1);
	m_tabMain.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),SW_SHOWNORMAL);
	m_tabMain.GetClientRect(&rc);
	rc.DeflateRect(3,23,3,3);   //top������Ϊ�˲������л�tabҳ
    m_tab_org.MoveWindow(rc);
	
	m_tab_fft.MoveWindow(rc);
    m_tab_org.ShowWindow(true);
	m_tab_fft.ShowWindow(false);
    m_tabMain.SetCurSel(0);
}


void CSCTMFCDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���������������
	//CDialog::EndDialog(0);
	CDialog::EndDialog(0);
}



//���ػ�����ʾϵͳ״̬��
void CSCTMFCDlg::OnTaskbar()
{
	// TODO: �ڴ���������������
	HWND hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);
	if(m_bShowTaskBar)    //���֮ǰ��״̬Ϊ��ʾ ������
	{
	    ::ShowWindow(hTaskBar,SW_HIDE);
		m_bShowTaskBar = false;
	}else{
        ::ShowWindow(hTaskBar,SW_SHOWNORMAL);
		m_bShowTaskBar = true;
	}
}


DWORD WINAPI CSCTMFCDlg::FFTAnaylizeThread(LPVOID lpVoid)   //FFT�任�߳�
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
		waveBtn->m_szTips = _T("���ݽ������������¼��أ�");
		waveBtn->m_bShowTips = TRUE;  //��ʾ��ʾ��Ϣ
		waveBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //ˢ�´�����Ϣ
        FFTBtn->m_szTips = _T("���ݽ������������¼��أ�");
		FFTBtn->m_bShowTips = TRUE;  //��ʾ��ʾ��Ϣ
		FFTBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //ˢ�´�����Ϣ
		return 0;
	}	 
	waveBtn->m_bShowTips = FALSE;  //��ʾ����   ��ͼ
	waveBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //ˢ�´�����Ϣ
	FFT(waveBtn->m_dataBase.GetTotalData(),FFTBtn->m_dataBase.GetTotalData());   //����fft�任 ��ʾfft	
	FFTBtn->m_bShowTips = FALSE;  //��ʾ����   ��ͼ
	FFTBtn->SendMessage(WM_SHOWTIPS,NULL,NULL);   //ˢ�´�����Ϣ

	return 0;
}

void CSCTMFCDlg::OnOpen()
{
	// TODO: �ڴ���������������
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
    //�����￪ʼ�Ϳ���ʹ�ö��߳��� ��ֹ�����û�����
    for(int i = 0;i<filenames.GetSize();++i)
	{
        m_btnOrg.m_szTips = _T("���ڽ��������У����Ժ󡣡���");
		m_btnOrg.CreatBtn(&m_tab_org,ID_OWERDRAW_BTN+2*i,GetFileName(filenames[i]));
		m_btnFFT.m_szTips = _T("���ڽ��������У����Ժ󡣡���");
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
	MessageBox(s,_T("����"),MB_OK);
}


