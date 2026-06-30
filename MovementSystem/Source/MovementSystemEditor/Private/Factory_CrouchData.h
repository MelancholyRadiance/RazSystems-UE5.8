#pragma once

#include "Factories/Factory.h"
#include "PDACrouchData.h"
#include "Factory_CrouchData.generated.h"

UCLASS()
class UFactory_CrouchData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_CrouchData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDACrouchData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "CrouchDataFactory", "Crouch Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Crouch_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDACrouchData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
