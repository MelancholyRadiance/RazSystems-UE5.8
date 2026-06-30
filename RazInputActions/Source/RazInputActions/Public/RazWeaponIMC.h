#pragma once

#include "InputMappingContext.h"
#include "RazWeaponIMC.generated.h"

/** Weapon-specific Input Mapping Context. Identical to UInputMappingContext at runtime. */
UCLASS(BlueprintType)
class RAZINPUTACTIONS_API URazWeaponIMC : public UInputMappingContext
{
	GENERATED_BODY()
};
