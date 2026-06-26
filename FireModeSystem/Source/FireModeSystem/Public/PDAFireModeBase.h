#pragma once

#include "Engine/DataAsset.h"
#include "PDAFireModeBase.generated.h"

class UFireModeLogicBase;

/**
 * Abstract base for all fire mode data assets.
 * Subclass this (or use the provided SemiAuto / Burst / FullAuto subclasses) to define
 * a fire mode configuration. Add instances to UFireModeManagerComponent on your weapon actor.
 */
UCLASS(Abstract, BlueprintType)
class FIREMODESYSTEM_API UPDAFireModeBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireMode")
	FText DisplayName;

	/** Returns the logic class that drives this fire mode at runtime. */
	virtual TSubclassOf<UFireModeLogicBase> GetLogicClass() const { return nullptr; }
};
