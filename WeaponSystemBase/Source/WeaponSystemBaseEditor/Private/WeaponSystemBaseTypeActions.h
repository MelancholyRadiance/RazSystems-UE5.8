#pragma once

#include "AssetTypeActions_Base.h"
#include "PDAWeaponData.h"

class FAssetTypeActions_PDAWeaponData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAWeaponData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override
	{
		return NSLOCTEXT("WeaponSystemBaseEditor", "WeaponName", "Weapon");
	}
	virtual FColor GetTypeColor() const override { return FColor(60, 90, 130); }
	virtual UClass* GetSupportedClass() const override { return UPDAWeaponData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("WeaponSystemBaseEditor", "WeaponSystemSubMenu", "WeaponSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
