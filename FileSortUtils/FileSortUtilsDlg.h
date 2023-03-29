
// FileSortUtilsDlg.h : header file
//

#pragma once

// CFileSortUtilsDlg dialog
class CFileSortUtilsDlg : public CDialogEx
{
// Construction
public:
	CFileSortUtilsDlg(CWnd* pParent = nullptr);	// standard constructor
	~CFileSortUtilsDlg() {};
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESORTUTILS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void UpdateTaskList();

// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void DisableElementsByRun();
	void EnableElements();
public:
	afx_msg void OnBnClickedRunButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedInputBrowseButton();
	afx_msg void OnBnClickedStopButton();
	afx_msg void OnBnClickedOutputBrowseButton();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadioAsc();
	afx_msg void OnBnClickedRadioDesc();
};
