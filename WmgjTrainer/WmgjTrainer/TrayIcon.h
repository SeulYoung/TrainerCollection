#pragma once

#define MSG_ICON_NOTIFY WM_USER + 2888

class TrayIcon
{
private:
	NOTIFYICONDATA notifyConData;

public:
	TrayIcon();
	~TrayIcon();
	void InitTrayIcon(CWnd* pWnd);
};
