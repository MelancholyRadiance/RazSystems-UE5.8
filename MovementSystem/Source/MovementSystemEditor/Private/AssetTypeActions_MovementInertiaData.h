#pragma once

#include "AssetTypeActions_Base.h"
#include "PDAMovementInertiaData.h"

class FAssetTypeActions_MovementInertiaData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_MovementInertiaData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override { return NSLOCTEXT("MovementSystemEditor", "MovementInertiaData", "Movement Inertia Data"); }
	virtual FColor GetTypeColor() const override { return FColor(100, 200, 255); }
	virtual UClass* GetSupportedClass() const override { return UPDAMovementInertiaData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }

	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MovementSystemEditor", "MovementSystemSubMenu", "MovementSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
