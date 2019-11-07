// WmgjLibrary.h: WmgjLibrary DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CWmgjLibraryApp
// 有关此类实现的信息，请参阅 WmgjLibrary.cpp
//

class CWmgjLibraryApp : public CWinApp
{
private:
	HANDLE hThread;

public:
	CWmgjLibraryApp();

	// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
