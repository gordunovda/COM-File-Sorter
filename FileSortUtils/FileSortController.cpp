#include "pch.h"
#include "FileSortController.h"
#include "XMLLogger.h"

using namespace std;


CFileSortController::CFileSortController(unsigned int n) : m_bRunning(false), m_pHandler(nullptr), m_pThread(nullptr)
{
	if (FAILED(CoInitialize(NULL)))
	{
		MessageBox(0, _T("FileSort Com not find"), _T("FileSort Com not find"), 0);
		CXMLLogger::Instance()->Error(_T("FileSort Com not find"));
	}
	IFileSort* pFileSort;
	for (int i = 0; i < n; i++)
	{
		HRESULT hr = CoCreateInstance(CLSID_FileSort, NULL, CLSCTX_ALL, IID_IFileSort, (void**)&pFileSort);
		if (SUCCEEDED(hr))
		{
			m_pFileSort.push_back(pFileSort);
			CXMLLogger::Instance()->Notice(_T("Create #%d instace of FileSort"), i);
		}
		else
			CXMLLogger::Instance()->Error(_T("Can't create #%d instace of FileSort"), i);
	}

	m_iProgress.resize(m_pFileSort.size(), 0);
	m_iMethodSort = FSM_ASC;
}

CFileSortController::~CFileSortController()
{
	Stop();
	ThreadDelete();

	for (auto p : m_pFileSort)
		p->Release();
	
	CoUninitialize();
}

void CFileSortController::SetInputDir(CString csDir)
{
	m_sTaskList.clear();
	HANDLE dir;
	WIN32_FIND_DATA file_data;
	CString  file_name, full_file_name;
	if ((dir = FindFirstFile((csDir + "/*"), &file_data)) == INVALID_HANDLE_VALUE)
	{
		CXMLLogger::Instance()->Error(_T("Invalide directory input directory: %s"), csDir);
	}

	while (FindNextFile(dir, &file_data)) {
		file_name = file_data.cFileName;
		full_file_name = csDir + file_name;
		CString file(file_data.cFileName);
		CString ext(file.Right(file.GetLength() - file.ReverseFind(_T('.'))));
		if (file != _T(".") && file != _T("..") && CString(ext) == _T(".bin"))
		{
			m_sTaskList.push_back(file);
			CXMLLogger::Instance()->Notice(_T("Add file to task: %s"), file);
		}
	}
	m_csInputDir = csDir;
}

void CFileSortController::SetOutputDir(CString sDir)
{
	m_csOutputDir = sDir;
	CXMLLogger::Instance()->Notice(_T("Set output dir: %s"), sDir);
}

HRESULT CFileSortController::LoadTask(IFileSort* p)
{
	BSTR inFile = CString(m_csInputDir + _T("\\") + m_sTaskList.back()).AllocSysString();
	BSTR outFile = CString(m_csOutputDir + _T("\\") + m_sTaskList.back()).AllocSysString();
	p->SetInputFile(inFile);
	p->SetOutputFile(outFile);
	p->SetMethodSort(m_iMethodSort);
	SysFreeString(inFile);
	SysFreeString(outFile);
	m_sTaskList.pop_back();

	HRESULT  hr = p->Run();
	if (SUCCEEDED(hr))
		CXMLLogger::Instance()->Notice(_T("Task %s running..."), inFile);
	else
		CXMLLogger::Instance()->Error(_T("Task %s error with code %d"), inFile, hr);
	return hr;
}

HRESULT CFileSortController::Run()
{
	if (m_csInputDir.IsEmpty() || m_csOutputDir.IsEmpty())
		return E_FAIL;

	{
		lock_guard<mutex> lock(m_mLock);
		m_bRunning = true;
	}
	ThreadDelete();

	m_pThread = new thread([](LPVOID pThis) {((CFileSortController*)pThis)->ThreadProcThunk(); }, this);
	return S_OK;
}


void CFileSortController::ThreadProcThunk()
{
	HRESULT hr;
	int uCountRunning = 0;
	bool bListUpdate = false;
	int state;
	int iProgress;

	while ((uCountRunning || !m_sTaskList.empty()) && m_bRunning)
	{
		uCountRunning = 0;
		for (int i = 0;  i < m_pFileSort.size(); i++)
		{
			m_pFileSort[i]->GetState(&state);
			bListUpdate = state == FSS_FINISH;
			if (state == FSS_CREATED || state == FSS_FINISH)
			{
				if (!m_sTaskList.empty())
				{
					hr = LoadTask(m_pFileSort[i]);
					if (SUCCEEDED(hr))
						uCountRunning++;
				}
			}
			else
			{
				uCountRunning++;
			}

			m_pFileSort[i]->GetProgress(&iProgress);

			if (iProgress != m_iProgress[i])
			{
				m_iProgress[i] = iProgress;

				if (m_pHandler)
					PostMessage(m_pHandler->GetSafeHwnd(), WM_USER_UPDATE_PROGRESS, i, iProgress);

			}

			if (bListUpdate && m_pHandler)
				PostMessage(m_pHandler->GetSafeHwnd(), WM_USER_UPDATE_TASK, 0, 0);

		}
		this_thread::sleep_for(chrono::milliseconds(FSC_UPDATE_TIMEOUT));
	}

	{
		lock_guard<mutex> lock(m_mLock);
		m_bRunning = false;
	}
	if (m_pHandler)
	{
		CXMLLogger::Instance()->Notice(_T("Finish tasks"));
		PostMessage(m_pHandler->GetSafeHwnd(), WM_USER_FINISH_TASKS, 0, 0);
	}

}


void CFileSortController::ThreadDelete()
{
	if (!m_pThread)
		return;
	m_pThread->join();
	delete m_pThread;
	m_pThread = nullptr;
}

void CFileSortController::Stop()
{
	if (!m_bRunning)
		return;
	{
		lock_guard<mutex> lock(m_mLock);
		m_bRunning = false;
	}

	CXMLLogger::Instance()->Notice(_T("Stop tasks..."));
	SetInputDir(m_csInputDir);
	ThreadDelete();

	for (auto p : m_pFileSort)
		p->Stop();
	
	if (m_pHandler)
		PostMessage(m_pHandler->GetSafeHwnd(), WM_USER_UPDATE_TASK, 0, 0);
}

void CFileSortController::SetMethodSort(FILE_SORT_METHOD iMethod)
{
	m_iMethodSort = iMethod;
	CXMLLogger::Instance()->Notice(_T("Change sort method to %s..."), (iMethod == FSM_ASC)?_T("ASC") : _T("DESC"));
}



