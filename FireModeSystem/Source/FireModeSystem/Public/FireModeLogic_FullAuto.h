#pragma once

#include "FireModeLogicBase.h"
#include "TimerManager.h"
#include "FireModeLogic_FullAuto.generated.h"

class UPDAFireModeFullAuto;

UCLASS()
class FIREMODESYSTEM_API UFireModeLogic_FullAuto : public UFireModeLogicBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner) override;
	virtual void StartFire() override;
	virtual void StopFire() override;

private:
	void FireAndScheduleNext();
	float GetCurrentRPM() const;

	UPROPERTY()
	TObjectPtr<UPDAFireModeFullAuto> Data;

	bool bFiring = false;
	float FireStartTime = 0.f;

	FTimerHandle FireTimer;
};
