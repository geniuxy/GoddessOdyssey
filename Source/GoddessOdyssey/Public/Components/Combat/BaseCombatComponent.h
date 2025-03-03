// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/BaseExtensionComponent.h"
#include "BaseCombatComponent.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseCombatComponent : public UBaseExtensionComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon* InWeaponToRegister,
	                           bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category="Combat")
	AWeapon* GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	AWeapon* GetCurrentEquippedWeapon() const;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	FGameplayTag CurrentEquippedWeaponTag;

private:
	TMap<FGameplayTag, AWeapon*> CarriedWeaponMap;
};
