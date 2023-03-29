// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "FileSorter_i.h"
#include "dllmain.h"

CFileSorterModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	DisableThreadLibraryCalls(hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved);
}
