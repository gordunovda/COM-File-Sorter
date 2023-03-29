

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 10:14:07 2038
 */
/* Compiler settings for FileSorter.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FileSorter_i_h__
#define __FileSorter_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileSort_FWD_DEFINED__
#define __IFileSort_FWD_DEFINED__
typedef interface IFileSort IFileSort;

#endif 	/* __IFileSort_FWD_DEFINED__ */


#ifndef __FileSort_FWD_DEFINED__
#define __FileSort_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileSort FileSort;
#else
typedef struct FileSort FileSort;
#endif /* __cplusplus */

#endif 	/* __FileSort_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileSort_INTERFACE_DEFINED__
#define __IFileSort_INTERFACE_DEFINED__

/* interface IFileSort */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileSort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2929d7ce-6729-4e6c-ac76-3187bf6bfeab")
    IFileSort : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInputFile( 
            /* [in] */ BSTR __MIDL__IFileSort0000) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOutputFile( 
            /* [in] */ BSTR __MIDL__IFileSort0001) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMethodSort( 
            /* [in] */ int __MIDL__IFileSort0002) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetState( 
            /* [retval][out] */ int *__MIDL__IFileSort0003) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProgress( 
            /* [retval][out] */ int *__MIDL__IFileSort0004) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFileSortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSort * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSort * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFileSort * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFileSort * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFileSort * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFileSort * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetInputFile )( 
            IFileSort * This,
            /* [in] */ BSTR __MIDL__IFileSort0000);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOutputFile )( 
            IFileSort * This,
            /* [in] */ BSTR __MIDL__IFileSort0001);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMethodSort )( 
            IFileSort * This,
            /* [in] */ int __MIDL__IFileSort0002);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            IFileSort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IFileSort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IFileSort * This,
            /* [retval][out] */ int *__MIDL__IFileSort0003);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetProgress )( 
            IFileSort * This,
            /* [retval][out] */ int *__MIDL__IFileSort0004);
        
        END_INTERFACE
    } IFileSortVtbl;

    interface IFileSort
    {
        CONST_VTBL struct IFileSortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSort_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileSort_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileSort_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileSort_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFileSort_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFileSort_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFileSort_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IFileSort_SetInputFile(This,__MIDL__IFileSort0000)	\
    ( (This)->lpVtbl -> SetInputFile(This,__MIDL__IFileSort0000) ) 

#define IFileSort_SetOutputFile(This,__MIDL__IFileSort0001)	\
    ( (This)->lpVtbl -> SetOutputFile(This,__MIDL__IFileSort0001) ) 

#define IFileSort_SetMethodSort(This,__MIDL__IFileSort0002)	\
    ( (This)->lpVtbl -> SetMethodSort(This,__MIDL__IFileSort0002) ) 

#define IFileSort_Run(This)	\
    ( (This)->lpVtbl -> Run(This) ) 

#define IFileSort_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IFileSort_GetState(This,__MIDL__IFileSort0003)	\
    ( (This)->lpVtbl -> GetState(This,__MIDL__IFileSort0003) ) 

#define IFileSort_GetProgress(This,__MIDL__IFileSort0004)	\
    ( (This)->lpVtbl -> GetProgress(This,__MIDL__IFileSort0004) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileSort_INTERFACE_DEFINED__ */



#ifndef __FileSorterLib_LIBRARY_DEFINED__
#define __FileSorterLib_LIBRARY_DEFINED__

/* library FileSorterLib */
/* [version][uuid] */ 

typedef 
enum FILE_SORT_METHOD
    {
        FSM_ASC	= 0,
        FSM_DESC	= ( FSM_ASC + 1 ) 
    } 	FILE_SORT_METHOD;

typedef 
enum FILE_SORT_STATE
    {
        FSS_CREATED	= 0,
        FSS_RUNNING	= ( FSS_CREATED + 1 ) ,
        FSS_STOP	= ( FSS_RUNNING + 1 ) ,
        FSS_FINISH	= ( FSS_STOP + 1 ) 
    } 	FILE_SORT_STATE;


EXTERN_C const IID LIBID_FileSorterLib;

EXTERN_C const CLSID CLSID_FileSort;

#ifdef __cplusplus

class DECLSPEC_UUID("719c4c05-3e00-46f4-b0d5-24f81c5351e4")
FileSort;
#endif
#endif /* __FileSorterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


