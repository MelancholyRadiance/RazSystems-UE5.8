#pragma once

#include "InputMappingContext.h"
#include "RazMovementIMC.generated.h"

/** Movement-specific Input Mapping Context. Identical to UInputMappingContext at runtime. */
UCLASS(BlueprintType)
class RAZINPUTACTIONS_API URazMovementIMC : public UInputMappingContext
{
	GENERATED_BODY()
};
