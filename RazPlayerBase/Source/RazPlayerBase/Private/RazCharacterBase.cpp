#include "RazCharacterBase.h"
#include "RazMovementDataComponent.h"
#include "AmmoManagerComponent.h"
#include "RazIMC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ARazCharacterBase::ARazCharacterBase()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MovementData = CreateDefaultSubobject<URazMovementDataComponent>(TEXT("MovementData"));
	AmmoManager  = CreateDefaultSubobject<UAmmoManagerComponent>(TEXT("AmmoManager"));
}

void ARazCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (InputContext)
			{
				Sub->AddMappingContext(InputContext, 0);
			}
		}
	}

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	if (IA_Move)  EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ARazCharacterBase::Input_Move);
	if (IA_Look)  EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ARazCharacterBase::Input_Look);

	if (IA_Jump)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started,   this, &ACharacter::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	if (IA_Sprint)
	{
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_SprintStart);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_SprintStop);
	}
	if (IA_Crouch)
	{
		EIC->BindAction(IA_Crouch, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_CrouchStart);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_CrouchStop);
	}
	if (IA_Prone)
	{
		EIC->BindAction(IA_Prone, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_ProneStart);
		EIC->BindAction(IA_Prone, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_ProneStop);
	}
	if (IA_Aim)
	{
		EIC->BindAction(IA_Aim, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_AimStart);
		EIC->BindAction(IA_Aim, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_AimStop);
	}
	if (IA_Fire)
	{
		EIC->BindAction(IA_Fire, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_FireStart);
		EIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_FireStop);
	}
	if (IA_AltFire)
	{
		EIC->BindAction(IA_AltFire, ETriggerEvent::Started,   this, &ARazCharacterBase::Input_AltFireStart);
		EIC->BindAction(IA_AltFire, ETriggerEvent::Completed, this, &ARazCharacterBase::Input_AltFireStop);
	}
	if (IA_Reload)        EIC->BindAction(IA_Reload,        ETriggerEvent::Started, this, &ARazCharacterBase::Input_Reload);
	if (IA_CheckMagazine) EIC->BindAction(IA_CheckMagazine, ETriggerEvent::Started, this, &ARazCharacterBase::Input_CheckMagazine);
	if (IA_CycleFireMode) EIC->BindAction(IA_CycleFireMode, ETriggerEvent::Started, this, &ARazCharacterBase::Input_CycleFireMode);
}

// --- Movement ----------------------------------------------------------------

void ARazCharacterBase::Input_Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Axis.Y != 0.f) AddMovementInput(GetActorForwardVector(), Axis.Y);
	if (Axis.X != 0.f) AddMovementInput(GetActorRightVector(),   Axis.X);
}

void ARazCharacterBase::Input_Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Axis.X != 0.f) AddControllerYawInput(Axis.X);
	if (Axis.Y != 0.f) AddControllerPitchInput(Axis.Y);
}

void ARazCharacterBase::Input_SprintStart()  { if (MovementData) MovementData->SetSprinting(true);  }
void ARazCharacterBase::Input_SprintStop()   { if (MovementData) MovementData->SetSprinting(false); }
void ARazCharacterBase::Input_CrouchStart()  { if (MovementData) MovementData->SetCrouching(true);  }
void ARazCharacterBase::Input_CrouchStop()   { if (MovementData) MovementData->SetCrouching(false); }
void ARazCharacterBase::Input_ProneStart()   { if (MovementData) MovementData->SetProne(true);      }
void ARazCharacterBase::Input_ProneStop()    { if (MovementData) MovementData->SetProne(false);     }
void ARazCharacterBase::Input_AimStart()     { if (MovementData) MovementData->SetAiming(true);     }
void ARazCharacterBase::Input_AimStop()      { if (MovementData) MovementData->SetAiming(false);    }

// --- Weapon ------------------------------------------------------------------

void ARazCharacterBase::Input_FireStart()     { OnFire(true);  }
void ARazCharacterBase::Input_FireStop()      { OnFire(false); }
void ARazCharacterBase::Input_AltFireStart()  { OnAltFire(true);  }
void ARazCharacterBase::Input_AltFireStop()   { OnAltFire(false); }
void ARazCharacterBase::Input_Reload()        { OnReload();        }
void ARazCharacterBase::Input_CheckMagazine() { OnCheckMagazine(); }
void ARazCharacterBase::Input_CycleFireMode() { OnCycleFireMode(); }

// --- BlueprintNativeEvent defaults -------------------------------------------

void ARazCharacterBase::OnFire_Implementation(bool bPressed)        {}
void ARazCharacterBase::OnAltFire_Implementation(bool bPressed)     {}
void ARazCharacterBase::OnCycleFireMode_Implementation()            {}

void ARazCharacterBase::OnReload_Implementation()
{
	if (AmmoManager) AmmoManager->Reload(nullptr);
}

void ARazCharacterBase::OnCheckMagazine_Implementation()
{
	if (AmmoManager) AmmoManager->CheckMagazine();
}
