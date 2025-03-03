// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/BaseAbilitySystemComponent.h"

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
