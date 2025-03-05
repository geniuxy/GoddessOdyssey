// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/BaseAbilitySystemComponent.h"

#include "GoddessTypes/GoddessStructTypes.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UBaseAbilitySystemComponent::GrantGoddessWeaponAbilities(const TArray<FGoddessAbilitySet>& InAbilitiesToGrant,
                                                              int32 ApplyLevel,
                                                              TArray<FGameplayAbilitySpecHandle>&
                                                              OutGrantedAbilitySpecHandles)
{
	if (InAbilitiesToGrant.IsEmpty()) return;

	for (const FGoddessAbilitySet& Ability : InAbilitiesToGrant)
	{
		if (!Ability.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(Ability.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(Ability.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UBaseAbilitySystemComponent::RemoveGrantedGoddessWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;

	for (FGameplayAbilitySpecHandle& HandleToRemove : InSpecHandlesToRemove)
	{
		if (HandleToRemove.IsValid())
			ClearAbility(HandleToRemove);
	}

	InSpecHandlesToRemove.Empty();
}
