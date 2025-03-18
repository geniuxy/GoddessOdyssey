// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"
#include "GoddessGA_TargetLock.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGA_TargetLock : public UGoddessGameplayAbility
{
	GENERATED_BODY()

public:
	//~ Begin UGameplayAbility Interface.
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;
	//~ End UGameplayAbility Interface.
private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float BoxTraceDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	FVector TraceBoxSize = FVector(2000.f, 2000.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannels;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;
};
