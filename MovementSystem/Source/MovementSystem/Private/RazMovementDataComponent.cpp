#include "RazMovementDataComponent.h"

#include "PDAJumpData.h"
#include "PDASprintData.h"
#include "PDACrouchData.h"
#include "PDAProneData.h"
#include "PDAAimData.h"
#include "PDAMovementInertiaData.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

URazMovementDataComponent::URazMovementDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void URazMovementDataComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		CMC = Owner->GetCharacterMovement();
	}

	if (!CMC)
	{
		return;
	}

	BaseWalkSpeed = CMC->MaxWalkSpeed;
	ApplyInertiaData();
	ApplyJumpData();
}

void URazMovementDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CMC)
	{
		return;
	}

	// Advance state timers only while in the state
	if (bSprinting) SprintTime += DeltaTime;
	else            SprintTime = 0.f;

	if (CMC->IsCrouching()) CrouchTime += DeltaTime;
	else                    CrouchTime = 0.f;

	if (bProne) ProneTime += DeltaTime;
	else        ProneTime = 0.f;

	CMC->MaxWalkSpeed = BaseWalkSpeed * GetCombinedSpeedMultiplier();
	CMC->MaxWalkSpeedCrouched = BaseWalkSpeed * GetCombinedSpeedMultiplier();
}

void URazMovementDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URazMovementDataComponent, bSprinting);
	DOREPLIFETIME(URazMovementDataComponent, bProne);
	DOREPLIFETIME(URazMovementDataComponent, bAiming);
}

void URazMovementDataComponent::SetSprinting(bool bNewSprinting)
{
	bSprinting = bNewSprinting;
}

void URazMovementDataComponent::SetAiming(bool bNewAiming)
{
	bAiming = bNewAiming;
}

void URazMovementDataComponent::SetCrouching(bool bNewCrouching)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		if (bNewCrouching)
		{
			Owner->Crouch();
		}
		else
		{
			Owner->UnCrouch();
		}
	}
}

void URazMovementDataComponent::SetProne(bool bNewProne)
{
	if (bProne == bNewProne)
	{
		return;
	}
	bProne = bNewProne;
	ApplyProneResize(bNewProne);
}

// ---------------------------------------------------------------------------

void URazMovementDataComponent::ApplyInertiaData() const
{
	if (!CMC || !InertiaData)
	{
		return;
	}
	CMC->MaxAcceleration                = InertiaData->MaxAcceleration;
	CMC->BrakingDecelerationWalking     = InertiaData->BrakingDeceleration;
	CMC->GroundFriction                 = InertiaData->GroundFriction;
	CMC->AirControl                     = InertiaData->AirControl;
	CMC->BrakingDecelerationFalling     = InertiaData->BrakingDecelerationFalling;
}

void URazMovementDataComponent::ApplyJumpData() const
{
	if (!CMC || !JumpData)
	{
		return;
	}
	CMC->JumpZVelocity = JumpData->JumpZVelocity;

	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		Owner->JumpMaxCount = JumpData->MaxJumpCount;
	}
}

void URazMovementDataComponent::ApplyProneResize(bool bEntering) const
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner || !ProneData)
	{
		return;
	}

	UCapsuleComponent* Capsule = Owner->GetCapsuleComponent();
	if (!Capsule)
	{
		return;
	}

	// Manual resize — not as authoritative as CMC crouch in competitive MP, but safe for most use cases.
	const float TargetHalfHeight = bEntering
		? ProneData->PronedHalfHeight
		: Owner->GetDefaultHalfHeight();

	Capsule->SetCapsuleHalfHeight(TargetHalfHeight);
}

float URazMovementDataComponent::GetCombinedSpeedMultiplier() const
{
	float Multiplier = 1.f;

	if (bSprinting && SprintData)
	{
		if (SprintData->SpeedCurve)
		{
			Multiplier *= SprintData->SpeedCurve->GetFloatValue(SprintTime);
		}
		else
		{
			Multiplier *= SprintData->SpeedMultiplier;
		}
	}

	if (CMC && CMC->IsCrouching() && CrouchData)
	{
		if (CrouchData->SpeedCurve)
		{
			Multiplier *= CrouchData->SpeedCurve->GetFloatValue(CrouchTime);
		}
		else
		{
			Multiplier *= CrouchData->SpeedMultiplier;
		}
	}

	if (bProne && ProneData)
	{
		if (ProneData->SpeedCurve)
		{
			Multiplier *= ProneData->SpeedCurve->GetFloatValue(ProneTime);
		}
		else
		{
			Multiplier *= ProneData->SpeedMultiplier;
		}
	}

	if (bAiming && AimData)
	{
		Multiplier *= AimData->SpeedMultiplier;
	}

	return Multiplier;
}
