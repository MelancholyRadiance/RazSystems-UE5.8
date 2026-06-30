#pragma once

#include "Factories/Factory.h"
#include "RazInputActionsEditor.h"
#include "RazMovementIMC.h"
#include "RazWeaponIMC.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Misc/PackageName.h"
#include "Factory_MovementInputActions.generated.h"

/**
 * Creates movement input actions and adds them to an existing IMC in the same folder.
 * If no IMC exists there, a new one is created.
 * Create this in the same folder as a Weapon Input Context to share one IMC.
 */
UCLASS()
class UFactory_MovementInputActions : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_MovementInputActions()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = URazMovementIMC::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("RazInputActionsEditor", "MovementInputFactory", "Movement Input Context");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("IMC_Movement_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		const FString BasePath  = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());
		const FString SubFolder = BasePath / TEXT("Movement Actions");
		const FString Prefix    = InName.ToString();

		// Reuse a URazWeaponIMC in this folder so weapon + movement share one context.
		// If none found, create a new URazMovementIMC for movement-only setups.
		UInputMappingContext* IMC = FindWeaponIMCInFolder(BasePath);
		if (!IMC)
		{
			IMC = NewObject<URazMovementIMC>(InParent, InClass, InName, Flags);
		}

		MakeAndMap(SubFolder, Prefix, TEXT("Sprint"), IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Jump"),   IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Crouch"), IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Prone"),  IMC, Flags);
		MakeAndMap(SubFolder, Prefix, TEXT("Aim"),    IMC, Flags);

		return IMC;
	}

	static uint32 RazSystemsCategory;

private:
	static UInputMappingContext* FindWeaponIMCInFolder(const FString& FolderPath)
	{
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
		FARFilter Filter;
		Filter.PackagePaths.Add(FName(*FolderPath));
		Filter.ClassPaths.Add(URazWeaponIMC::StaticClass()->GetClassPathName());
		Filter.bRecursivePaths = false;
		TArray<FAssetData> Found;
		Registry.GetAssets(Filter, Found);
		return Found.IsEmpty() ? nullptr : Cast<UInputMappingContext>(Found[0].GetAsset());
	}

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
