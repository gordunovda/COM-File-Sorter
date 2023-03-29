#pragma once

class CXMLLogger
{
public:
	static CXMLLogger *Instance();
	static void Release();

	CXMLLogger(CString filename);
	void Notice(CString message, ...);
	void Warning(CString message, ...);
	void Error(CString message, ...);
	~CXMLLogger();
private:
	static CXMLLogger* m_pInstance;

	void Write(CString node, CString message);
	
	CString m_csFilename;
	IXMLDOMDocumentPtr m_spXMLDoc;
	IXMLDOMNode* m_spRootNode;
	IXMLDOMElement* m_spRootElement;
};

