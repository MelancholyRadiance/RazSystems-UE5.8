#include "FireModeLogic_Burst.h"
#include "PDAFireModeBurst.h"

void UFireModeLogic_Burst::Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner)
{
	Super::Initialize(InData, InOwner);
	Data = Cast<UPDAFireModeBurst>(InData);
}

void UFireModeLogic_Burst::StartFire()
{
	bTriggerHeld = true;

	if (!Data || !GetWorld() || bBurstInProgress || bOnCooldown) return;

	ShotsRemainingInBurst = Data->BurstCount;
	bBurstInProgress = true;
	FireNextShotInBurst();
}

void UFireModeLogic_Burst::StopFire()
{
	bTriggerHeld = false;
}

void UFireModeLogic_Burst::FireNextShotInBurst()
{
	if (!Data || !GetWorld()) return;

	OnFireShot.Broadcast();
	ShotsRemainingInBurst--;

	if (ShotsRemainingInBurst <= 0)
	{
		bBurstInProgress = false;
		bOnCooldown = true;
		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this,
			&UFireModeLogic_Burst::OnCooldownFinished,
			Data->CooldownBetweenBursts, false);
		return;
	}

	// Progress through the burst as a 0-1 value for the optional curve.
	const float Progress = 1.f - static_cast<float>(ShotsRemainingInBurst) / static_cast<float>(Data->BurstCount);
	const float Multiplier = Data->FireRateCurve ? Data->FireRateCurve->GetFloatValue(Progress) : 1.f;
	const float RPM = FMath::Max(1.f, static_cast<float>(Data->BurstFireRate) * Multiplier);
	const float Delay = 60.f / RPM;

	GetWorld()->GetTimerManager().SetTimer(BurstShotTimer, this,
		&UFireModeLogic_Burst::FireNextShotInBurst, Delay, false);
}

void UFireModeLogic_Burst::OnCooldownFinished()
{
	bOnCooldown = false;

	if (Data && Data->bContinuousBurst && bTriggerHeld)
	{
		ShotsRemainingInBurst = Data->BurstCount;
		bBurstInProgress = true;
		FireNextShotInBurst();
	}
}
