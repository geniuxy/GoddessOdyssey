// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

struct FGoddessAbilitySet;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category="Ability", meta=(ApplyLevel = "1"))
	void GrantGoddessWeaponAbilities(const TArray<FGoddessAbilitySet>& InAbilitiesToGrant, int32 ApplyLevel);
};
