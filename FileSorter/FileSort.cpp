// FileSort.cpp : Implementation of CFileSort

#include "pch.h"
#include "FileSort.h"
#include <fstream>
#include <map>

using namespace std;

// CFileSort

CFileSort::CFileSort(): m_pThread(nullptr)
{
	m_iProgress = 0;
	m_eState = FSS_CREATED;
	m_eSortMethod = FSM_DESC;
}

CFileSort::~CFileSort()
{
	ThreadDelete();
}

STDMETHODIMP CFileSort::SetInputFile(BSTR bsFileName)
{
	lock_guard<mutex> lock(m_mLock);

	if (m_eState != FSS_RUNNING)
	{
		m_csFileInput = bsFileName;
		return S_OK;
	}
	return E_FAIL;
}
STDMETHODIMP CFileSort::GetState(int *x)
{
	lock_guard<mutex> lock(m_mLock);
	*x = m_eState;
	return S_OK;
}

STDMETHODIMP CFileSort::SetOutputFile(BSTR bsFileName)
{
	lock_guard<mutex> lock(m_mLock);

	if (m_eState != FSS_RUNNING)
	{
		m_csFileOutput = bsFileName;
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CFileSort::SetMethodSort(int iMethod)
{
	lock_guard<mutex> lock(m_mLock);

	if (m_eState != FSS_RUNNING)
	{
		m_eSortMethod = static_cast<FILE_SORT_METHOD>(iMethod);
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CFileSort::GetProgress(int* x)
{
	lock_guard<mutex> lock(m_mLock);
	*x = m_iProgress;
	return S_OK;
}

STDMETHODIMP CFileSort::Stop()
{
	if (m_eState != FSS_RUNNING)
		return E_NOT_VALID_STATE;

	{
		lock_guard<mutex> lock(m_mLock);
		m_eState = FSS_STOP;
	}

	ThreadDelete();

	return S_OK;
}

STDMETHODIMP CFileSort::Run()
{
	lock_guard<mutex> lock(m_mLock);
	m_iProgress = 0;
	if (m_eState != FSS_CREATED && m_eState != FSS_FINISH || m_eState == FSS_RUNNING)
		return E_CHANGED_STATE;

	if (m_csFileInput.IsEmpty() || m_csFileOutput.IsEmpty())
		return E_FAIL;

	m_eState = FSS_RUNNING;
	ThreadDelete();
	m_pThread = new thread([](LPVOID pThis) {((CFileSort *)pThis)->ThreadProcThunk(); }, this);
	
	return S_OK;
}

HRESULT CFileSort::ReadFileToMap(map<readbuf, unsigned long>& hash, double& fileSize)
{
	ifstream inFile;
	readbuf buf;
	inFile.open(m_csFileInput, ios::in | ios::binary);

	if (!inFile.is_open())
		return S_FALSE;

	inFile.seekg(0, ios::end);
	fileSize = inFile.tellg();
	inFile.seekg(0, ios::beg);

	if (!fileSize)
	{
		inFile.close();
		return S_FALSE;
	}

	while (inFile.read((char*)&buf, sizeof(readbuf)))
	{
		if (hash.find(buf) != hash.end())
			hash[buf]++;
		else
			hash[buf] = 1;

		m_iProgress = ((double)inFile.tellg() / (double)fileSize) * 90;

		if (m_eState == FSS_STOP)
		{
			inFile.close();
			return S_FALSE;
		}
	}
	
	inFile.close();
	return S_OK;
}

HRESULT CFileSort::WriteHashKey(ofstream& outFile, double& posWriteFile, double fileSize, readbuf key, unsigned long count)
{
	for (unsigned long i = 0; i < count; i++)
	{
		outFile.write((char*)&key, sizeof(readbuf));

		posWriteFile += sizeof(readbuf);
		m_iProgress = 90 + ((double)posWriteFile / (double)fileSize) * 10;

		if (m_eState == FSS_STOP)
			return S_FALSE;
	}
	return S_OK;
}

HRESULT CFileSort::WriteFileFromMap(const map<readbuf, unsigned long>& hash, double fileSize)
{
	ofstream outFile;
	outFile.open(m_csFileOutput, ios::out | ios::binary);

	if (!outFile.is_open())
	{
		return S_FALSE;
	}

	double posWriteFile = 0;

	if (m_eSortMethod == FSM_ASC)
	{
		for (auto it = hash.begin(); it != hash.end(); it++)
		{
			if (WriteHashKey(outFile, posWriteFile, fileSize, it->first, it->second) != S_OK)
			{
				outFile.close();
				return S_FALSE;
			}
		}
	}
	else
	{
		for (auto it = hash.rbegin(); it != hash.rend(); it++)
		{
			if (WriteHashKey(outFile, posWriteFile, fileSize, it->first, it->second) != S_OK)
			{
				outFile.close();
				return S_FALSE;
			}

		}
	}
	outFile.close();
	return S_OK;
}

void CFileSort::ThreadProcThunk()
{
	map<readbuf, unsigned long> hash;
	double fileSize;

	if (ReadFileToMap(hash, fileSize) != S_OK)
	{
		FinishTask();
		return;
	}
		
	WriteFileFromMap(hash, fileSize);
	FinishTask();
	return;
}

void  CFileSort::FinishTask()
{
	lock_guard<mutex> lock(m_mLock);
	m_iProgress = 100;
	m_eState = FSS_FINISH;
}

void  CFileSort::ThreadDelete()
{
	if (!m_pThread)
		return;
	m_pThread->join();
	delete m_pThread;
	m_pThread = nullptr;
}

