#pragma once

class GlobalInfo
{
private:
	static GlobalInfo* globalInfo;
	HWND hWndDllMain;

private:
	GlobalInfo();
	~GlobalInfo();

public:
	static GlobalInfo* getGlobalInfoInstance();
	HANDLE getProcessHandle() { return GetCurrentProcess(); }
	HWND getHWndDllMain() const { return hWndDllMain; }
	void setHWndDllMain(const HWND& hWnd) { hWndDllMain = hWnd; }
};
