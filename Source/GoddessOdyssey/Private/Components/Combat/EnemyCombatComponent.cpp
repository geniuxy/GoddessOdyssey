// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoddessFunctionLibrary.h"
#include "GoddessGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Characters/Enemy.h"
#include "Components/BoxComponent.h"

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

void UEnemyCombatComponent::ToggleBodyCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AEnemy* Enemy = GetOwningPawn<AEnemy>();

	check(Enemy);

	UBoxComponent* LeftHandCollisionBox = Enemy->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = Enemy->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(
			bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(
			bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
		OverlappedActors.Empty();
}
