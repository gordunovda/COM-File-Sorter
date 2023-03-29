
// FileSortUtilsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FileSortUtils.h"
#include "FileSortUtilsDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileSortUtilsDlg dialog



CFileSortUtilsDlg::CFileSortUtilsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILESORTUTILS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSortUtilsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileSortUtilsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUN_BUTTON, &CFileSortUtilsDlg::OnBnClickedRunButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CFileSortUtilsDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_INPUT_BROWSE_BUTTON, &CFileSortUtilsDlg::OnBnClickedInputBrowseButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CFileSortUtilsDlg::OnBnClickedStopButton)
	ON_BN_CLICKED(IDC_OUTPUT_BROWSE_BUTTON, &CFileSortUtilsDlg::OnBnClickedOutputBrowseButton)
	ON_BN_CLICKED(IDC_RADIO_ASC, &CFileSortUtilsDlg::OnBnClickedRadioAsc)
	ON_BN_CLICKED(IDC_RADIO_DESC, &CFileSortUtilsDlg::OnBnClickedRadioDesc)
END_MESSAGE_MAP()


// CFileSortUtilsDlg message handlers

BOOL CFileSortUtilsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetRange32(0, 100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS2))->SetRange32(0, 100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS3))->SetRange32(0, 100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS4))->SetRange32(0, 100);
	((CButton*)GetDlgItem(IDC_RADIO_ASC))->SetCheck(true);
	
	EnableElements();

	return TRUE;  
}

void CFileSortUtilsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileSortUtilsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileSortUtilsDlg::OnBnClickedRunButton()
{
	if (FAILED(theApp.m_cController.Run()))
		MessageBox(_T("Error run params not set"));
	else
		DisableElementsByRun();

}


void CFileSortUtilsDlg::OnBnClickedCloseButton()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void CFileSortUtilsDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CFileSortUtilsDlg::OnBnClickedInputBrowseButton()
{
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_EDIT_INPUT)->SetWindowText(dlg.GetPathName());
		theApp.m_cController.SetInputDir(dlg.GetPathName());
		UpdateTaskList();
	}
}

void CFileSortUtilsDlg::UpdateTaskList()
{
	CListBox* ctrl = (CListBox*)GetDlgItem(IDC_TASK_LIST);
	ctrl->ResetContent();
	auto list = theApp.m_cController.GetTaskList();
	for (auto item : list)
	{
		ctrl->AddString(item);
	}
}

LRESULT CFileSortUtilsDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	vector<UINT> progress = {IDC_PROGRESS1, IDC_PROGRESS2, IDC_PROGRESS3, IDC_PROGRESS4 };
	switch(message)
	{
	case WM_USER_UPDATE_TASK:
		UpdateTaskList();
		break;
	case WM_USER_UPDATE_PROGRESS:
		((CProgressCtrl*)GetDlgItem(progress[(int)wParam]))->SetPos((int)lParam);
		break;
	case WM_USER_FINISH_TASKS:
		EnableElements();
		break;
	}
	return __super::WindowProc(message, wParam, lParam);
}

void CFileSortUtilsDlg::DisableElementsByRun()
{
	GetDlgItem(IDC_OUTPUT_BROWSE_BUTTON)->EnableWindow(false);
	GetDlgItem(IDC_INPUT_BROWSE_BUTTON)->EnableWindow(false);
	GetDlgItem(IDC_RUN_BUTTON)->EnableWindow(false);
	GetDlgItem(IDC_RADIO_ASC)->EnableWindow(false);
	GetDlgItem(IDC_RADIO_DESC)->EnableWindow(false);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(true);
	
}

void CFileSortUtilsDlg::EnableElements()
{
	GetDlgItem(IDC_OUTPUT_BROWSE_BUTTON)->EnableWindow(true);
	GetDlgItem(IDC_INPUT_BROWSE_BUTTON)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_ASC)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_DESC)->EnableWindow(true);
	GetDlgItem(IDC_RUN_BUTTON)->EnableWindow(true);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(false);
}

void CFileSortUtilsDlg::OnBnClickedStopButton()
{
	theApp.m_cController.Stop();
	EnableElements();
}


void CFileSortUtilsDlg::OnBnClickedOutputBrowseButton()
{
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowText(dlg.GetPathName());
		theApp.m_cController.SetOutputDir(dlg.GetPathName());
		UpdateTaskList();
	}
}




void CFileSortUtilsDlg::OnBnClickedRadioAsc()
{
	theApp.m_cController.SetMethodSort(FSM_ASC);
}


void CFileSortUtilsDlg::OnBnClickedRadioDesc()
{
	theApp.m_cController.SetMethodSort(FSM_DESC);
}
