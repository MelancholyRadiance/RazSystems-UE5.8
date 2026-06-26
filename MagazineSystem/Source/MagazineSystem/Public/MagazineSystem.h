#pragma once

#include "Modules/ModuleManager.h"

class FMagazineSystemModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
