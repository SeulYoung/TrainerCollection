#pragma once

class ParamMgr
{
private:
	static ParamMgr* paramMgr;

public:
	AttackSkills attackSkills;
	AttackMonsters attackMonsters;

private:
	~ParamMgr();

public:
	static ParamMgr* getParamMgrInstance();
};

