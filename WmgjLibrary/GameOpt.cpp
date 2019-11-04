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
	int roleOffset[] = { NAME_OFFSET, 0 };
	char buf[32] = { 0 };
	memOpt.readOffsetMemory(roleOffset, 2, buf, 32);
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)buf, -1, info.name, 32, NULL, NULL);


}
