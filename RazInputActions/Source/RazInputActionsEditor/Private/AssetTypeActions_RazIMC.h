#pragma once

#include "AssetTypeActions_Base.h"
#include "RazWeaponIMC.h"
#include "RazMovementIMC.h"

class FAssetTypeActions_WeaponIMC : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_WeaponIMC(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override { return NSLOCTEXT("RazInputActionsEditor", "WeaponIMC", "Weapon Input Context"); }
	virtual FColor GetTypeColor() const override { return FColor(255, 180, 50); }
	virtual UClass* GetSupportedClass() const override { return URazWeaponIMC::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }

	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};

class FAssetTypeActions_MovementIMC : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_MovementIMC(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override { return NSLOCTEXT("RazInputActionsEditor", "MovementIMC", "Movement Input Context"); }
	virtual FColor GetTypeColor() const override { return FColor(100, 220, 130); }
	virtual UClass* GetSupportedClass() const override { return URazMovementIMC::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }

	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
