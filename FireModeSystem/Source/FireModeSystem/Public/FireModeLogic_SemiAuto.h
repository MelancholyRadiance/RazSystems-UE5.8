#pragma once

#include "FireModeLogicBase.h"
#include "FireModeLogic_SemiAuto.generated.h"

class UPDAFireModeSemiAuto;

UCLASS()
class FIREMODESYSTEM_API UFireModeLogic_SemiAuto : public UFireModeLogicBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner) override;
	virtual void StartFire() override;
	virtual void StopFire() override;

private:
	UPROPERTY()
	TObjectPtr<UPDAFireModeSemiAuto> Data;

	float LastFireTime = -999.f;
};
