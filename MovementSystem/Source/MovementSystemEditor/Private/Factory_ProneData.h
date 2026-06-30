#pragma once

#include "Factories/Factory.h"
#include "PDAProneData.h"
#include "Factory_ProneData.generated.h"

UCLASS()
class UFactory_ProneData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_ProneData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAProneData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "ProneDataFactory", "Prone Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Prone_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAProneData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
