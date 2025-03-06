// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "AbilitySystems/Abilities/EnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InBaseASCToGiven, ApplyLevel);

	for (const TSubclassOf<UEnemyGameplayAbility>& EnemyStartUpAbility : EnemyStartUpAbilities)
	{
		if (!EnemyStartUpAbility) continue;

		FGameplayAbilitySpec AbilitySpec(EnemyStartUpAbility);
		AbilitySpec.SourceObject = InBaseASCToGiven->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InBaseASCToGiven->GiveAbility(AbilitySpec);
	}
}
