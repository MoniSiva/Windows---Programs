#include <jni.h>
#include <jni_md.h>
#include<windows.h>
#define _WIN32_DCOM
#include <iostream>
#include "SampleApp.h"
#include <comdef.h>
#include <comutil.h>
#include <Wbemidl.h>
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif
#pragma comment(lib, "wbemuuid.lib")

using namespace std;
JNIEXPORT void  JNICALL Java_SampleApp_logMessage(JNIEnv *env,jobject obj,jstring javaString){


	
	HRESULT hres;
    hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x" 
            << hex << hres << endl;
        return;                  
    }

   
    hres =  CoInitializeSecurity(NULL,-1, NULL,NULL,RPC_C_AUTHN_LEVEL_DEFAULT,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,EOAC_NONE,NULL);

                      
    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x" 
            << hex << hres << endl;
        CoUninitialize();
        return; 
    }
    // Obtain the initial locator to WMI -------------------------

    IWbemLocator *pLoc = NULL;

    hres = CoCreateInstance(CLSID_WbemLocator, 0,CLSCTX_INPROC_SERVER,IID_IWbemLocator, (LPVOID *) &pLoc);
 
    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object."
            << " Err code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return;                
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method

    IWbemServices *pSvc = NULL;
 
    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer( _bstr_t(L"ROOT\\CIMV2"),NULL,NULL,0,NULL,0,0,&pSvc );
    
    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x" 
             << hex << hres << endl;
        pLoc->Release();     
        CoUninitialize();
        return;                
    }

    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(pSvc,RPC_C_AUTHN_WINNT,RPC_C_AUTHZ_NONE,NULL,RPC_C_AUTHN_LEVEL_CALL,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,EOAC_NONE);

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x" 
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();     
        CoUninitialize();
        return;              
    }

   
    // Use the IWbemServices pointer to make requests of WMI ----

   const char *nativeString = env->GetStringUTFChars(javaString, 0);
   
   
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(bstr_t("WQL"),bstr_t("SELECT * FROM Win32_NTLogEvent WHERE Logfile = 'Application'"),WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,NULL,&pEnumerator);
    
    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."<< " Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;               // Program has failed.
    }

    // Get the data from the query in step 6 -------------------
 
    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
   
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,&pclsObj, &uReturn);

        if(0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        jclass cls = env->GetObjectClass(obj);
		
		char* str=NULL;
		int len;
		jstring jstr;
		jmethodID mid;
		
       hr = pclsObj->Get(L"ComputerName", 0, &vtProp, 0, 0);
		len = wcslen(vtProp.bstrVal);
		str = new char[len+1];
		wcstombs(str, vtProp.bstrVal, len+1);	
		jstr = env->NewStringUTF(str);
		if(cls !=0)
			{  
				mid = env->GetMethodID(cls,"printComputerName", "(Ljava/lang/String;)V");				
				if(mid !=0)
				{  
				   env->CallVoidMethod(obj, mid, jstr);
				}
				
		}
		
        hr = pclsObj->Get(L"SourceName", 0, &vtProp, 0, 0);
		len = wcslen(vtProp.bstrVal);
		str = new char[len+1];
		wcstombs(str, vtProp.bstrVal, len+1);	
		jstr = env->NewStringUTF(str);
		if(cls !=0)
			{  
				mid = env->GetMethodID(cls,"printSourceName", "(Ljava/lang/String;)V");				
				if(mid !=0)
				{  
				   env->CallVoidMethod(obj, mid, jstr);
				}
				
		}
		
		hr = pclsObj->Get(L"EventCode", 0, &vtProp, 0, 0);
		if(cls !=0)
			{  
				mid = env->GetMethodID(cls,"printEventCode", "(I)V");				
				if(mid !=0)
				{  
				   env->CallVoidMethod(obj, mid, vtProp.iVal);
				}
				
		}
		
			 
        hr = pclsObj->Get(L"EventType", 0, &vtProp, 0, 0);
		if(cls !=0)
			{  
				mid = env->GetMethodID(cls,"printEventId", "(I)V");				
				if(mid !=0)
				{  
				   env->CallVoidMethod(obj, mid, vtProp.iVal);
				}
				
		}
			
		
		
        VariantClear(&vtProp);

        pclsObj->Release();
    }

  
    env->ReleaseStringUTFChars(javaString, nativeString);
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return;   
 
}