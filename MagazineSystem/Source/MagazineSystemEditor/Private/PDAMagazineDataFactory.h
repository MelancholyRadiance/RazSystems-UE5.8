#pragma once

#include "Factories/Factory.h"
#include "PDAMagazineData.h"
#include "PDAMagazineDataFactory.generated.h"

UCLASS()
class UPDAMagazineDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAMagazineDataFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDAMagazineData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("MagazineSystemEditor", "MagazineFactory", "Magazine");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MagazineSystemEditor", "MagazineSystemSubMenu", "MagazineSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Mag_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAMagazineData>(InParent, InClass, InName, Flags);
	}

	static uint32 RazSystemsCategory;
};
