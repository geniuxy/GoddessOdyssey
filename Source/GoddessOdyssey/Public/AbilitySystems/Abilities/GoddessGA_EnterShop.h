// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"
#include "GoddessGA_EnterShop.generated.h"

class ANPC;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGA_EnterShop : public UGoddessGameplayAbility
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
	
	UFUNCTION(BlueprintCallable)
	void LookForNearestNPC();

	UFUNCTION(BlueprintCallable)
	void OpenShopOverlay();

private:
	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> NPCTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugBox = false;

	UPROPERTY()
	ANPC* NearestNPC;
	
};
