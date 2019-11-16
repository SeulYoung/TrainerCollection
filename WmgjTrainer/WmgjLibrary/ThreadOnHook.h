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
	float getDistance(float x1, float y1, float z1, float x2, float y2, float z2);
	static DWORD WINAPI ThreadWork(LPVOID lpParameter);

private:
	void onHookWork();
	void selectMonster();
	void attackMonster();
};
