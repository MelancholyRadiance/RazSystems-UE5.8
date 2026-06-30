#pragma once

#include "AssetTypeActions_Base.h"
#include "RazIMC.h"

class FAssetTypeActions_RazIMC : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_RazIMC(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override { return NSLOCTEXT("RazInputActionsEditor", "RazIMC", "Input Context"); }
	virtual FColor GetTypeColor() const override { return FColor(255, 180, 50); }
	virtual UClass* GetSupportedClass() const override { return URazIMC::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }

	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
