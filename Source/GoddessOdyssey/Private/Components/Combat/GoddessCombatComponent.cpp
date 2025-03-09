// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/GoddessCombatComponent.h"
#include "Item/Weapons/GoddessWeapon.h"
#include "DebugHelper.h"


AGoddessWeapon* UGoddessCombatComponent::GetGoddessCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AGoddessWeapon>(GetCarriedWeaponByTag(InWeaponTagToGet));
}

void UGoddessCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(),
	             FColor::Green);
}

void UGoddessCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(
		GetOwningPawn()->GetActorNameOrLabel() + TEXT(" 's weapon pulled from ' ") + InteractedActor->
		GetActorNameOrLabel(), FColor::Red);
}
