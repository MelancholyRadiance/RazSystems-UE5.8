#pragma once

#include "Factories/Factory.h"
#include "PDAMovementInertiaData.h"
#include "Factory_MovementInertiaData.generated.h"

UCLASS()
class UFactory_MovementInertiaData : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_MovementInertiaData()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAMovementInertiaData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MovementSystemEditor", "MovementInertiaDataFactory", "Movement Inertia Data");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Inertia_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAMovementInertiaData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
