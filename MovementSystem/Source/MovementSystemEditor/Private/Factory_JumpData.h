#pragma once

#include "Factories/Factory.h"
#include "PDAJumpData.h"
#include "Factory_JumpData.generated.h"

UCLASS()
class UFactory_JumpData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_JumpData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAJumpData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "JumpDataFactory", "Jump Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Jump_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAJumpData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
