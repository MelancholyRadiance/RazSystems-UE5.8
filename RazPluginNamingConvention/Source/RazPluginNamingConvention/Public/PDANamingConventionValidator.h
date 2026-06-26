// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "PDANamingConventionValidator.generated.h"

/**
 * Editor-time validator that enforces the PDA_ naming convention for the
 * data assets created by the Ammo / Magazine / Weapon plugins.
 *
 * Conventions enforced (each part is separated by '_'):
 *   Magazine : PDA_Mag_<Calibre>_<Capacity>_<Name>          e.g. PDA_Mag_556x45_030_Stanag
 *   Ammo     : PDA_Ammo_<Calibre>_<Damage>_<Penetration>_<Name>  e.g. PDA_Ammo_556x45_46_28_M855
 *   Weapon   : PDA_Weapon_<Calibre>_<FireRate>_<Name>       e.g. PDA_Weapon_556x45_800_M4A1
 *
 * This runs automatically whenever an asset is saved or when "Validate Assets"
 * is invoked. Malformed names are reported as errors so they cannot slip
 * through; assets that start with PDA_ but use an unknown type produce a
 * warning instead of blocking.
 *
 * To add a new type, extend the rules table in PDANamingConventionValidator.cpp.
 */
UCLASS()
class UPDANamingConventionValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

public:
	UPDANamingConventionValidator();

protected:
	virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;
};
