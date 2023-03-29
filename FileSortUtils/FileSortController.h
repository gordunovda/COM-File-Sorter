#pragma once

#include "..\FileSorter\FileSorter_i.h"

using namespace std;

class CFileSortController
{
public:
	CFileSortController(unsigned int n = 4);
	~CFileSortController();
	void ThreadDelete();
	void SetInputDir(CString  csDir);
	void SetOutputDir(CString  csDir);
	void SetMethodSort(FILE_SORT_METHOD iMethod);
	HRESULT Run();
	void Stop();

	void SetHandler(CWnd* pWnd) { m_pHandler = pWnd;  };

	vector<CString> GetTaskList() {
		return m_sTaskList;
	};
protected:
	HRESULT LoadTask(IFileSort*);
	void ThreadProcThunk();

private:
	vector<IFileSort*> m_pFileSort;
	vector<int> m_iProgress;
	vector<CString> m_sTaskList;
	CString m_csOutputDir;
	CString m_csInputDir;
	FILE_SORT_METHOD m_iMethodSort;
	mutex m_mLock;
	thread* m_pThread;
	bool m_bRunning;
	CWnd* m_pHandler;
};

