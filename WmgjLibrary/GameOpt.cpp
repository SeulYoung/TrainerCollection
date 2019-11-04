#include "pch.h"
#include "GameOpt.h"
#include "MemoryOpt.h"

GameOpt::GameOpt()
{
	gameOptInstance = NULL;
}

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

	int offset[OFFSET];
	for (int i = 0; i < OFFSET; i++)
		offset[i] = BASE_OFFSET1;
}
