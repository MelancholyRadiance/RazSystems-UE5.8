#pragma once

#include "FireModeLogicBase.h"
#include "TimerManager.h"
#include "FireModeLogic_Burst.generated.h"

class UPDAFireModeBurst;

UCLASS()
class FIREMODESYSTEM_API UFireModeLogic_Burst : public UFireModeLogicBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner) override;
	virtual void StartFire() override;
	virtual void StopFire() override;

private:
	void FireNextShotInBurst();
	void OnCooldownFinished();

	UPROPERTY()
	TObjectPtr<UPDAFireModeBurst> Data;

	int32 ShotsRemainingInBurst = 0;
	bool bTriggerHeld = false;
	bool bBurstInProgress = false;
	bool bOnCooldown = false;

	FTimerHandle BurstShotTimer;
	FTimerHandle CooldownTimer;
};
