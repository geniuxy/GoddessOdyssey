// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/GoddessCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "GoddessGameplayTags.h"
#include "Item/Weapons/GoddessWeapon.h"


void UGoddessCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon* InWeaponToRegister,
                                                    bool bRegisterAsEquippedWeapon)
{
	Super::RegisterSpawnedWeapon(InWeaponTagToRegister, InWeaponToRegister, bRegisterAsEquippedWeapon);
}

AWeapon* UGoddessCombatComponent::RemoveCurrentWeapon()
{
	if (!CarriedWeaponMap.IsEmpty())
	{
		Debug::Print(TEXT("CarriedWeaponMap is not empty"));
		// 移除 原本carried武器的delegate
		AWeapon* CurrentCarriedWeapon = GetCarriedWeaponByTag(GetRegisteredWeaponTag());
		CurrentCarriedWeapon->OnWeaponHitTarget.Unbind();
		CurrentCarriedWeapon->OnWeaponPulledFromTarget.Unbind();
		// 清空 CarriedWeaponMap 和 CurrentEquippedWeaponTag
		if (CurrentEquippedWeaponTag.IsValid())
		{
			FGameplayEventData Data;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				GetOwner(),
				GoddessGameplayTags::Character_Event_UnEquip,
				Data
			);
		}

		return CurrentCarriedWeapon;
	}
	return nullptr;
}

void UGoddessCombatComponent::ClearCarriedWeaponMap()
{
	CarriedWeaponMap.Empty();
}

AGoddessWeapon* UGoddessCombatComponent::GetGoddessCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AGoddessWeapon>(GetCarriedWeaponByTag(InWeaponTagToGet));
}

AGoddessWeapon* UGoddessCombatComponent::GetGoddessCurrentEquippedWeapon() const
{
	return Cast<AGoddessWeapon>(GetCurrentEquippedWeapon());
}

float UGoddessCombatComponent::GetCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetGoddessCurrentEquippedWeapon()->GoddessWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
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

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		GoddessGameplayTags::Character_Event_HitPause,
		FGameplayEventData()
	);
}

void UGoddessCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		GoddessGameplayTags::Character_Event_HitPause,
		FGameplayEventData()
	);
}
