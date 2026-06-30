#pragma once

#include "Modules/ModuleManager.h"

class FAmmoManagementModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
