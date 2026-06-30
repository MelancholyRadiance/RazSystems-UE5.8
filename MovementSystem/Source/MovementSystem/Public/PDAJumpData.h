#pragma once

#include "PDAMovementBase.h"
#include "PDAJumpData.generated.h"

/**
 * Defines jump behaviour. Applied to CharacterMovementComponent on BeginPlay.
 * Naming convention: PDA_Jump_<ZVelocity>_<MaxJumpCount>  e.g. PDA_Jump_600_1
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDAJumpData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** Upward launch velocity when jumping. UE default is 420. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Jump", meta=(ClampMin=0.0))
	float JumpZVelocity = 600.f;

	/** 1 = single jump, 2 = double jump, etc. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Jump", meta=(ClampMin=1))
	int32 MaxJumpCount = 1;
};
