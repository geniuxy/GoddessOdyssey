// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpData.generated.h"

class UGameplayEffect;
class UBaseGameplayAbility;
class UBaseAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UDataAsset_StartUpData : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpEffects;
	
	void GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>>& InAbilitiesToGiven,
	                    UBaseAbilitySystemComponent* InBaseASCToGiven, int32 ApplyLevel = 1);
};
