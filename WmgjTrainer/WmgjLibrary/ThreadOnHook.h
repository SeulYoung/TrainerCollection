#pragma once

class ThreadOnHook
{
private:
	HANDLE hThread;
	bool isStop;

public:
	ThreadOnHook();

	void start();
	void stop();
	static DWORD WINAPI ThreadWork(LPVOID lpParameter);

private:
	void onHookWork();
	void selectMonster();
	void attackMonster();
};
