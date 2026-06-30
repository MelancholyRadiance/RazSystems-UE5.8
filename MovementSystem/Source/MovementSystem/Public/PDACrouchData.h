#pragma once

#include "PDAMovementBase.h"
#include "Curves/CurveFloat.h"
#include "PDACrouchData.generated.h"

/**
 * Defines crouch behaviour. Uses CMC's native Crouch/UnCrouch so capsule resize
 * is correctly replicated in multiplayer.
 * Naming convention: PDA_Crouch_<SpeedMultiplierPercent>  e.g. PDA_Crouch_50
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDACrouchData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** Multiplier applied to base walk speed while crouched. 0.5 = 50% speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Crouch", meta=(ClampMin=0.0))
	float SpeedMultiplier = 0.5f;

	/** Capsule half-height while crouched. UE default is 44. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Crouch", meta=(ClampMin=1.0))
	float CrouchedHalfHeight = 44.f;

	/**
	 * Optional speed curve. Overrides SpeedMultiplier when set.
	 * X = seconds spent crouching. Y = speed multiplier.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Crouch")
	TObjectPtr<UCurveFloat> SpeedCurve;
};
