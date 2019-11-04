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

	int offset[OFFSET] = { BASE_OFFSET1, BASE_OFFSET2, BASE_OFFSET3, BASE_OFFSET4, BASE_OFFSET5 };



}
