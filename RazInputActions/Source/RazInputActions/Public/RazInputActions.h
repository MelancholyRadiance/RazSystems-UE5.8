#pragma once

#include "Modules/ModuleManager.h"

class FRazInputActionsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
