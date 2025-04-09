// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/BaseGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AEnemy;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UEnemyGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="BaseAbility")
	AEnemy* GetEnemyFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BaseAbility")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BaseAbility")
	FGameplayEffectSpecHandle MakeEnemyEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	                                                    const FScalableFloat& InDamageScalableFloat,
	                                                    const float& InShieldPower);

private:
	TWeakObjectPtr<AEnemy> CachedEnemy;
};
