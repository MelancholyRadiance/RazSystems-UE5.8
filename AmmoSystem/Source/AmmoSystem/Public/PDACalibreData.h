#pragma once

#include "Engine/DataAsset.h"
#include "PDACalibreData.generated.h"

/**
 * Defines a physical cartridge type. Calibre identity is the asset pointer itself —
 * two items are compatible if and only if they reference the exact same PDA_Calibre_ asset.
 * Naming convention: PDA_Calibre_<NNxNN>  e.g. PDA_Calibre_556x45
 */
UCLASS(BlueprintType)
class AMMOSYSTEM_API UPDACalibreData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Calibre")
	FText DisplayName;
};
