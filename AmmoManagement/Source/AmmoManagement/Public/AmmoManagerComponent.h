#pragma once

#include "Components/ActorComponent.h"
#include "MagazineInstance.h"
#include "Curves/CurveFloat.h"
#include "AmmoManagerComponent.generated.h"

class UPDACalibreData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagazinesChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMagazineChecked, int32, EstimatedCount, bool, bIsAccurate);

/**
 * Manages a character's magazine inventory and the currently loaded magazine.
 * Add to a Character alongside FireModeManagerComponent.
 *
 * Workflow:
 *   - Populate inventory with CreateAndAddMagazine() on BeginPlay or on pickup.
 *   - Call Reload() to swap in the next compatible mag.
 *   - Call ConsumeRound() from your fire logic (or bind directly to OnFireShot).
 *   - Call CheckMagazine() from input to broadcast an estimated count to the widget.
 */
UCLASS(ClassGroup=(RazSystems), meta=(BlueprintSpawnableComponent))
class AMMOMANAGEMENT_API UAmmoManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * Optional curve that refines magazine-check accuracy.
	 * X = fill percent (0-1). Y = accuracy (0 = nearest 5 rounds, 1 = exact count).
	 * When unset: exact below 20% and above 80% fill, nearest-5 in between.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AmmoManagement")
	TObjectPtr<UCurveFloat> CheckAccuracyCurve;

	/** Fired whenever the inventory or loaded magazine changes. Bind the widget to this. */
	UPROPERTY(BlueprintAssignable, Category="AmmoManagement")
	FOnMagazinesChanged OnMagazinesChanged;

	/** Fired after CheckMagazine(). EstimatedCount is the perceived round count. */
	UPROPERTY(BlueprintAssignable, Category="AmmoManagement")
	FOnMagazineChecked OnMagazineChecked;

	// --- Inventory -----------------------------------------------------------

	/** Creates a magazine from a data asset and adds it to inventory. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	UMagazineInstance* CreateAndAddMagazine(UPDAMagazineData* MagData, bool bFull = true);

	/** Adds an existing instance to inventory (e.g. a pickup, a dropped partial mag). */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	void AddMagazine(UMagazineInstance* Mag);

	UFUNCTION(BlueprintPure, Category="AmmoManagement")
	const TArray<UMagazineInstance*>& GetMagazineInventory() const;

	// --- Loading / Reloading -------------------------------------------------

	/** Manually load a specific magazine instance. Ejects the current one into inventory. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	void LoadMagazine(UMagazineInstance* Mag);

	/** Ejects the loaded magazine back into inventory. Returns it (may be null). */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	UMagazineInstance* EjectMagazine();

	/**
	 * Ejects the current magazine, then loads the next inventory mag whose calibre
	 * matches RequiredCalibre. Pass null to accept any calibre.
	 * Returns false if no compatible mag is available.
	 */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	bool Reload(UPDACalibreData* RequiredCalibre = nullptr);

	// --- Firing --------------------------------------------------------------

	/** Call this on each shot. Returns false when the loaded magazine is empty. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	bool ConsumeRound();

	// --- Inspection ----------------------------------------------------------

	/** Checks the loaded magazine and broadcasts OnMagazineChecked with an estimated count. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement")
	void CheckMagazine();

	UFUNCTION(BlueprintPure, Category="AmmoManagement")
	UMagazineInstance* GetLoadedMagazine() const { return LoadedMagazine; }

private:
	UPROPERTY()
	TArray<TObjectPtr<UMagazineInstance>> MagazineInventory;

	UPROPERTY()
	TObjectPtr<UMagazineInstance> LoadedMagazine;

	void BroadcastChanged();
};
