#include "pch.h"
#include "ThreadOnHook.h"
#include "GameOpt.h"
#include "ParamMgr.h"

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

float ThreadOnHook::getDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return pow(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2), 0.5);
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
	RoleInfo role;
	GameOpt::getGameOptInstance()->getRole(role);
	VEC_MONSTER monsters;
	GameOpt::getGameOptInstance()->getMonsters(monsters);

	int monsterId = monsters[0].id;
	float dist = getDistance(role.posX, role.posY, role.posZ, monsters[0].posX, monsters[0].posY, monsters[0].posZ);
	// 选择距离最近的普通怪物
	for (size_t i = 1; i < monsters.size(); i++)
		if (monsters[i].type == ORDINARY)
		{
			bool isAttackList = ParamMgr::getParamMgrInstance()->attackMonsters.isAttackList;
			bool isInList = ParamMgr::getParamMgrInstance()->attackMonsters.isInList(CString(monsters[i].name));
			if ((isAttackList && !isInList) || (!isAttackList && isInList))
				continue;

			float temp = getDistance(role.posX, role.posY, role.posZ, monsters[i].posX, monsters[i].posY, monsters[i].posZ);
			if (temp < dist)
			{
				monsterId = monsters[i].id;
				dist = temp;
			}
		}
	GameOpt::getGameOptInstance()->selectObjById(monsterId);
}

void ThreadOnHook::attackMonster()
{
	AttackSkills& attackSkills = ParamMgr::getParamMgrInstance()->attackSkills;
	bool isFirstSkillUsed;
	for (size_t i = 0; i < attackSkills.skills.size(); i++)
	{
		RoleInfo role;
		GameOpt::getGameOptInstance()->getRole(role);
		if (role.selectObjId == 0)
			break;

		GameOpt::getGameOptInstance()->useSkillByName(attackSkills.skills[i]);
	}
}
