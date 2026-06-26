#pragma once

#include "PDAFireModeBase.h"
#include "Curves/CurveFloat.h"
#include "PDAFireModeFullAuto.generated.h"

/**
 * Fully automatic fire mode. Fires continuously while the trigger is held.
 * Naming convention: PDA_FullAuto_<FireRate>_<Name>  e.g. PDA_FullAuto_800_Standard
 */
UCLASS(BlueprintType)
class FIREMODESYSTEM_API UPDAFireModeFullAuto : public UPDAFireModeBase
{
	GENERATED_BODY()

public:
	/** Steady-state fire rate in rounds per minute. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode", meta=(ClampMin=1))
	int32 FireRate = 800;

	/**
	 * Optional RPM curve for wind-up / spin-up effects.
	 * X = seconds the trigger has been held continuously.
	 * Y = multiplier on FireRate (0-1). Leave unset for instant full rate.
	 * Example: Y=0 at X=0, Y=1 at X=2 gives a 2-second wind-up to full RPM.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode")
	TObjectPtr<UCurveFloat> FireRateCurve;

	virtual TSubclassOf<UFireModeLogicBase> GetLogicClass() const override;
};
