#pragma once

#include "Engine/DataAsset.h"
#include "PDACalibreData.h"
#include "PDAMagazineData.h"
#include "PDAWeaponData.generated.h"

/**
 * Defines a weapon. Calibre is the key used to validate that an inserted magazine
 * matches this weapon — at runtime compare Calibre pointers for identity.
 * WeaponMesh is a soft reference so it is only streamed in when the weapon is equipped.
 * Naming convention: PDA_Weapon_<Calibre>_<FireRate>_<Name>
 * e.g. PDA_Weapon_556x45_800_M4A1
 */
UCLASS(BlueprintType)
class WEAPONSYSTEMBASE_API UPDAWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UPDACalibreData> Calibre;

	/** Default magazine to spawn the weapon with. Must share the same Calibre. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UPDAMagazineData> DefaultMagazine;

	/** Rounds per minute. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 FireRate = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FText DisplayName;
};
