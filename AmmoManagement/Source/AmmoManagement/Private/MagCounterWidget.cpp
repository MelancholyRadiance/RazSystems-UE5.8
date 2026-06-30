#include "MagCounterWidget.h"

void UMagCounterWidget::SetAmmoManager(UAmmoManagerComponent* InManager)
{
	if (AmmoManager)
	{
		AmmoManager->OnMagazinesChanged.RemoveDynamic(this, &UMagCounterWidget::HandleMagazinesChanged);
		AmmoManager->OnMagazineChecked.RemoveDynamic(this, &UMagCounterWidget::HandleMagazineChecked);
	}

	AmmoManager = InManager;

	if (AmmoManager)
	{
		AmmoManager->OnMagazinesChanged.AddDynamic(this, &UMagCounterWidget::HandleMagazinesChanged);
		AmmoManager->OnMagazineChecked.AddDynamic(this, &UMagCounterWidget::HandleMagazineChecked);
		RebuildSlots();
	}
}

FLinearColor UMagCounterWidget::GetFillTint(float FillPercent)
{
	const float Brightness = FMath::Lerp(0.1f, 1.0f, FMath::Clamp(FillPercent, 0.f, 1.f));
	return FLinearColor(Brightness, Brightness, Brightness, 1.f);
}

void UMagCounterWidget::NativeDestruct()
{
	if (AmmoManager)
	{
		AmmoManager->OnMagazinesChanged.RemoveDynamic(this, &UMagCounterWidget::HandleMagazinesChanged);
		AmmoManager->OnMagazineChecked.RemoveDynamic(this, &UMagCounterWidget::HandleMagazineChecked);
	}
	Super::NativeDestruct();
}

void UMagCounterWidget::HandleMagazinesChanged()
{
	RebuildSlots();
}

void UMagCounterWidget::HandleMagazineChecked(int32 EstimatedCount, bool bIsAccurate)
{
	OnMagazineChecked(EstimatedCount, bIsAccurate);
}

void UMagCounterWidget::RebuildSlots()
{
	if (!AmmoManager) return;

	TArray<FMagSlotData> SlotList;

	// Loaded magazine comes first so it's visually distinct in Blueprint
	if (UMagazineInstance* Loaded = AmmoManager->GetLoadedMagazine())
	{
		FMagSlotData& Entry = SlotList.AddDefaulted_GetRef();
		Entry.FillPercent = Loaded->GetFillPercent();
		Entry.TintColor   = GetFillTint(Entry.FillPercent);
		Entry.bIsLoaded   = true;
		Entry.Capacity    = Loaded->GetCapacity();
	}

	for (UMagazineInstance* Mag : AmmoManager->GetMagazineInventory())
	{
		if (!Mag) continue;
		FMagSlotData& Entry = SlotList.AddDefaulted_GetRef();
		Entry.FillPercent = Mag->GetFillPercent();
		Entry.TintColor   = GetFillTint(Entry.FillPercent);
		Entry.bIsLoaded   = false;
		Entry.Capacity    = Mag->GetCapacity();
	}

	OnMagazinesUpdated(SlotList);
}
