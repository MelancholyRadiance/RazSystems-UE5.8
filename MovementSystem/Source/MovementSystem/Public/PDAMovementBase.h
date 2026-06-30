#pragma once

#include "Engine/DataAsset.h"
#include "PDAMovementBase.generated.h"

/** Abstract base for all movement data assets. */
UCLASS(Abstract, BlueprintType)
class MOVEMENTSYSTEM_API UPDAMovementBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
};
