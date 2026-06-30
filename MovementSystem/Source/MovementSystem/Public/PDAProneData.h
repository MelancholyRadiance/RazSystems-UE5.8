#pragma once

#include "PDAMovementBase.h"
#include "Curves/CurveFloat.h"
#include "PDAProneData.generated.h"

/**
 * Defines prone behaviour. Capsule resize is done manually — the replicated bProne bool
 * drives the resize on both server and client, but it is not as robustly authoritative
 * as CMC's native crouch. Acceptable for non-competitive multiplayer.
 * Naming convention: PDA_Prone_<SpeedMultiplierPercent>  e.g. PDA_Prone_15
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDAProneData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** Multiplier applied to base walk speed while prone. 0.15 = 15% speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Prone", meta=(ClampMin=0.0))
	float SpeedMultiplier = 0.15f;

	/** Capsule half-height while prone. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Prone", meta=(ClampMin=1.0))
	float PronedHalfHeight = 22.f;

	/** Time in seconds to transition into or out of prone. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Prone", meta=(ClampMin=0.0))
	float TransitionTime = 0.5f;

	/**
	 * Optional speed curve. Overrides SpeedMultiplier when set.
	 * X = seconds spent prone. Y = speed multiplier.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Prone")
	TObjectPtr<UCurveFloat> SpeedCurve;
};
