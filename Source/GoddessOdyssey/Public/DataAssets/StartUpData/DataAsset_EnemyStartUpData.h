// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpData.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven,
											  int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UEnemyGameplayAbility>> EnemyCombatAbilities;
};
