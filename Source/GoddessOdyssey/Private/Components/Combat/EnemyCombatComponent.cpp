// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoddessFunctionLibrary.h"
#include "GoddessGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	// block logic
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking =
		UGoddessFunctionLibrary::NativeDoesActorHaveTag(HitActor, GoddessGameplayTags::Character_Status_Blocking);
	const bool bIsAttackUnblockable =
		UGoddessFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), GoddessGameplayTags::Enemy_Status_UnBlockable);

	if (bIsPlayerBlocking && !bIsAttackUnblockable)
	{
		bIsValidBlock = UGoddessFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			GoddessGameplayTags::Character_Event_SuccessfulBlock,
			Data
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			GoddessGameplayTags::Shared_Event_MeleeAttack,
			Data
		);
	}
}
