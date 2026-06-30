#pragma once

#include "PDAMovementBase.h"
#include "Curves/CurveFloat.h"
#include "PDASprintData.generated.h"

/**
 * Defines sprint behaviour. Multiplier stacks with other active states (crouch, prone, aim).
 * Naming convention: PDA_Sprint_<SpeedMultiplierPercent>  e.g. PDA_Sprint_150
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDASprintData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** Multiplier applied to base walk speed while sprinting. 1.5 = 150% speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprint", meta=(ClampMin=0.0))
	float SpeedMultiplier = 1.5f;

	/**
	 * Optional speed curve. Overrides SpeedMultiplier when set.
	 * X = seconds spent sprinting. Y = speed multiplier.
	 * Use for ramp-up effects or weight-based fatigue over time.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprint")
	TObjectPtr<UCurveFloat> SpeedCurve;
};
