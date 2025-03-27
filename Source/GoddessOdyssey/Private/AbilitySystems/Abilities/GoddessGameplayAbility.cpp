// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"

#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Goddess.h"
#include "PlayerControllers/GoddessController.h"

AGoddess* UGoddessGameplayAbility::GetGoddessFromActorInfo()
{
	if (!CachedGoddess.IsValid())
		CachedGoddess = Cast<AGoddess>(CurrentActorInfo->AvatarActor);

	return CachedGoddess.IsValid() ? CachedGoddess.Get() : nullptr;
}

AGoddessController* UGoddessGameplayAbility::GetGoddessControllerFromActorInfo()
{
	if (!CachedGoddessController.IsValid())
		CachedGoddessController = Cast<AGoddessController>(CurrentActorInfo->PlayerController);

	return CachedGoddessController.IsValid() ? CachedGoddessController.Get() : nullptr;
}

UGoddessCombatComponent* UGoddessGameplayAbility::GetGoddessCombatComponentFromActorInfo()
{
	return GetGoddessFromActorInfo()->GetGoddessCombatComponent();
}

FGameplayEffectSpecHandle UGoddessGameplayAbility::MakeGoddessEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle =
		GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(GoddessGameplayTags::Shared_SetByCaller_BaseDamage, InBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);

	return EffectSpecHandle;
}

bool UGoddessGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime,
                                                               float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());
	
	FGameplayEffectQuery CooldownQuery =
		FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());
	
	TArray<TPair<float, float>> TimeRemainingAndDuration =
		GetBaseAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);
	
	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}
	
	return RemainingCooldownTime > 0.f;
}
