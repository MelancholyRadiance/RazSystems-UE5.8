#pragma once

#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

class FMovementSystemEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static EAssetTypeCategories::Type RazSystemsCategory;

private:
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredTypeActions;
};
