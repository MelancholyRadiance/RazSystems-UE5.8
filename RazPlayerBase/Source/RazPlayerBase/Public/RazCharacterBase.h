#pragma once

#include "GameFramework/Character.h"
#include "RazCharacterBase.generated.h"

class URazMovementDataComponent;
class UAmmoManagerComponent;
class USpringArmComponent;
class UCameraComponent;
class URazIMC;
class UInputAction;
struct FInputActionValue;

/**
 * Abstract base character with RazSystems pre-wired.
 *
 * Setup in your subclass (Blueprint or C++):
 *   1. Assign InputContext (URazIMC asset).
 *   2. Assign each IA_* slot to the matching UInputAction asset from the same folder.
 *   3. Assign data assets on MovementData (JumpData, SprintData, etc.) and AmmoManager.
 *   4. Override OnFire / OnAltFire / OnReload / OnCycleFireMode to drive your weapon actor.
 *
 * Move and Look are fully handled in C++.
 * Reload and CheckMagazine call AmmoManager directly as a default implementation.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class RAZPLAYERBASE_API ARazCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARazCharacterBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<URazMovementDataComponent> MovementData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UAmmoManagerComponent> AmmoManager;

	// --- Input context --------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TObjectPtr<URazIMC> InputContext;

	// --- Input actions --------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Sprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Crouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Prone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Movement")
	TObjectPtr<UInputAction> IA_Aim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Weapon")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Weapon")
	TObjectPtr<UInputAction> IA_AltFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Weapon")
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Weapon")
	TObjectPtr<UInputAction> IA_CheckMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Weapon")
	TObjectPtr<UInputAction> IA_CycleFireMode;

	// --- Weapon hooks (override in subclass) ----------------------------------

	/** Called when Fire is pressed (bPressed=true) or released (bPressed=false). */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	void OnFire(bool bPressed);

	/** Called when AltFire is pressed or released. */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	void OnAltFire(bool bPressed);

	/** Called on Reload input. Default: calls AmmoManager->Reload(any calibre). */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	void OnReload();

	/** Called on CheckMagazine input. Default: calls AmmoManager->CheckMagazine(). */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	void OnCheckMagazine();

	/** Called on CycleFireMode input. Override to forward to your weapon's FireModeManagerComponent. */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	void OnCycleFireMode();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_SprintStart();
	void Input_SprintStop();
	void Input_CrouchStart();
	void Input_CrouchStop();
	void Input_ProneStart();
	void Input_ProneStop();
	void Input_AimStart();
	void Input_AimStop();
	void Input_FireStart();
	void Input_FireStop();
	void Input_AltFireStart();
	void Input_AltFireStop();
	void Input_Reload();
	void Input_CheckMagazine();
	void Input_CycleFireMode();
};
