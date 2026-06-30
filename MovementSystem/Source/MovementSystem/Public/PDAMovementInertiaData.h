#pragma once

#include "PDAMovementBase.h"
#include "PDAMovementInertiaData.generated.h"

/**
 * Defines the feel of movement — how quickly the character accelerates, decelerates,
 * and how much control they have in the air.
 * Naming convention: PDA_Inertia_<Name>  e.g. PDA_Inertia_Standard
 */
UCLASS(BlueprintType)
class MOVEMENTSYSTEM_API UPDAMovementInertiaData : public UPDAMovementBase
{
	GENERATED_BODY()

public:
	/** How quickly the character reaches max speed on the ground. UE default is 2048. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inertia", meta=(ClampMin=0.0))
	float MaxAcceleration = 2048.f;

	/** How quickly the character slows to a stop on the ground. UE default is 2048. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inertia", meta=(ClampMin=0.0))
	float BrakingDeceleration = 2048.f;

	/** Surface friction. Higher = snappier stops and turns. UE default is 8. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inertia", meta=(ClampMin=0.0))
	float GroundFriction = 8.f;

	/** 0-1. How much directional control the character has while airborne. UE default is 0.35. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inertia", meta=(ClampMin=0.0, ClampMax=1.0))
	float AirControl = 0.35f;

	/** Deceleration applied while falling. 0 = full momentum carry. UE default is 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inertia", meta=(ClampMin=0.0))
	float BrakingDecelerationFalling = 0.f;
};
