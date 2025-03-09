// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/BaseCombatComponent.h"
#include "GoddessCombatComponent.generated.h"

class AGoddessWeapon;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessCombatComponent : public UBaseCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Combat")
	AGoddessWeapon* GetGoddessCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
