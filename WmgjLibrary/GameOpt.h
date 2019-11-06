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

typedef struct
{
	int id;
	char name[32];
	int cd;
	int available;		// 0表示技能可用
}SkillInfo;

typedef std::vector<SkillInfo> VEC_SKILL;

class GameOpt
{
private:
	static GameOpt* gameOptInstance;

	~GameOpt();

public:
	static GameOpt* getGameOptInstance();
	void getRole(RoleInfo& info);
	void getSkills(VEC_SKILL& skills);
};
