#pragma once

#include "AssetTypeActions_Base.h"
#include "PDACalibreData.h"
#include "PDAAmmoData.h"

// ─── Calibre ─────────────────────────────────────────────────────────────────

class FAssetTypeActions_PDACalibreData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDACalibreData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override
	{
		return NSLOCTEXT("AmmoSystemEditor", "CalibreName", "Calibre");
	}
	virtual FColor GetTypeColor() const override { return FColor(200, 160, 20); }
	virtual UClass* GetSupportedClass() const override { return UPDACalibreData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("AmmoSystemEditor", "AmmoSystemSubMenu", "AmmoSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};

// ─── Ammo ─────────────────────────────────────────────────────────────────────

class FAssetTypeActions_PDAAmmoData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAAmmoData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override
	{
		return NSLOCTEXT("AmmoSystemEditor", "AmmoName", "Ammo");
	}
	virtual FColor GetTypeColor() const override { return FColor(180, 80, 30); }
	virtual UClass* GetSupportedClass() const override { return UPDAAmmoData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("AmmoSystemEditor", "AmmoSystemSubMenu", "AmmoSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
