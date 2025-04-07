// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/BaseCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Item/Weapons/Weapon.h"

void UBaseCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon)
{
	checkf(InWeaponTagToRegister.IsValid(),
	       TEXT("Weapon Tag named %s is invalid"), *InWeaponTagToRegister.ToString());
	checkf(!CarriedWeaponMap.Contains(InWeaponTagToRegister),
	       TEXT("Weapon Tag named %s has already registered as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	// 注册武器的时候就将delegate绑定对应的方法
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
		CurrentEquippedWeaponTag = InWeaponTagToRegister;

	// const FString WeaponText = FString::Printf(
	// 	TEXT("A weapon: %s, has been registered by tag: %s"),
	// 	*InWeaponToRegister->GetName(),
	// 	*InWeaponTagToRegister.ToString()
	// );
	// Debug::Print(WeaponText);
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

void UBaseCombatComponent::ToggleDamageCollisionBox(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ToggleCurrentEquippedWeaponCollision(bShouldEnable);
	}
	else
	{
		// Handle body collision boxes
		ToggleBodyCollision(bShouldEnable, ToggleDamageType);
	}
}

void UBaseCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
	AWeapon* WeaponToToggle = GetCurrentEquippedWeapon();

	check(WeaponToToggle);

	if (bShouldEnable)
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}
}

void UBaseCombatComponent::ToggleBodyCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
}

void UBaseCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UBaseCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

FGameplayTag UBaseCombatComponent::GetRegisteredWeaponTag()
{
	if (CarriedWeaponMap.IsEmpty())
		return FGameplayTag::EmptyTag;
	// 获取第一个键值对的键和值
	TTuple<FGameplayTag, AWeapon*> Pair = *CarriedWeaponMap.CreateIterator();
	FGameplayTag RegisteredWeaponTag = Pair.Key;
	return RegisteredWeaponTag;
}
