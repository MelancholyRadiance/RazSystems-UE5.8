#pragma once

#include "Factories/Factory.h"
#include "PDAFireModeFullAuto.h"
#include "PDAFireModeFullAutoFactory.generated.h"

UCLASS()
class UPDAFireModeFullAutoFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPDAFireModeFullAutoFactory() { bCreateNew = true; bEditAfterNew = true; SupportedClass = UPDAFireModeFullAuto::StaticClass(); }
	virtual FText GetDisplayName() const override { return NSLOCTEXT("FireModeSystemEditor", "FullAutoFactory", "Fully Automatic"); }
	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }
	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> S = { NSLOCTEXT("FireModeSystemEditor", "FireModeSystemSubMenu", "FireModeSystem") };
		return S;
	}
	virtual FString GetDefaultNewAssetName() const override { return TEXT("PDA_FullAuto_"); }
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UPDAFireModeFullAuto>(InParent, InClass, InName, Flags);
	}
	static uint32 RazSystemsCategory;
};
