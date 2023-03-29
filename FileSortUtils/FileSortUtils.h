
// FileSortUtils.h : main header file for the PROJECT_NAME application
//

#pragma once

#include "resource.h"		
#include "FileSortController.h"


class CFileSortUtilsApp : public CWinApp
{
public:
	CFileSortUtilsApp();
	~CFileSortUtilsApp();

public:
	virtual BOOL InitInstance();


	CFileSortController m_cController;
	DECLARE_MESSAGE_MAP()
};

extern CFileSortUtilsApp theApp;
