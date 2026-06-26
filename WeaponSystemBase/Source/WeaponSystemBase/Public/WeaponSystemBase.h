#pragma once

#include "Modules/ModuleManager.h"

class FWeaponSystemBaseModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
