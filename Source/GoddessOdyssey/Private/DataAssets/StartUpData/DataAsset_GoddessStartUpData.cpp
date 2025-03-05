// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_GoddessStartUpData.h"

#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "GoddessTypes/GoddessStructTypes.h"

void UDataAsset_GoddessStartUpData::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven,
                                                                 int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InBaseASCToGiven, ApplyLevel);

	for (const FGoddessAbilitySet& StartUpAbilitySet : GoddessStartUpAbilitySets)
	{
		if (!StartUpAbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(StartUpAbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InBaseASCToGiven->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(StartUpAbilitySet.InputTag);

		InBaseASCToGiven->GiveAbility(AbilitySpec);
	}
}
