#pragma once

#include "PDAFireModeBase.h"
#include "PDAFireModeSemiAuto.generated.h"

/**
 * Semi-automatic fire mode. One shot per trigger press.
 * MaxFireRate caps how fast the trigger can be pulled (prevents auto-clickers).
 * Naming convention: PDA_SemiAuto_<MaxFireRate>_<Name>  e.g. PDA_SemiAuto_600_Standard
 */
UCLASS(BlueprintType)
class FIREMODESYSTEM_API UPDAFireModeSemiAuto : public UPDAFireModeBase
{
	GENERATED_BODY()

public:
	/** Maximum shots per minute. Caps how fast the trigger can be pulled. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode", meta=(ClampMin=1))
	int32 MaxFireRate = 600;

	virtual TSubclassOf<UFireModeLogicBase> GetLogicClass() const override;
};
