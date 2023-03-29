
// FileSortUtils.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "FileSortUtils.h"
#include "FileSortUtilsDlg.h"
#include "XMLLogger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileSortUtilsApp

BEGIN_MESSAGE_MAP(CFileSortUtilsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFileSortUtilsApp construction

CFileSortUtilsApp::CFileSortUtilsApp():m_cController(4)
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	CXMLLogger::Instance()->Error(_T("Test"));
	CXMLLogger::Instance()->Notice(_T("Test1"));
}


CFileSortUtilsApp theApp;


// CFileSortUtilsApp initialization

BOOL CFileSortUtilsApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CFileSortUtilsDlg dlg;
	m_pMainWnd = &dlg;
	m_cController.SetHandler(m_pMainWnd);
	INT_PTR nResponse = dlg.DoModal();
	
	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

	return FALSE;
}

CFileSortUtilsApp::~CFileSortUtilsApp()
{
	CXMLLogger::Release();
}
