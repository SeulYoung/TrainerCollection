#include "pch.h"
#include "MemoryOpt.h"
#include <TlHelp32.h>

MemoryOpt::MemoryOpt()
{
	HANDLE hProc = NULL;
	HANDLE hThread = NULL;
	PVOID base = NULL;
	PVOID threadAddr = NULL;
	PVOID paraAddr = NULL;
}

MemoryOpt::~MemoryOpt()
{
	if (paraAddr != NULL)
		VirtualFreeEx(hProc, paraAddr, 0, MEM_RELEASE);
	if (threadAddr != NULL)
		VirtualFreeEx(hProc, threadAddr, 0, MEM_RELEASE);

	if (hThread != NULL)
		CloseHandle(hThread);
	if (hProc != NULL)
		CloseHandle(hProc);
}

DWORD MemoryOpt::getProcId(CString gameProcName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	DWORD procId = 0;
	bool ret = Process32First(hSnapShot, &pe32);
	while (ret)
	{
		CString procName = pe32.szExeFile;
		//procName.MakeLower();
		if (gameProcName == procName)
		{
			procId = pe32.th32ProcessID;
			break;
		}
		ret = Process32Next(hSnapShot, &pe32);
	}
	CloseHandle(hSnapShot);

	return procId;
}

void MemoryOpt::initHandle()
{
	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, getProcId(GAME_PROC_NAME));;
	if (hProc == NULL)
		throw std::exception("打开游戏进程失败");
}

void MemoryOpt::initPara(DWORD baseAddr, int offset[], int count)
{
	initHandle();

	base = (PVOID)baseAddr;
	if (count > 0)
	{
		DWORD addr;
		readOffsetMemory(offset, count - 1, &addr, 4);
		base = (PVOID)(addr + offset[count - 1]);
	}
}

void MemoryOpt::readMemory(PVOID buf, int size)
{
	DWORD temp;
	ReadProcessMemory(hProc, base, buf, size, &temp);
}

void MemoryOpt::readOffsetMemory(int offset[], int count, PVOID buf, int size)
{
	PVOID baseAddr = base;
	DWORD addr;
	DWORD temp;

	for (int i = 0; i < count; i++)
	{
		if (!ReadProcessMemory(hProc, baseAddr, &addr, 4, &temp))
			throw std::exception("读取游戏内存数据失败");
		baseAddr = (PVOID)(addr + offset[i]);
	}
	if (!ReadProcessMemory(hProc, baseAddr, buf, size, &temp))
		throw std::exception("读取游戏内存数据失败");
}

void MemoryOpt::writeMemory(PVOID buf, int size)
{
	DWORD temp;
	WriteProcessMemory(hProc, base, buf, size, &temp);
}

void MemoryOpt::writeOffsetMemory(int offset[], int count, PVOID buf, int size)
{
	PVOID baseAddr = base;
	DWORD addr;
	DWORD temp;

	for (int i = 0; i < count; i++)
	{
		if (!ReadProcessMemory(hProc, baseAddr, &addr, 4, &temp))
			throw std::exception("读取游戏内存数据失败");
		baseAddr = (PVOID)(addr + offset[i]);
	}
	if (!WriteProcessMemory(hProc, baseAddr, buf, size, &temp))
		throw std::exception("写入游戏内存数据失败");
}

void MemoryOpt::runRemoteThread(PVOID func, PVOID buf, int size)
{
	threadAddr = VirtualAllocEx(hProc, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (threadAddr == NULL)
		throw std::exception("分配线程运行内存失败");

	DWORD writeSize;
	if (!WriteProcessMemory(hProc, threadAddr, func, 4096, &writeSize))
		throw std::exception("线程函数写入游戏内存失败");

	paraAddr = VirtualAllocEx(hProc, NULL, size, MEM_COMMIT, PAGE_READWRITE);
	if (paraAddr == NULL)
		throw std::exception("分配参数内存失败");

	if (!WriteProcessMemory(hProc, paraAddr, buf, size, &writeSize))
		throw std::exception("参数写入游戏内存失败");

	hThread = CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)threadAddr, buf, NULL, NULL);
	if (hThread == NULL)
		throw std::exception("创建辅助线程失败");

	DWORD waitResult = WaitForSingleObject(hThread, 10000);
	if (waitResult == WAIT_TIMEOUT)
		throw std::exception("线程执行等待超时");

	if (paraAddr != NULL)
		VirtualFreeEx(hProc, paraAddr, 0, MEM_RELEASE);
	if (threadAddr != NULL)
		VirtualFreeEx(hProc, threadAddr, 0, MEM_RELEASE);

	if (hThread != NULL)
		CloseHandle(hThread);
	if (hProc != NULL)
		CloseHandle(hProc);
}
