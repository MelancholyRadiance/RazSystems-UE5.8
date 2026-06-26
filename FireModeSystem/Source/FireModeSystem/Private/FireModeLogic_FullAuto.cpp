#include "FireModeLogic_FullAuto.h"
#include "PDAFireModeFullAuto.h"

void UFireModeLogic_FullAuto::Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner)
{
	Super::Initialize(InData, InOwner);
	Data = Cast<UPDAFireModeFullAuto>(InData);
}

void UFireModeLogic_FullAuto::StartFire()
{
	if (!Data || !GetWorld() || bFiring) return;

	bFiring = true;
	FireStartTime = GetWorld()->GetTimeSeconds();
	FireAndScheduleNext();
}

void UFireModeLogic_FullAuto::StopFire()
{
	bFiring = false;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}

void UFireModeLogic_FullAuto::FireAndScheduleNext()
{
	if (!bFiring || !Data || !GetWorld()) return;

	OnFireShot.Broadcast();

	const float RPM = GetCurrentRPM();
	const float Delay = 60.f / FMath::Max(1.f, RPM);
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this,
		&UFireModeLogic_FullAuto::FireAndScheduleNext, Delay, false);
}

float UFireModeLogic_FullAuto::GetCurrentRPM() const
{
	if (Data->FireRateCurve && GetWorld())
	{
		const float SecondsHeld = GetWorld()->GetTimeSeconds() - FireStartTime;
		const float Multiplier = FMath::Clamp(Data->FireRateCurve->GetFloatValue(SecondsHeld), 0.f, 1.f);
		return static_cast<float>(Data->FireRate) * Multiplier;
	}
	return static_cast<float>(Data->FireRate);
}
