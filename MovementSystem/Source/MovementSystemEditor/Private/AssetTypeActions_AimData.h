#pragma once

#include "AssetTypeActions_Base.h"
#include "PDAAimData.h"

class FAssetTypeActions_AimData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_AimData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override { return NSLOCTEXT("MovementSystemEditor", "AimData", "Aim Data"); }
	virtual FColor GetTypeColor() const override { return FColor(100, 200, 255); }
	virtual UClass* GetSupportedClass() const override { return UPDAAimData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }

	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
