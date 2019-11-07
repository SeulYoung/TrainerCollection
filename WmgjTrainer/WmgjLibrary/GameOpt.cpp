#include "pch.h"
#include "GameOpt.h"
#include "MemoryOpt.h"

GameOpt* GameOpt::gameOptInstance = NULL;

GameOpt::~GameOpt()
{
	if (gameOptInstance != NULL)
		delete gameOptInstance;
}

GameOpt* GameOpt::getGameOptInstance()
{
	if (gameOptInstance == NULL)
		gameOptInstance = new GameOpt();
	return gameOptInstance;
}

void GameOpt::getRole(RoleInfo& info)
{
	ZeroMemory(&info, sizeof(RoleInfo));
	int offset[] = { BASE_OFFSET1, BASE_OFFSET2, BASE_OFFSET3, BASE_OFFSET4, BASE_OFFSET5 };

	MemoryOpt memOpt(GlobalInfo::getGlobalInfoInstance()->getProcessHandle(), BASE_ADDRESS, offset, COUNT);
	int roleOffset[2];

	roleOffset[0] = NAME_OFFSET;
	roleOffset[1] = 0;
	char nameBuf[32] = { 0 };
	memOpt.readOffsetMemory(roleOffset, 2, nameBuf, sizeof(nameBuf));
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)nameBuf, -1, info.name, sizeof(nameBuf), NULL, NULL);

	roleOffset[0] = LEVEL_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.level, sizeof(info.level));

	roleOffset[0] = HP_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.hp, sizeof(info.hp));

	roleOffset[0] = HP_MAX_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.hpMax, sizeof(info.hpMax));

	roleOffset[0] = MP_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.mp, sizeof(info.mp));

	roleOffset[0] = MP_MAX_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.mpMax, sizeof(info.mpMax));

	roleOffset[0] = EXP_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.exp, sizeof(info.exp));

	roleOffset[0] = MONEY_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.money, sizeof(info.money));

	roleOffset[0] = POS_X_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.posX, sizeof(info.posX));

	roleOffset[0] = POS_Y_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.posY, sizeof(info.posY));

	roleOffset[0] = POS_Z_OFFSET;
	memOpt.readOffsetMemory(roleOffset, 1, &info.posZ, sizeof(info.posZ));

}

void GameOpt::getSkills(VEC_SKILL& skills)
{
	skills.clear();
	int offset[] = { 0x1C, 0x34, 0x00, 0x00 };
	MemoryOpt memOpt(GlobalInfo::getGlobalInfoInstance()->getProcessHandle(), BASE_ADDRESS, offset, 4);

	int count;
	offset[2] = SKILL_OFFSET + 0x4;
	memOpt.readOffsetMemory(offset, 3, &count, sizeof(count));
	offset[2] = SKILL_OFFSET;
	for (int i = 0; i < count; i++)
	{
		DWORD addr = 0;
		offset[3] = i * 0x4;
		memOpt.readOffsetMemory(offset, 4, &addr, sizeof(addr));
		if (addr == 0)
			continue;

		SkillInfo skill;
		MemoryOpt memInfo(GlobalInfo::getGlobalInfoInstance()->getProcessHandle(), BASE_ADDRESS, offset, 4);
		int infoOffset[4] = { 0 };

		infoOffset[0] = ID_OFFSET;
		memInfo.readOffsetMemory(infoOffset, 1, &skill.id, sizeof(skill.id));

		infoOffset[0] = NAME_OFFSET1;
		infoOffset[1] = NAME_OFFSET2;
		infoOffset[2] = NAME_OFFSET3;
		infoOffset[3] = 0x0;
		char nameBuf[32] = { 0 };
		memInfo.readOffsetMemory(infoOffset, 4, nameBuf, sizeof(nameBuf));
		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)nameBuf, -1, skill.name, sizeof(nameBuf), NULL, NULL);

		infoOffset[0] = CD_OFFSET;
		memInfo.readOffsetMemory(infoOffset, 1, &skill.cd, sizeof(skill.cd));

		infoOffset[0] = AVAILABLE_OFFSET;
		memInfo.readOffsetMemory(infoOffset, 1, &skill.available, sizeof(skill.available));

		skills.push_back(skill);
	}

}
