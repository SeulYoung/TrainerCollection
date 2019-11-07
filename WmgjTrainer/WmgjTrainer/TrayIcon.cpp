#include "pch.h"
#include "resource.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon()
{
	memset(&notifyConData, 0, sizeof(NOTIFYICONDATA));
}

TrayIcon::~TrayIcon()
{
	Shell_NotifyIcon(NIM_DELETE, &notifyConData);
}

void TrayIcon::InitTrayIcon(CWnd* pWnd)
{
	notifyConData.cbSize = sizeof(NOTIFYICONDATA);
	notifyConData.hWnd = pWnd->GetSafeHwnd();

	CString text;
	pWnd->GetWindowText(text);
	StrCpy(notifyConData.szTip, text);

	notifyConData.uCallbackMessage = MSG_ICON_NOTIFY;
	notifyConData.uID = IDR_MAINFRAME;
	notifyConData.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	notifyConData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &notifyConData);
}
