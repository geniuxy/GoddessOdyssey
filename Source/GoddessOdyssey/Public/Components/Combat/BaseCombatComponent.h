// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/BaseExtensionComponent.h"
#include "BaseCombatComponent.generated.h"

class AInventoryItemBase;
class AWeapon;

UENUM(BlueprintType)
enum class EToggleDamageType:uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseCombatComponent : public UBaseExtensionComponent
{
	GENERATED_BODY()

public:
#pragma region Weapon
	UFUNCTION(BlueprintCallable, Category="Combat")
	virtual void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon* InWeaponToRegister,
	                                   bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category="Combat")
	AWeapon* GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	FGameplayTag CurrentCarriedWeaponTag;

	UFUNCTION(BlueprintCallable, Category="Combat")
	AWeapon* GetCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ToggleDamageCollisionBox(bool bShouldEnable,
	                              EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
#pragma endregion

	UFUNCTION(BlueprintCallable, Category="Combat")
	virtual void RegisterShield(
		FGameplayTag InShieldTagToRegister,
		TSubclassOf<AInventoryItemBase> InShieldToRegister,
		float InShieldPower
	);

	UFUNCTION(BlueprintCallable, Category="Combat")
	TSubclassOf<AInventoryItemBase> GetCarriedShieldByTag(FGameplayTag InShieldTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	FGameplayTag CurrentCarriedShieldTag;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	float CurrentCarriedShieldPower = 0.f;

protected:
	TArray<AActor*> OverlappedActors;

	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TMap<FGameplayTag, AWeapon*> CarriedWeaponMap;

	TMap<FGameplayTag, TSubclassOf<AInventoryItemBase>> CarriedShieldMap;

private:
};
