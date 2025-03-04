// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/GoddessCombatComponent.h"

#include "Item/Weapons/GoddessWeapon.h"

AGoddessWeapon* UGoddessCombatComponent::GetGoddessCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AGoddessWeapon>(GetCarriedWeaponByTag(InWeaponTagToGet));
}
