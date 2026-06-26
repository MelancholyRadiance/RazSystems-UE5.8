#pragma once

#include "UObject/NoExportTypes.h"
#include "FireModeLogicBase.generated.h"

class UPDAFireModeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireShotSignature);

/**
 * Base class for fire mode runtime logic. One instance is created per active fire mode.
 * Subclasses handle the timing, burst counting, and rate limiting for their mode.
 * Bind OnFireShot to your weapon's actual shot function.
 */
UCLASS(Abstract, BlueprintType)
class FIREMODESYSTEM_API UFireModeLogicBase : public UObject
{
	GENERATED_BODY()

public:
	/** Broadcast each time the fire mode decides a shot should be fired. */
	UPROPERTY(BlueprintAssignable, Category="FireMode")
	FOnFireShotSignature OnFireShot;

	/** Called once after the object is created. InOwner is the component that owns this logic. */
	virtual void Initialize(UPDAFireModeBase* InData, UActorComponent* InOwner);

	UFUNCTION(BlueprintCallable, Category="FireMode")
	virtual void StartFire() {}

	UFUNCTION(BlueprintCallable, Category="FireMode")
	virtual void StopFire() {}

	virtual UWorld* GetWorld() const override;

protected:
	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};
