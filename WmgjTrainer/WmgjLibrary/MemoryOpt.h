#pragma once
class MemoryOpt
{
private:
	HANDLE hProcess;
	PVOID base;

public:
	MemoryOpt(HANDLE hProcess,DWORD base,int offset[],int count);
	bool readMemory(PVOID buf,int size);
	bool readOffsetMemory(int offset[], int count, PVOID buf, int size);
	bool writeMemory(PVOID buf,int size);
	bool writeOffsetMemory(int offset[], int count, PVOID buf, int size);

};

