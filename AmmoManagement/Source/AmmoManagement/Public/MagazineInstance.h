#pragma once

#include "UObject/Object.h"
#include "PDAMagazineData.h"
#include "Curves/CurveFloat.h"
#include "MagazineInstance.generated.h"

/**
 * A runtime magazine. Holds a reference to a data asset (type, calibre, capacity)
 * and tracks the current round count separately so partial mags are preserved.
 * Create via UMagazineInstance::Create — never instantiate directly.
 */
UCLASS(BlueprintType)
class AMMOMANAGEMENT_API UMagazineInstance : public UObject
{
	GENERATED_BODY()

public:
	/** The data asset that defines this magazine's type. */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	TObjectPtr<UPDAMagazineData> MagazineType;

	/** Current rounds remaining. */
	UPROPERTY(BlueprintReadOnly, Category="Magazine")
	int32 CurrentRounds = 0;

	/** Creates a magazine instance from a data asset. */
	UFUNCTION(BlueprintCallable, Category="AmmoManagement", meta=(DefaultToSelf="Outer"))
	static UMagazineInstance* Create(UObject* Outer, UPDAMagazineData* Data, bool bFull = true);

	/** 0-1 where 1 is fully loaded. */
	UFUNCTION(BlueprintPure, Category="Magazine")
	float GetFillPercent() const;

	UFUNCTION(BlueprintPure, Category="Magazine")
	int32 GetCapacity() const;

	/** Removes one round. Returns false when the mag is empty. */
	UFUNCTION(BlueprintCallable, Category="Magazine")
	bool ConsumeRound();

	/**
	 * Returns an estimated round count as perceived by the player after a magazine check.
	 *
	 * Default behaviour (no curve):
	 *   0-20% fill  -> exact count (few rounds, easy to feel)
	 *   80-100% fill -> exact count (nearly full, easy to feel)
	 *   20-80% fill -> rounded down to the nearest 5 (hard to gauge)
	 *
	 * Optional curve: X = fill (0-1), Y = accuracy (0-1).
	 *   Accuracy 1 = exact count. Accuracy 0 = nearest 5.
	 *   Use this to tune how forgiving the check is at each fill level.
	 *
	 * Also returns whether the result is exact via bOutIsAccurate.
	 */
	UFUNCTION(BlueprintCallable, Category="Magazine")
	int32 GetCheckedEstimate(UCurveFloat* AccuracyCurve, bool& bOutIsAccurate) const;
};
