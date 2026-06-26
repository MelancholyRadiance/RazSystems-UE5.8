#pragma once

#include "AssetTypeActions_Base.h"
#include "PDAMagazineData.h"

class FAssetTypeActions_PDAMagazineData : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAMagazineData(EAssetTypeCategories::Type InCategory)
		: Category(InCategory) {}

	virtual FText GetName() const override
	{
		return NSLOCTEXT("MagazineSystemEditor", "MagazineName", "Magazine");
	}
	virtual FColor GetTypeColor() const override { return FColor(80, 130, 60); }
	virtual UClass* GetSupportedClass() const override { return UPDAMagazineData::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("MagazineSystemEditor", "MagazineSystemSubMenu", "MagazineSystem") };
		return SubMenus;
	}

private:
	EAssetTypeCategories::Type Category;
};
