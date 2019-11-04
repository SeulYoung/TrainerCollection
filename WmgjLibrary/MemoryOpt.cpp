#include "pch.h"
#include "MemoryOpt.h"

MemoryOpt::MemoryOpt(HANDLE hProcess, DWORD base, int offset[], int count)
{
	this->hProcess = hProcess;
	this->base = (PVOID)base;
	if (count > 0)
	{
		DWORD addr;
		readOffsetMemory(offset, count - 1, &addr, 4);
		this->base = (PVOID)(addr + offset[count - 1]);
	}
}

bool MemoryOpt::readMemory(PVOID buf, int size)
{
	DWORD temp;
	return ReadProcessMemory(hProcess, base, buf, size, &temp);
}

bool MemoryOpt::readOffsetMemory(int offset[], int size, PVOID buf, int count)
{
	PVOID baseAddr = base;
	DWORD addr;
	DWORD temp;

	for (int i = 0; i < size; i++)
	{
		if (!ReadProcessMemory(hProcess, baseAddr, &addr, 4, &temp))
			return false;
		baseAddr = (PVOID)(addr + offset[i]);
	}
	return ReadProcessMemory(hProcess, baseAddr, buf, count, &temp);
}

bool MemoryOpt::writeMemory(PVOID buf, int size)
{
	DWORD temp;
	return WriteProcessMemory(hProcess, base, buf, size, &temp);
}

bool MemoryOpt::writeOffsetMemory(int offset[], int size, PVOID buf, int count)
{
	PVOID baseAddr = base;
	DWORD addr;
	DWORD temp;

	for (int i = 0; i < size; i++)
	{
		if (!ReadProcessMemory(hProcess, baseAddr, &addr, 4, &temp))
			return false;
		baseAddr = (PVOID)(addr + offset[i]);
	}
	return WriteProcessMemory(hProcess, baseAddr, buf, count, &temp);
}
