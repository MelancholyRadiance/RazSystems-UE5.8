#pragma once

#include "Engine/DataAsset.h"
#include "PDACalibreData.h"
#include "PDAAmmoData.generated.h"

/**
 * Defines a single ammo type. Calibre must match the magazine and weapon that use it.
 * Naming convention: PDA_Ammo_<Calibre>_<Damage>_<Penetration>_<Name>
 * e.g. PDA_Ammo_556x45_46_28_M855
 */
UCLASS(BlueprintType)
class AMMOSYSTEM_API UPDAAmmoData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	TObjectPtr<UPDACalibreData> Calibre;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 Damage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 Penetration = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	FText DisplayName;
};
