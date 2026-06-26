#pragma once

#include "Factories/Factory.h"
#include "PDAFireModeSemiAuto.h"
#include "PDAFireModeSemiAutoFactory.generated.h"

UCLASS()
class UPDAFireModeSemiAutoFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAFireModeSemiAutoFactory() { bCreateNew = true; bEditAfterNew = true; SupportedClass = UPDAFireModeSemiAuto::StaticClass(); }
	virtual FText GetDisplayName() const override { return NSLOCTEXT("FireModeSystemEditor", "SemiAutoFactory", "Semi Automatic"); }
	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }
	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> S = { NSLOCTEXT("FireModeSystemEditor", "FireModeSystemSubMenu", "FireModeSystem") };
		return S;
	}
	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_SemiAuto_"); }
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAFireModeSemiAuto>(InParent, InClass, InName, Flags);
	}
	static uint32 RazSystemsCategory;
};
