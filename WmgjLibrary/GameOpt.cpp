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

	MemoryOpt memOpt(GlobalInfo::getGlobalInfoInstance()->getProcessHandle(), BASE_ADDRESS, offset, OFFSET);
	int roleOffset[2];

	roleOffset[0] = NAME_OFFSET;
	roleOffset[1] = 0;
	char buf[32] = { 0 };
	memOpt.readOffsetMemory(roleOffset, 2, buf, sizeof(buf));
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)buf, -1, info.name, sizeof(buf), NULL, NULL);

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
