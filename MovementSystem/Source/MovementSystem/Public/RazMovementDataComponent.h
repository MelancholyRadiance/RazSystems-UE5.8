#pragma once

#include "Components/ActorComponent.h"
#include "RazMovementDataComponent.generated.h"

class UPDAJumpData;
class UPDASprintData;
class UPDACrouchData;
class UPDAProneData;
class UPDAAimData;
class UPDAMovementInertiaData;
class UCharacterMovementComponent;

/**
 * Companion component that reads movement data assets and drives the Character's
 * CharacterMovementComponent. Add this to a Character alongside the default CMC.
 * Sprint, Crouch, and Prone stack multiplicatively and are not mutually exclusive.
 */
UCLASS(ClassGroup=(RazSystems), meta=(BlueprintSpawnableComponent))
class MOVEMENTSYSTEM_API URazMovementDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URazMovementDataComponent();

	// --- Data assets ----------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDAJumpData> JumpData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDASprintData> SprintData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDACrouchData> CrouchData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDAProneData> ProneData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDAAimData> AimData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Data")
	TObjectPtr<UPDAMovementInertiaData> InertiaData;

	// --- State ----------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetSprinting(bool bNewSprinting);

	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetAiming(bool bNewAiming);

	/** Uses CMC's native Crouch/UnCrouch so replication is handled by the engine. */
	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetCrouching(bool bNewCrouching);

	/** Prone uses manual capsule resize. Replicated via bProne. */
	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetProne(bool bNewProne);

	UFUNCTION(BlueprintPure, Category="Movement")
	bool IsSprinting() const { return bSprinting; }

	UFUNCTION(BlueprintPure, Category="Movement")
	bool IsAiming() const { return bAiming; }

	UFUNCTION(BlueprintPure, Category="Movement")
	bool IsProne() const { return bProne; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void ApplyInertiaData() const;
	void ApplyJumpData() const;
	void ApplyProneResize(bool bEntering) const;
	float GetCombinedSpeedMultiplier() const;

	UPROPERTY(Replicated)
	bool bSprinting = false;

	UPROPERTY(Replicated)
	bool bProne = false;

	UPROPERTY(Replicated)
	bool bAiming = false;

	/** Time spent continuously in each state, used to evaluate speed curves. */
	float SprintTime = 0.f;
	float CrouchTime = 0.f;
	float ProneTime = 0.f;

	float BaseWalkSpeed = 600.f;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CMC;
};
