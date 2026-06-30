#pragma once

#include "Factories/Factory.h"
#include "RazInputActionsEditor.h"
#include "RazWeaponIMC.h"
#include "InputAction.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "Factory_WeaponInputActions.generated.h"

/**
 * Creates an Input Mapping Context pre-populated with weapon input actions.
 * Individual UInputAction assets land in a "Weapon Actions" subfolder.
 * Assign keys to them inside the generated IMC.
 */
UCLASS()
class UFactory_WeaponInputActions : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_WeaponInputActions()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = URazWeaponIMC::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("RazInputActionsEditor", "WeaponInputFactory", "Weapon Input Context");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("IMC_Weapon_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		URazWeaponIMC* IMC = NewObject<URazWeaponIMC>(InParent, InClass, InName, Flags);

		const FString BasePath  = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());
		const FString SubFolder = BasePath / TEXT("Weapon Actions");
		const FString Prefix    = InName.ToString();

		MakeAndMap(SubFolder, Prefix, TEXT("Fire"),          IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("AltFire"),       IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Reload"),        IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("CheckMagazine"), IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("CycleFireMode"), IMC, Flags);

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
