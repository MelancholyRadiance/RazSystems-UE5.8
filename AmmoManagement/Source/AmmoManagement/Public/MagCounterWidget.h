#pragma once

#include "Blueprint/UserWidget.h"
#include "AmmoManagerComponent.h"
#include "MagCounterWidget.generated.h"

/**
 * Per-magazine display data passed to Blueprint for rendering.
 * Each entry maps to one magazine slot in the UI.
 */
USTRUCT(BlueprintType)
struct FMagSlotData
{
	GENERATED_BODY()

	/** 0-1. Drive icon brightness or fill bar from this. */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	float FillPercent = 0.f;

	/**
	 * White at full, dark gray at empty.
	 * Ready to drop into a tint or colour parameter on an image widget.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	FLinearColor TintColor = FLinearColor::White;

	/** True when this is the magazine currently loaded in the weapon. */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	bool bIsLoaded = false;

	/** Max rounds this magazine can hold. */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	int32 Capacity = 0;
};

/**
 * C++ base for the magazine counter HUD widget.
 * Create a Blueprint subclass of this, implement the BlueprintImplementableEvents,
 * then call SetAmmoManager() on BeginPlay to wire it up.
 *
 * Colour math: white (1,1,1) at 100% fill, dark gray (0.1,0.1,0.1) at 0%.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class AMMOMANAGEMENT_API UMagCounterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Wire this widget to an AmmoManagerComponent. Call once on BeginPlay. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	void SetAmmoManager(UAmmoManagerComponent* InManager);

	/** Returns a tint colour for a fill level. White = full, dark gray = empty. */
	UFUNCTION(BlueprintPure, Category="AmmoManagement")
	static FLinearColor GetFillTint(float FillPercent);

protected:
	/**
	 * Called whenever the inventory or loaded magazine changes.
	 * Rebuild your list of mag slot widgets from this array.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="AmmoManagement")
	void OnMagazinesUpdated(const TArray<FMagSlotData>& Slots);

	/**
	 * Called after the player presses the magazine-check input.
	 * bIsAccurate: true when the count is exact (0-20% / 80-100% fill or curve says so).
	 * When false, consider displaying a "~" prefix or a pulsing indicator.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="AmmoManagement")
	void OnMagazineChecked(int32 EstimatedCount, bool bIsAccurate);

	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TObjectPtr<UAmmoManagerComponent> AmmoManager;

	UFUNCTION()
	void HandleMagazinesChanged();

	UFUNCTION()
	void HandleMagazineChecked(int32 EstimatedCount, bool bIsAccurate);

	void RebuildSlots();
};
