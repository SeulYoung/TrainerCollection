#pragma once

enum BaseOffset
{
	BASE_ADDRESS = 0x0F037C4,
	COUNT = 5,
	BASE_OFFSET1 = 0x1C,
	BASE_OFFSET2 = 0x1C,
	BASE_OFFSET3 = 0x1C,
	BASE_OFFSET4 = 0x8,
	BASE_OFFSET5 = 0x34
};

enum RoleOffset
{
	NAME_OFFSET = 0x700,
	LEVEL_OFFSET = 0x4C4,
	POS_X_OFFSET = 0x3C,
	POS_Y_OFFSET = 0x44,
	POS_Z_OFFSET = 0x40,
	HP_OFFSET = 0x4CC,
	HP_MAX_OFFSET = 0x520,
	MP_OFFSET = 0x4D0,
	MP_MAX_OFFSET = 0x524,
	EXP_OFFSET = 0x530,
	MONEY_OFFSET = 0x5A8,
	SKILL_OFFSET = 0x1578
};

enum SkillOffset
{
	ID_OFFSET = 0x8,
	NAME_OFFSET1 = 0x4,
	NAME_OFFSET2 = 0x4,
	NAME_OFFSET3 = 0xC,
	CD_OFFSET = 0x14,
	AVAILABLE_OFFSET = 0x10		// 0代表技能可用
};

enum MonsterType
{
	ORDINARY = 6
};

enum callAddress
{
	SELECT_MONSTER = 0x86F2F0,
	USE_SKILL = 0x4BCB10
};

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

typedef struct
{
	int id;
	char name[32];
	int hp;
	int type;
}MonsterInfo;

typedef std::vector<SkillInfo> VEC_SKILL;
typedef std::vector<MonsterInfo> VEC_MONSTER;
