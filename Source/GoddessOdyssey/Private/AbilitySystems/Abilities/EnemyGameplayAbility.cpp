// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/EnemyGameplayAbility.h"

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
