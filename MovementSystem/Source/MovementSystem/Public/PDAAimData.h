#pragma once

#include "PDAMovementBase.h"
#include "PDAAimData.generated.h"

/**
 * Defines aim-down-sights movement penalty.
 * Naming convention: PDA_Aim_<SpeedMultiplierPercent>  e.g. PDA_Aim_70
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDAAimData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** Multiplier applied to base walk speed while aiming. 0.7 = 70% speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Aim", meta=(ClampMin=0.0))
	float SpeedMultiplier = 0.7f;
};
