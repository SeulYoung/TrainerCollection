#include "pch.h"
#include "ParamMgr.h"

ParamMgr* ParamMgr::paramMgr = NULL;

ParamMgr::~ParamMgr()
{
	if (paramMgr != NULL)
		delete paramMgr;
}

ParamMgr* ParamMgr::getParamMgrInstance()
{
	if (paramMgr == NULL)
		paramMgr = new ParamMgr();
	return paramMgr;
}
