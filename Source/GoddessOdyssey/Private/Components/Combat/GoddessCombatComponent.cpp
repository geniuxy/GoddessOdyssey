// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/GoddessCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoddessGameplayTags.h"
#include "Item/Weapons/GoddessWeapon.h"


AGoddessWeapon* UGoddessCombatComponent::GetGoddessCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AGoddessWeapon>(GetCarriedWeaponByTag(InWeaponTagToGet));
}

void UGoddessCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		GoddessGameplayTags::Shared_Event_MeleeAttack,
		Data
	);
}

void UGoddessCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
