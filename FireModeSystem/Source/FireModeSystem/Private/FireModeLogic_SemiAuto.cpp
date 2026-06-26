#include "FireModeLogic_SemiAuto.h"
#include "PDAFireModeSemiAuto.h"

void UFireModeLogic_SemiAuto::Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner)
{
	Super::Initialize(InData, InOwner);
	Data = Cast<UPDAFireModeSemiAuto>(InData);
}

void UFireModeLogic_SemiAuto::StartFire()
{
	if (!Data || !GetWorld()) return;

	const float Now = GetWorld()->GetTimeSeconds();
	const float MinInterval = Data->MaxFireRate > 0 ? 60.f / static_cast<float>(Data->MaxFireRate) : 0.f;

	if (Now - LastFireTime >= MinInterval)
	{
		LastFireTime = Now;
		OnFireShot.Broadcast();
	}
}

void UFireModeLogic_SemiAuto::StopFire()
{
	// Nothing to clean up — single shot per press, no active timers.
}
