#pragma once

class GameOpt
{
private:
	static GameOpt* gameOptInstance;

private:
	~GameOpt();

public:
	static GameOpt* getGameOptInstance();
	void getRole(RoleInfo& info);
	void getSkills(VEC_SKILL& skills);
	void getMonsters(VEC_MONSTER& monsters);
	void selectObjById(int objId);
	void useSkillById(int skillId);
	void userSkillByName(CString name);
};
