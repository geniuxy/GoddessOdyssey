// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/EnemyGameplayAbility.h"

#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Enemy.h"

AEnemy* UEnemyGameplayAbility::GetEnemyFromActorInfo()
{
	if (!CachedEnemy.IsValid())
		CachedEnemy = Cast<AEnemy>(CurrentActorInfo->AvatarActor);

	return CachedEnemy.IsValid() ? CachedEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
                                                                           const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle =
		GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(GoddessGameplayTags::Shared_SetByCaller_BaseDamage,
	                                               InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}
