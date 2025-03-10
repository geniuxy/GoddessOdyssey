// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/BaseGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Components/Combat/BaseCombatComponent.h"
#include "GoddessTypes/GoddessEnumTypes.h"

void UBaseGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EBaseAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EBaseAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UBaseCombatComponent* UBaseGameplayAbility::GetBaseCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UBaseCombatComponent>();
}

UBaseAbilitySystemComponent* UBaseGameplayAbility::GetBaseAbilitySystemComponentFromActorInfo() const
{
	return Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UBaseGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	return GetBaseAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UBaseGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EGoddessSuccessType& OutSuccessType)
{
	const FActiveGameplayEffectHandle EffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = EffectHandle.WasSuccessfullyApplied()
		                 ? EGoddessSuccessType::Successful
		                 : EGoddessSuccessType::Failed;

	return EffectHandle;
}
