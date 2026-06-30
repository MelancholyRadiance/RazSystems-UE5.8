#pragma once

#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

class FRazInputActionsEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static EAssetTypeCategories::Type RazSystemsCategory;

private:
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredTypeActions;
};
