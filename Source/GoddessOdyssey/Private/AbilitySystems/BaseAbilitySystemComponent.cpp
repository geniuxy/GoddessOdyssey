// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/BaseAbilitySystemComponent.h"

#include "GoddessGameplayTags.h"
#include "GoddessTypes/GoddessStructTypes.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		if (InInputTag.MatchesTag(GoddessGameplayTags::Input_Toggleable) && AbilitySpec.IsActive())
			CancelAbilityHandle(AbilitySpec.Handle);
		else
			TryActivateAbility(AbilitySpec.Handle);
	}
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(GoddessGameplayTags::Input_MustBeHeld)) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
			CancelAbilityHandle(AbilitySpec.Handle);
	}
}

void UBaseAbilitySystemComponent::GrantGoddessWeaponAbilities(
	const TArray<FGoddessAbilitySet>& InAbilitiesToGrant,
	const TArray<FGoddessSpecialAbilitySet>& InSpecialAbilitiesToGrant,
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
		// Ability.InputTag作为一个标识或触发条件，帮助游戏逻辑在适当的时候激活Ability.AbilityToGrant
		AbilitySpec.DynamicAbilityTags.AddTag(Ability.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}

	for (const FGoddessAbilitySet& SpecialAbility : InSpecialAbilitiesToGrant)
	{
		if (!SpecialAbility.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(SpecialAbility.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		// Ability.InputTag作为一个标识或触发条件，帮助游戏逻辑在适当的时候激活Ability.AbilityToGrant
		AbilitySpec.DynamicAbilityTags.AddTag(SpecialAbility.InputTag);

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

bool UBaseAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag TagToActivate)
{
	check(TagToActivate.IsValid());
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
			return TryActivateAbility(SpecToActivate->Handle);
	}
	return false;
}
