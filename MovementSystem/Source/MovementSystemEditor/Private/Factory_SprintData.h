#pragma once

#include "Factories/Factory.h"
#include "PDASprintData.h"
#include "Factory_SprintData.generated.h"

UCLASS()
class UFactory_SprintData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_SprintData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDASprintData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "SprintDataFactory", "Sprint Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Sprint_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDASprintData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
