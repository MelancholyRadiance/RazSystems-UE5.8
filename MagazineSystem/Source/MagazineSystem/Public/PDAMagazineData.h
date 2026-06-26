#pragma once

#include "Engine/DataAsset.h"
#include "PDACalibreData.h"
#include "PDAMagazineData.generated.h"

/**
 * Defines a magazine type. Calibre must match the weapon it is loaded into.
 * Naming convention: PDA_Mag_<Calibre>_<Capacity>_<Name>
 * e.g. PDA_Mag_556x45_030_Stanag
 */
UCLASS(BlueprintType)
class MAGAZINESYSTEM_API UPDAMagazineData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magazine")
	TObjectPtr<UPDACalibreData> Calibre;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magazine")
	int32 Capacity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magazine")
	FText DisplayName;
};
