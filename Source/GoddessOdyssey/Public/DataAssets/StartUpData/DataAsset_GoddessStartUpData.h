// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystems/Abilities/BaseGameplayAbility.h"
#include "DataAssets/StartUpData/DataAsset_StartUpData.h"
#include "DataAsset_GoddessStartUpData.generated.h"

struct FGoddessAbilitySet;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UDataAsset_GoddessStartUpData : public UDataAsset_StartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven,
	                                          int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty="InputTag"))
	TArray<FGoddessAbilitySet> GoddessStartUpAbilitySets;
};
