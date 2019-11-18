#pragma once

constexpr auto GAME_PROC_NAME = _T("age2_x1.exe");

enum UnitId
{
	HEROC = 0x239,			// 圣殿骑士
	UTKNI = 0x22A,			// 条顿武士
	UMOSU = 0x231,			// 精锐蒙古骑射手
	ULGBW = 0x212,			// 精锐长弓兵
	PARAM_ADDR = 0x0	// 存放参数的地址
};

constexpr auto BASE = 0x7FF69AC0F668;

enum BaseOffset
{
	OFFSET1 = 0xB8,
	OFFSET2 = 0xBBF0,
	OFFSET3 = 0xD0,
	OFFSET4 = 0x8,
	OFFSET5 = 0x168,
	OFFSET6 = 0x118,
	OFFSET7 = 0x18
};

enum ResourceOffset
{
	RESO_OFFSET1 = 0x68,
	FOOD_OFFSET = 0x0,
	WOOD_OFFSET = 0x4,
	STONE_OFFSET = 0x8,
	GOOD_OFFSET = 0xC,
	POPULATION_OFFSET = 0x2C
};
