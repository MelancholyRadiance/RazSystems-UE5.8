#include "MovementSystemEditor.h"
#include "AssetToolsModule.h"

#include "AssetTypeActions_JumpData.h"
#include "AssetTypeActions_SprintData.h"
#include "AssetTypeActions_CrouchData.h"
#include "AssetTypeActions_ProneData.h"
#include "AssetTypeActions_AimData.h"
#include "AssetTypeActions_MovementInertiaData.h"

#include "Factory_JumpData.h"
#include "Factory_SprintData.h"
#include "Factory_CrouchData.h"
#include "Factory_ProneData.h"
#include "Factory_AimData.h"
#include "Factory_MovementInertiaData.h"

#define LOCTEXT_NAMESPACE "FMovementSystemEditorModule"

uint32 UFactory_JumpData::RazSystemsCategory            = EAssetTypeCategories::Misc;
uint32 UFactory_SprintData::RazSystemsCategory          = EAssetTypeCategories::Misc;
uint32 UFactory_CrouchData::RazSystemsCategory          = EAssetTypeCategories::Misc;
uint32 UFactory_ProneData::RazSystemsCategory           = EAssetTypeCategories::Misc;
uint32 UFactory_AimData::RazSystemsCategory             = EAssetTypeCategories::Misc;
uint32 UFactory_MovementInertiaData::RazSystemsCategory = EAssetTypeCategories::Misc;

void FMovementSystemEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type RazCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName("RazSystems"),
		LOCTEXT("RazSystemsCategory", "RazSystems")
	);

	UFactory_JumpData::RazSystemsCategory            = RazCategory;
	UFactory_SprintData::RazSystemsCategory          = RazCategory;
	UFactory_CrouchData::RazSystemsCategory          = RazCategory;
	UFactory_ProneData::RazSystemsCategory           = RazCategory;
	UFactory_AimData::RazSystemsCategory             = RazCategory;
	UFactory_MovementInertiaData::RazSystemsCategory = RazCategory;

	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_JumpData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_SprintData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_CrouchData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_ProneData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_AimData>(RazCategory));
	RegisteredTypeActions.Add(MakeShared<FAssetTypeActions_MovementInertiaData>(RazCategory));

	for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredTypeActions)
	{
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FMovementSystemEditorModule::ShutdownModule()
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

IMPLEMENT_MODULE(FMovementSystemEditorModule, MovementSystemEditor)
