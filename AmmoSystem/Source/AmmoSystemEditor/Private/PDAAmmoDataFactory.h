#pragma once

#include "Factories/Factory.h"
#include "PDAAmmoData.h"
#include "PDAAmmoDataFactory.generated.h"

UCLASS()
class UPDAAmmoDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAAmmoDataFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAAmmoData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("AmmoSystemEditor", "AmmoFactory", "Ammo");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("AmmoSystemEditor", "AmmoSystemSubMenu", "AmmoSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Ammo_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAAmmoData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
