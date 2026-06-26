#pragma once

#include "Factories/Factory.h"
#include "PDAFireModeBurst.h"
#include "PDAFireModeBurstFactory.generated.h"

UCLASS()
class UPDAFireModeBurstFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAFireModeBurstFactory() { bCreateNew = true; bEditAfterNew = true; SupportedClass = UPDAFireModeBurst::StaticClass(); }
	virtual FText GetDisplayName() const override { return NSLOCTEXT("FireModeSystemEditor", "BurstFactory", "Burst Fire"); }
	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }
	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> S = { NSLOCTEXT("FireModeSystemEditor", "FireModeSystemSubMenu", "FireModeSystem") };
		return S;
	}
	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_Burst_"); }
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAFireModeBurst>(InParent, InClass, InName, Flags);
	}
	static uint32 RazSystemsCategory;
};
