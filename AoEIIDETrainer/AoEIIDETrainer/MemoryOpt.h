#pragma once
class MemoryOpt
{
private:
	HANDLE hProc;
	HANDLE hThread;
	PVOID base;
	PVOID threadAddr;
	PVOID paraAddr;

public:
	MemoryOpt();
	~MemoryOpt();

	DWORD getProcId(CString gameProcName);
	// 不要在构造函数或析构函数throw异常，会导致析构函数不能被正确调用
	void initHandle();
	void initPara(QWORD base, int offset[], int count);
	void readMemory(PVOID buf, int size);
	void readOffsetMemory(int offset[], int count, PVOID buf, int size);
	void writeMemory(PVOID buf, int size);
	void writeOffsetMemory(int offset[], int count, PVOID buf, int size);
	void runRemoteThread(PVOID fun, PVOID buf, int size);
};
