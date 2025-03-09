// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpData.h"

#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "AbilitySystems/Abilities/BaseGameplayAbility.h"

void UDataAsset_StartUpData::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* InBaseASCToGiven,
                                                          int32 ApplyLevel)
{
	check(InBaseASCToGiven);

	GrantAbilities(ActivateOnGivenAbilities, InBaseASCToGiven, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InBaseASCToGiven, ApplyLevel);

	if (!StartUpEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& Effect : StartUpEffects)
		{
			if (!Effect) continue;

			UGameplayEffect* GameplayEffect = Effect->GetDefaultObject<UGameplayEffect>();

			InBaseASCToGiven->ApplyGameplayEffectToSelf(
				GameplayEffect,
				ApplyLevel,
				InBaseASCToGiven->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpData::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>>& InAbilitiesToGiven,
                                            UBaseAbilitySystemComponent* InBaseASCToGiven, int32 ApplyLevel)
{
	if (InAbilitiesToGiven.IsEmpty()) return;

	for (const TSubclassOf<UBaseGameplayAbility>& Ability : InAbilitiesToGiven)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InBaseASCToGiven->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InBaseASCToGiven->GiveAbility(AbilitySpec);
	}
}
