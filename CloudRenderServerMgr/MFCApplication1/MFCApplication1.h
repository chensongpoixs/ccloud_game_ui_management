﻿
// MFCApplication1.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


class CMFCApplication1Dlg;

// CMFCApplication1App:
// 有关此类的实现，请参阅 MFCApplication1.cpp
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// 实现

	DECLARE_MESSAGE_MAP()

private:
	CMFCApplication1Dlg * m_application_wnd;
};

extern CMFCApplication1App theApp;
