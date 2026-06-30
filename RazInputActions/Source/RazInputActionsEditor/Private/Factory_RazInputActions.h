#pragma once

#include "Factories/Factory.h"
#include "RazInputActionsEditor.h"
#include "RazIMC.h"
#include "InputAction.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "Factory_RazInputActions.generated.h"

UCLASS()
class UFactory_RazInputActions : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_RazInputActions()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = URazIMC::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("RazInputActionsEditor", "RazInputFactory", "Input Context");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("IMC_Player_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		URazIMC* IMC = NewObject<URazIMC>(InParent, InClass, InName, Flags);

		const FString BasePath  = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());
		const FString SubFolder = BasePath / TEXT("Input Actions");
		const FString Prefix    = InName.ToString();

		MakeAndMap(SubFolder, Prefix, TEXT("Fire"),          IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("AltFire"),       IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Reload"),        IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("CheckMagazine"), IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("CycleFireMode"), IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Sprint"),        IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Jump"),          IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Crouch"),        IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Prone"),         IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Aim"),           IMC, Flags);

		return IMC;
	}

	static uint32 RazSystemsCategory;

private:
	template<typename T>
	static T* MakeAsset(const FString& FolderPath, const FString& AssetName, EObjectFlags Flags)
	{
		UPackage* Pkg = CreatePackage(*(FolderPath / AssetName));
		T* Obj = NewObject<T>(Pkg, T::StaticClass(), *AssetName, Flags | RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(Obj);
		Pkg->MarkPackageDirty();
		return Obj;
	}

	static void MakeAndMap(const FString& FolderPath, const FString& Prefix, const FString& ActionSuffix, UInputMappingContext* IMC, EObjectFlags Flags)
	{
		UInputAction* Action = MakeAsset<UInputAction>(FolderPath, Prefix + TEXT("_") + ActionSuffix, Flags);
		if (IMC && Action)
		{
			IMC->MapKey(Action, FKey());
		}
	}
};
