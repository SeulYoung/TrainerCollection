#include "pch.h"
#include "ThreadOnHook.h"
#include "GameOpt.h"

ThreadOnHook::ThreadOnHook()
{
	hThread = NULL;
	isStop = true;
}

void ThreadOnHook::start()
{
	DWORD threadId;
	if (hThread == NULL)
		hThread = CreateThread(NULL, 0, ThreadWork, this, 0, &threadId);
	isStop = false;
}

void ThreadOnHook::stop()
{
	if (hThread != NULL)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
	isStop = true;
}

DWORD WINAPI ThreadOnHook::ThreadWork(LPVOID lpParameter)
{
	ThreadOnHook* onHook = (ThreadOnHook*)lpParameter;
	if (onHook != NULL)
		onHook->onHookWork();
	return 0;
}

void ThreadOnHook::onHookWork()
{
	while (!isStop)
	{
		selectMonster();
		attackMonster();
		Sleep(100);
	}
}

void ThreadOnHook::selectMonster()
{
	VEC_MONSTER monsters;
	GameOpt::getGameOptInstance()->getMonsters(monsters);
	for (size_t i = 0; i < monsters.size(); i++)
		if (monsters[i].type == ORDINARY)
		{
			GameOpt::getGameOptInstance()->selectObjById(monsters[i].id);
			break;
		}
}

void ThreadOnHook::attackMonster()
{
	while (true)
	{
		GameOpt::getGameOptInstance()->userSkillByName(_T("»÷ÔÎÊ¸"));
	}
}
