#pragma once

#include "Components/ActorComponent.h"
#include "FireModeLogicBase.h"
#include "FireModeManagerComponent.generated.h"

class UPDAFireModeBase;

/**
 * Add this component to your weapon actor. Populate FireModes with your PDA_SemiAuto / PDA_Burst /
 * PDA_FullAuto assets, then bind OnFireShot to your weapon's actual shot logic.
 *
 * Call StartFire() / StopFire() from your input events.
 * Call CycleFireMode() to advance through the modes list.
 */
UCLASS(ClassGroup=(RazSystems), meta=(BlueprintSpawnableComponent))
class FIREMODESYSTEM_API UFireModeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFireModeManagerComponent();

	/** Fire mode data assets to make available on this weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FireMode")
	TArray<TObjectPtr<UPDAFireModeBase>> FireModes;

	/**
	 * Broadcast each time the active fire mode decides a shot should fire.
	 * Bind your weapon's shot logic (spawn projectile, play anim, etc.) here.
	 */
	UPROPERTY(BlueprintAssignable, Category="FireMode")
	FOnFireShotSignature OnFireShot;

	/** Call this when the player presses the trigger. */
	UFUNCTION(BlueprintCallable, Category="FireMode")
	void StartFire();

	/** Call this when the player releases the trigger. */
	UFUNCTION(BlueprintCallable, Category="FireMode")
	void StopFire();

	/** Advances to the next fire mode in the list, wrapping around. */
	UFUNCTION(BlueprintCallable, Category="FireMode")
	void CycleFireMode();

	UFUNCTION(BlueprintPure, Category="FireMode")
	UPDAFireModeBase* GetCurrentFireMode() const;

	UFUNCTION(BlueprintPure, Category="FireMode")
	int32 GetCurrentFireModeIndex() const { return CurrentFireModeIndex; }

protected:
	virtual void BeginPlay() override;

private:
	void ActivateFireMode(int32 Index);

	UFUNCTION()
	void ForwardFireShot() { OnFireShot.Broadcast(); }

	UPROPERTY()
	TObjectPtr<UFireModeLogicBase> ActiveLogic;

	int32 CurrentFireModeIndex = 0;
};
