#pragma once

#include "Factories/Factory.h"
#include "PDAAimData.h"
#include "Factory_AimData.generated.h"

UCLASS()
class UFactory_AimData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_AimData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAAimData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "AimDataFactory", "Aim Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Aim_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAAimData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
