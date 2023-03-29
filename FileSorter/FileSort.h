// FileSort.h : Declaration of the CFileSort

#pragma once
#include "resource.h"       // main symbols



#include "FileSorter_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CFileSort

class ATL_NO_VTABLE CFileSort :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileSort, &CLSID_FileSort>,
	public IDispatchImpl<IFileSort, &IID_IFileSort, &LIBID_FileSorterLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFileSort();
	~CFileSort();
	

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CFileSort)
	COM_INTERFACE_ENTRY(IFileSort)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(SetInputFile)(BSTR);
	STDMETHOD(SetOutputFile)(BSTR);
	STDMETHOD(SetMethodSort)(int);
	STDMETHOD(Run)();
	STDMETHOD(Stop)();
	STDMETHOD(GetState)(int*);
	STDMETHOD(GetProgress)(int*);


private:
	HRESULT WriteHashKey(ofstream& outFile, double& posWriteFile, double fileSize, readbuf key, unsigned long count);
	HRESULT ReadFileToMap(map<readbuf, unsigned long>& hash, double &fileSize);
	HRESULT WriteFileFromMap(const map<readbuf, unsigned long>& hash, double fileSize);
	void ThreadProcThunk();
	void ThreadDelete();
	void FinishTask();

	CString m_csFileInput;
	CString m_csFileOutput;
	int m_eSortMethod;
	int m_eState;
	int m_iProgress;
	thread *m_pThread;
	mutex m_mLock;
};

OBJECT_ENTRY_AUTO(__uuidof(FileSort), CFileSort)
