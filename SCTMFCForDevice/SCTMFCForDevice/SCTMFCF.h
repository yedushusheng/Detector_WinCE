// SCTMFCForDevice.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CSCTMFCApp:
// �йش����ʵ�֣������ SCTMFCForDevice.cpp
//

class CSCTMFCApp : public CWinApp
{
public:
	CSCTMFCApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSCTMFCApp theApp;
