#include "FireModeSystemEditor.h"
#include "AssetToolsModule.h"
#include "FireModeSystemTypeActions.h"
#include "PDAFireModeSemiAutoFactory.h"
#include "PDAFireModeBurstFactory.h"
#include "PDAFireModeFullAutoFactory.h"

#define LOCTEXT_NAMESPACE "FFireModeSystemEditorModule"

uint32 UPDAFireModeSemiAutoFactory::RazSystemsCategory = EAssetTypeCategories::Misc;
uint32 UPDAFireModeBurstFactory::RazSystemsCategory    = EAssetTypeCategories::Misc;
uint32 UPDAFireModeFullAutoFactory::RazSystemsCategory = EAssetTypeCategories::Misc;

void FFireModeSystemEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type RazCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName("RazSystems"),
		LOCTEXT("RazSystemsCategory", "RazSystems")
	);

	UPDAFireModeSemiAutoFactory::RazSystemsCategory = RazCategory;
	UPDAFireModeBurstFactory::RazSystemsCategory    = RazCategory;
	UPDAFireModeFullAutoFactory::RazSystemsCategory = RazCategory;

	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDAFireModeSemiAuto>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDAFireModeBurst>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_PDAFireModeFullAuto>(RazCategory));

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
	{
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FFireModeSystemEditorModule::ShutdownModule()
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

IMPLEMENT_MODULE(FFireModeSystemEditorModule, FireModeSystemEditor)
