// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include <dui/DuiSystem.h> 
#include <dui/DuiDefaultLogger.h>
 
#include "MainDlg.h"

#include <exdisp.h>
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	//HRESULT hRes = CoInitialize(NULL);
	OleInitialize(NULL);
	//DUIASSERT(SUCCEEDED(hRes));
 
// 	CLSID iecls=CLSID_InternetExplorer;
// 	IUnknown *pwb;
// 	HRESULT hres = CoCreateInstance(iecls, NULL,
// 		CLSCTX_LOCAL_SERVER, IID_IUnknown, (void **)&pwb);


	TCHAR szCurrentDir[MAX_PATH+1]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, MAX_PATH );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DuiSystem duiSystem(hInstance);
	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\duiengine.log"));
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent(_T("demo started"));

	#ifdef __DUIFILE_RC 
	//从文件夹加载皮肤,指定皮肤位置
	_tcscat( szCurrentDir, _T("\\..\\skin") );
	DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
	if(!pResFiles->Init(szCurrentDir))
	{
		DUIASSERT(0);
		return 1;
	}
	duiSystem.SetResProvider(pResFiles);
#else 
	//从资源加载皮肤
	duiSystem.SetResProvider(new DuiResProviderPE(hInstance));
#endif 
	BOOL bOK=duiSystem.Init(_T("IDR_DUI_INIT")); //初始化DUI系统,原来的系统初始化方式依然可以使用。
	duiSystem.SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent(_T("demo end"));

	delete duiSystem.GetResProvider();

//	CoUninitialize();
	OleUninitialize();
	return nRet;
}
