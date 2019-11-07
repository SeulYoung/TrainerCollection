#include "pch.h"
#include "GlobalInfo.h"

GlobalInfo* GlobalInfo::globalInfo = NULL;

GlobalInfo::GlobalInfo()
{
	hWndDllMain = NULL;
}

GlobalInfo::~GlobalInfo()
{
	if (globalInfo != NULL)
		delete globalInfo;
}

GlobalInfo* GlobalInfo::getGlobalInfoInstance()
{
	if (globalInfo == NULL)
		globalInfo = new GlobalInfo();
	return globalInfo;
}
