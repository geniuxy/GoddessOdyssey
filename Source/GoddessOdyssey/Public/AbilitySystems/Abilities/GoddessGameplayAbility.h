// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/BaseGameplayAbility.h"
#include "GoddessGameplayAbility.generated.h"

class UGoddessCombatComponent;
class AGoddessController;
class AGoddess;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="BaseAbility")
	AGoddess* GetGoddessFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BaseAbility")
	AGoddessController* GetGoddessControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BaseAbility")
	UGoddessCombatComponent* GetGoddessCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AGoddess> CachedGoddess;
	TWeakObjectPtr<AGoddessController> CachedGoddessController;
};
