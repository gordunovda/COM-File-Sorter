#include "pch.h"
#include "XMLLogger.h"
#include <iomanip>
#include <cstdarg>
#include <ctime>


CXMLLogger *CXMLLogger::m_pInstance = nullptr;

CXMLLogger* CXMLLogger::Instance()
{
	if (!m_pInstance)
		m_pInstance = new CXMLLogger(_T("log.xml"));
	return m_pInstance;
}

void CXMLLogger::Release()
{
	if (m_pInstance)
		delete m_pInstance;
}

CString GetApplicationPath() 
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos).c_str();
}

CXMLLogger::CXMLLogger(CString filename)
{
	m_csFilename = GetApplicationPath() + _T("\\") + filename;
	HRESULT hr = m_spXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if (FAILED(hr))
	{
		MessageBox(0, _T("Logger MSXML2::DOMDocument30 not crated"), _T("CXMLLogger"), 0);
		return;
	}
	IXMLDOMProcessingInstruction* root;
	m_spXMLDoc->createProcessingInstruction(_T("xml"), _T(" version='1.0' encoding='UTF-8'"), &root);
	m_spXMLDoc->appendChild(root, &m_spRootNode);
	m_spXMLDoc->createElement(_T("logs"), &m_spRootElement);
	
}
void CXMLLogger::Notice(CString message, ...)
{
	std::va_list vaArgs;
	va_start(vaArgs, message);
	CString outMassage;
	outMassage.FormatV(message, vaArgs);
	Write(_T("Notice"), outMassage);
	va_end(vaArgs);	
}

void CXMLLogger::Warning(CString message, ...)
{
	std::va_list vaArgs;
	va_start(vaArgs, message);
	CString outMassage;
	outMassage.FormatV(message, vaArgs);
	Write(_T("Warning"), outMassage);
	va_end(vaArgs);
	
}

void CXMLLogger::Write(CString node, CString message)
{
	CString csTime;
	CTime time;

	time = CTime::GetCurrentTime();
	csTime = time.Format("%F %T");

	CComVariant varNodeType = NODE_ELEMENT;
	CComVariant value = message;
	CComVariant timeValue = csTime;
	IXMLDOMElement* pXMLNewChild;

	BSTR bsNode = node.AllocSysString();
	BSTR msg = message.AllocSysString();

	m_spXMLDoc->createElement(_T("notice"), &pXMLNewChild);

	pXMLNewChild->setAttribute(_T("time"), timeValue);
	pXMLNewChild->put_text(msg);

	SysFreeString(msg);
	SysFreeString(bsNode);

	m_spRootElement->appendChild(pXMLNewChild, &m_spRootNode);
}
void CXMLLogger::Error(CString message, ...)
{
	std::va_list vaArgs;
	va_start(vaArgs, message);
	CString outMassage;
	outMassage.FormatV(message, vaArgs);
	Write(_T("Error"), outMassage);
	va_end(vaArgs);
}

CXMLLogger::~CXMLLogger()
{
	m_spXMLDoc->appendChild(m_spRootElement, &m_spRootNode);
	CComVariant varFile = m_csFilename;
	m_spXMLDoc->save(varFile);
}
