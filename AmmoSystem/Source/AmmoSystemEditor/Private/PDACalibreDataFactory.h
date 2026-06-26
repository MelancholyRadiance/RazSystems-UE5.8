#pragma once

#include "Factories/Factory.h"
#include "PDACalibreData.h"
#include "PDACalibreDataFactory.generated.h"

UCLASS()
class UPDACalibreDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDACalibreDataFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UPDACalibreData::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("AmmoSystemEditor", "CalibreFactory", "Calibre");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("AmmoSystemEditor", "AmmoSystemSubMenu", "AmmoSystem") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Calibre_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDACalibreData>(InParent, InClass, InName, Flags);
	}

	// Set by the editor module after registering the custom category.
	static uint32 RazSystemsCategory;
};
