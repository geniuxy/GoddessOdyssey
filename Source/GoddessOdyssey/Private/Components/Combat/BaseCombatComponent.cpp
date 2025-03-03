// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/BaseCombatComponent.h"

#include "DebugHelper.h"
#include "Item/Weapons/Weapon.h"

void UBaseCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon)
{
	checkf(!CarriedWeaponMap.Contains(InWeaponTagToRegister),
	       TEXT("Weapon Tag named %s has already registered as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
		CurrentEquippedWeaponTag = InWeaponTagToRegister;

	const FString WeaponText = FString::Printf(
		TEXT("A weapon: %s, has been registered by tag: %s"),
		*InWeaponToRegister->GetName(),
		*InWeaponTagToRegister.ToString()
	);
	Debug::Print(WeaponText);
}

AWeapon* UBaseCombatComponent::GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWeapon* const* FoundWeapon = CarriedWeaponMap.Find(InWeaponTagToGet))
			return *FoundWeapon;
	}
	return nullptr;
}

AWeapon* UBaseCombatComponent::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
