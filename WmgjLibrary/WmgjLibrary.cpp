// WmgjLibrary.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "WmgjLibrary.h"
#include "DllMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CWmgjLibraryApp

BEGIN_MESSAGE_MAP(CWmgjLibraryApp, CWinApp)
END_MESSAGE_MAP()


// CWmgjLibraryApp 构造

CWmgjLibraryApp::CWmgjLibraryApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	hThread = NULL;
}


// 唯一的 CWmgjLibraryApp 对象

CWmgjLibraryApp theApp;

const GUID CDECL _tlid = { 0x28892970,0xc545,0x4adc,{0x8d,0x93,0x0d,0x19,0x66,0x8b,0xd6,0xf1} };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

DWORD WINAPI ShowMainDlg(LPVOID pParam)
{
	MessageBox(NULL, _T("辅助模块加载成功"), NULL, 0);
	DllMainDlg dlg;
	dlg.DoModal();
	return 0;
}

// CWmgjLibraryApp 初始化

BOOL CWmgjLibraryApp::InitInstance()
{
	CWinApp::InitInstance();

	hThread = ::CreateThread(NULL, 0, ShowMainDlg, NULL, 0, NULL);

	// 将所有 OLE 服务器(工厂)注册为运行。  这将使
	//  OLE 库得以从其他应用程序创建对象。
	COleObjectFactory::RegisterAll();

	return TRUE;
}

int CWmgjLibraryApp::ExitInstance()
{
	SendMessage(GlobalInfo::getGlobalInfoInstance()->getHWndDllMain(), WM_CLOSE, 0, 0);
	TerminateThread(hThread, 0);
	WaitForSingleObject(hThread, INFINITE);
	MessageBox(NULL, _T("辅助模块卸载成功"), NULL, 0);

	return 0;
}

// DllGetClassObject - 返回类工厂

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - 允许 COM 卸载 DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}
