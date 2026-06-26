#include "WeaponSystemBaseEditor.h"
#include "AssetToolsModule.h"
#include "WeaponSystemBaseTypeActions.h"
#include "PDAWeaponDataFactory.h"

#define LOCTEXT_NAMESPACE "FWeaponSystemBaseEditorModule"

uint32 UPDAWeaponDataFactory::RazSystemsCategory = EAssetTypeCategories::Misc;

void FWeaponSystemBaseEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type RazCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName("RazSystems"),
		LOCTEXT("RazSystemsCategory", "RazSystems")
	);

	UPDAWeaponDataFactory::RazSystemsCategory = RazCategory;

	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDAWeaponData>(RazCategory));

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
	{
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FWeaponSystemBaseEditorModule::ShutdownModule()
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

IMPLEMENT_MODULE(FWeaponSystemBaseEditorModule, WeaponSystemBaseEditor)
