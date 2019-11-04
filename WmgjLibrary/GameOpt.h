#pragma once

typedef struct
{
	char name[32];
	int level;
	float posX;
	float posY;
	float posZ;
	int hp;
	int hpMax;
	int mp;
	int mpMax;
	int exp;
	int money;
}RoleInfo;

class GameOpt
{
private:
	static GameOpt* gameOptInstance;

	GameOpt();
	~GameOpt();

public:
	static GameOpt* getGameOptInstance();
	void getRole(RoleInfo& info);

};
