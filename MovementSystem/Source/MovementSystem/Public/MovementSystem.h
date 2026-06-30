#pragma once

#include "Modules/ModuleManager.h"

class FMovementSystemModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
