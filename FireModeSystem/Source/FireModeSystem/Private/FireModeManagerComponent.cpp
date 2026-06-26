#include "FireModeManagerComponent.h"
#include "PDAFireModeBase.h"

UFireModeManagerComponent::UFireModeManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFireModeManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (FireModes.Num() > 0)
	{
		ActivateFireMode(0);
	}
}

void UFireModeManagerComponent::StartFire()
{
	if (ActiveLogic)
	{
		ActiveLogic->StartFire();
	}
}

void UFireModeManagerComponent::StopFire()
{
	if (ActiveLogic)
	{
		ActiveLogic->StopFire();
	}
}

void UFireModeManagerComponent::CycleFireMode()
{
	if (FireModes.Num() <= 1) return;

	if (ActiveLogic)
	{
		ActiveLogic->StopFire();
	}

	CurrentFireModeIndex = (CurrentFireModeIndex + 1) % FireModes.Num();
	ActivateFireMode(CurrentFireModeIndex);
}

UPDAFireModeBase* UFireModeManagerComponent::GetCurrentFireMode() const
{
	if (FireModes.IsValidIndex(CurrentFireModeIndex))
	{
		return FireModes[CurrentFireModeIndex];
	}
	return nullptr;
}

void UFireModeManagerComponent::ActivateFireMode(int32 Index)
{
	if (!FireModes.IsValidIndex(Index) || !FireModes[Index]) return;

	UPDAFireModeBase* ModeData = FireModes[Index];
	const TSubclassOf<UFireModeLogicBase> LogicClass = ModeData->GetLogicClass();

	if (!LogicClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("FireModeManagerComponent: '%s' returned no LogicClass."), *ModeData->GetName());
		return;
	}

	ActiveLogic = NewObject<UFireModeLogicBase>(this, LogicClass);
	ActiveLogic->OnFireShot.AddDynamic(this, &UFireModeManagerComponent::ForwardFireShot);
	ActiveLogic->Initialize(ModeData, this);
	CurrentFireModeIndex = Index;
}
