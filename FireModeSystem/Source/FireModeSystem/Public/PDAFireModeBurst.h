#pragma once

#include "PDAFireModeBase.h"
#include "Curves/CurveFloat.h"
#include "PDAFireModeBurst.generated.h"

/**
 * Burst fire mode. Fires a fixed number of shots per trigger press.
 * Naming convention: PDA_Burst_<BurstCount>_<BurstFireRate>_<Name>  e.g. PDA_Burst_3_900_Standard
 */
UCLASS(BlueprintType)
class FIREMODESYSTEM_API UPDAFireModeBurst : public UPDAFireModeBase
{
	GENERATED_BODY()

public:
	/** Number of shots fired per burst. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode", meta=(ClampMin=2))
	int32 BurstCount = 3;

	/** RPM between shots within a single burst. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode", meta=(ClampMin=1))
	int32 BurstFireRate = 900;

	/** Seconds before another burst can begin. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode", meta=(ClampMin=0.0))
	float CooldownBetweenBursts = 0.4f;

	/**
	 * If true, holding the trigger keeps firing bursts after each cooldown.
	 * If false, the trigger must be released and pressed again for every burst.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode")
	bool bContinuousBurst = false;

	/**
	 * Optional RPM curve applied within the burst.
	 * X = normalised burst progress (0 = first shot, 1 = last shot).
	 * Y = multiplier on BurstFireRate (0-1). Leave unset for constant rate.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode")
	TObjectPtr<UCurveFloat> FireRateCurve;

	virtual TSubclassOf<UFireModeLogicBase> GetLogicClass() const override;
};
