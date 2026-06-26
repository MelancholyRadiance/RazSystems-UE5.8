#include "FireModeLogicBase.h"
#include "Components/ActorComponent.h"

void UFireModeLogicBase::Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner)
{
	OwnerComponent = InOwner;
}

UWorld* UFireModeLogicBase::GetWorld() const
{
	return OwnerComponent ? OwnerComponent->GetWorld() : nullptr;
}
