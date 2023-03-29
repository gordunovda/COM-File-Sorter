// dllmain.h : Declaration of module class.

class CFileSorterModule : public ATL::CAtlDllModuleT< CFileSorterModule >
{
public :
	DECLARE_LIBID(LIBID_FileSorterLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILESORTER, "{4295041b-13e5-41bb-b936-ee1b54af4dc1}")
};

extern class CFileSorterModule _AtlModule;
