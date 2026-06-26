#pragma once

#include "AssetTypeActions_Base.h"
#include "PDAFireModeSemiAuto.h"
#include "PDAFireModeBurst.h"
#include "PDAFireModeFullAuto.h"

static const TArray<FText>& GetFireModeSubMenus()
{
	static const TArray<FText> SubMenus = { NSLOCTEXT("FireModeSystemEditor", "FireModeSystemSubMenu", "FireModeSystem") };
	return SubMenus;
}

// ─── Semi Auto ───────────────────────────────────────────────────────────────

class FAssetTypeActions_PDAFireModeSemiAuto : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAFireModeSemiAuto(EAssetTypeCategories::Type InCategory) : Category(InCategory) {}
	virtual FText GetName() const override { return NSLOCTEXT("FireModeSystemEditor", "SemiAutoName", "Semi Automatic"); }
	virtual FColor GetTypeColor() const override { return FColor(100, 180, 100); }
	virtual UClass* GetSupportedClass() const override { return UPDAFireModeSemiAuto::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override { return GetFireModeSubMenus(); }
private:
	EAssetTypeCategories::Type Category;
};

// ─── Burst ───────────────────────────────────────────────────────────────────

class FAssetTypeActions_PDAFireModeBurst : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAFireModeBurst(EAssetTypeCategories::Type InCategory) : Category(InCategory) {}
	virtual FText GetName() const override { return NSLOCTEXT("FireModeSystemEditor", "BurstName", "Burst Fire"); }
	virtual FColor GetTypeColor() const override { return FColor(200, 150, 50); }
	virtual UClass* GetSupportedClass() const override { return UPDAFireModeBurst::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override { return GetFireModeSubMenus(); }
private:
	EAssetTypeCategories::Type Category;
};

// ─── Full Auto ───────────────────────────────────────────────────────────────

class FAssetTypeActions_PDAFireModeFullAuto : public FAssetTypeActions_Base
{
public:
	explicit FAssetTypeActions_PDAFireModeFullAuto(EAssetTypeCategories::Type InCategory) : Category(InCategory) {}
	virtual FText GetName() const override { return NSLOCTEXT("FireModeSystemEditor", "FullAutoName", "Fully Automatic"); }
	virtual FColor GetTypeColor() const override { return FColor(200, 70, 70); }
	virtual UClass* GetSupportedClass() const override { return UPDAFireModeFullAuto::StaticClass(); }
	virtual uint32 GetCategories() override { return Category; }
	virtual const TArray<FText>& GetSubMenus() const override { return GetFireModeSubMenus(); }
private:
	EAssetTypeCategories::Type Category;
};
