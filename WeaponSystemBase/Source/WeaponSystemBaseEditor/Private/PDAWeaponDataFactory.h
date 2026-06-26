#pragma once

#include "Factories/Factory.h"
#include "PDAWeaponData.h"
#include "PDAWeaponDataFactory.generated.h"

UCLASS()
class UPDAWeaponDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAWeaponDataFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAWeaponData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("WeaponSystemBaseEditor", "WeaponFactory", "Weapon");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("WeaponSystemBaseEditor", "WeaponSystemSubMenu", "WeaponSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Weapon_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAWeaponData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
