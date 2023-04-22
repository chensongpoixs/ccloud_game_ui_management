﻿
// MFCApplication1.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "clog.h"
#include "clog.h"
#include "ccfg.h"
#include <stdio.h>
// CMFCApplication1App

BEGIN_MESSAGE_MAP(CMFCApplication1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication1App 构造

CMFCApplication1App::CMFCApplication1App()
	: m_application_wnd(NULL)
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCApplication1App 对象

CMFCApplication1App theApp;
#include <iostream>
using namespace chen;
// CMFCApplication1App 初始化
static void check_file(const char* file_name)
{
	//access
	//if (::_access(file_name, 0) != 0)
	{
		FILE* fp = ::fopen(file_name, "r");
		if (!fp)
		{
			FILE* fp = ::fopen(file_name, "wb+");
		}
		if (fp)
		{
			::fclose(fp);
			fp = NULL;
		}
	}
}
BOOL CMFCApplication1App::InitInstance()
{

	
	LOG::init("./log", "CloudRenderServerMgr");
	const char * config_file = "./CloudRenderServerMgr.cfg";
	check_file(config_file);
	if (!g_cfg.init(config_file))
	{
		using namespace chen;
		 ERROR_EX_LOG("not find CloudRenderServerMgr.cfg failed !!!");
		LOG::destroy();
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	//CShellManager *pShellManager = new CShellManager;

	//// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("@CloudRenderServerMgr"));

	bool AlreadyRunning = false;

	Sleep(1000);
	HANDLE hMutexOneInstance = ::CreateMutex(NULL, FALSE, _T("CloudRenderServerMgr_{44D28BCA-7F46-4af2-A1FF-36EE0DAC7CD2}"));

	AlreadyRunning = (::GetLastError() == ERROR_ALREADY_EXISTS ||
		::GetLastError() == ERROR_ACCESS_DENIED);

	if (AlreadyRunning)
	{
		MessageBox(NULL, _T("One instance of this aplication is already running."), _T("CloudRenderServerMgr"), 0);
		/*g_cfg.destroy();
		using namespace chen;
		LOG::destroy();*/
		return FALSE;
	}

	m_application_wnd = new CMFCApplication1Dlg();
	m_pMainWnd = m_application_wnd;
	m_application_wnd->Create(IDD_MFCAPPLICATION1_DIALOG);
	
	ShowWindow(m_pMainWnd->GetSafeHwnd(), SW_SHOW);


	return TRUE;
	CMFCApplication1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	dlg.destroy();
	g_cfg.destroy();
	using namespace chen;
	LOG::destroy();
	// 删除上面创建的 shell 管理器。
	/*if (pShellManager != nullptr)
	{
		delete pShellManager;
	}*/

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CMFCApplication1App::ExitInstance()
{
	if(m_application_wnd)
	{
		m_application_wnd->destroy();
		m_application_wnd->DestroyWindow();
		
	}
	g_cfg.destroy();
	using namespace chen;
	LOG::destroy();
	m_application_wnd = NULL;
	return  CWinApp::ExitInstance();
}

