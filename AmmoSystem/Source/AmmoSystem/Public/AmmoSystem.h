#pragma once

#include "Modules/ModuleManager.h"

class FAmmoSystemModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
