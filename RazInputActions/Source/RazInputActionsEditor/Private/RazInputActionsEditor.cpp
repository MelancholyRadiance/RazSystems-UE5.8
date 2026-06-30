#include "RazInputActionsEditor.h"
#include "AssetToolsModule.h"

#include "AssetTypeActions_RazIMC.h"
#include "Factory_RazInputActions.h"

#define LOCTEXT_NAMESPACE "FRazInputActionsEditorModule"

uint32 UFactory_RazInputActions::RazSystemsCategory = EAssetTypeCategories::Misc;

EAssetTypeCategories::Type FRazInputActionsEditorModule::RazSystemsCategory = EAssetTypeCategories::Misc;

void FRazInputActionsEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type RazCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName("RazSystems"),
		LOCTEXT("RazSystemsCategory", "RazSystems")
	);

	RazSystemsCategory = RazCategory;
	UFactory_RazInputActions::RazSystemsCategory = RazCategory;

	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_RazIMC>(RazCategory));

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
	{
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FRazInputActionsEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
	RegisteredTypeActions.Empty();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRazInputActionsEditorModule, RazInputActionsEditor)
