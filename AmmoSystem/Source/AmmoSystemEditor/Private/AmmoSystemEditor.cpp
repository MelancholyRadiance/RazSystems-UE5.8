#include "AmmoSystemEditor.h"
#include "AssetToolsModule.h"
#include "AmmoSystemTypeActions.h"
#include "PDACalibreDataFactory.h"
#include "PDAAmmoDataFactory.h"

#define LOCTEXT_NAMESPACE "FAmmoSystemEditorModule"

uint32 UPDACalibreDataFactory::RazSystemsCategory = EAssetTypeCategories::Misc;
uint32 UPDAAmmoDataFactory::RazSystemsCategory    = EAssetTypeCategories::Misc;

void FAmmoSystemEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type RazCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName("RazSystems"),
		LOCTEXT("RazSystemsCategory", "RazSystems")
	);

	UPDACalibreDataFactory::RazSystemsCategory = RazCategory;
	UPDAAmmoDataFactory::RazSystemsCategory    = RazCategory;

	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDACalibreData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDAAmmoData>(RazCategory));

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
	{
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FAmmoSystemEditorModule::ShutdownModule()
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

IMPLEMENT_MODULE(FAmmoSystemEditorModule, AmmoSystemEditor)
