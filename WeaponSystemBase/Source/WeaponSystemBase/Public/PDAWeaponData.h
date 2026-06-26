#pragma once

#include "Engine/DataAsset.h"
#include "PDACalibreData.h"
#include "PDAMagazineData.h"
#include "PDAWeaponData.generated.h"

/**
 * Defines a weapon. Calibre is the key used to validate that an inserted magazine
 * matches this weapon - at runtime compare Calibre pointers for identity.
 * WeaponMesh is a soft reference so it is only streamed in when the weapon is equipped.
 * Naming convention: PDA_Weapon_<Calibre>_<FallbackFireRate>_<Name>
 * e.g. PDA_Weapon_556x45_800_M4A1
 */
UCLASS(BlueprintType)
class WEAPONSYSTEMBASE_API UPDAWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UPDACalibreData> Calibre;

	/** Default magazine to spawn the weapon with. Must share the same Calibre. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UPDAMagazineData> DefaultMagazine;

	/**
	 * Used when FireModeSystem is not present or FireModes is empty.
	 * If you are using FireModeManagerComponent, set fire rate on each fire mode asset instead.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	int32 FallbackFireRate = 0;

	/**
	 * Fire mode data assets available on this weapon (PDAFireModeSemiAuto, PDAFireModeBurst, PDAFireModeFullAuto).
	 * Requires the FireModeSystem plugin. Leave empty if using FallbackFireRate only.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowedClasses="/Script/FireModeSystem.PDAFireModeBase"))
	TArray<TObjectPtr<UPrimaryDataAsset>> FireModes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	FText DisplayName;
};
