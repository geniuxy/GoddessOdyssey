// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GoddessGE_UseEatableItem.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGE_UseEatableItem : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UGoddessGE_UseEatableItem();
	
	void SetEffectHealingAmount(float InHealAmount);
	void ClearModifiers();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	FGameplayAttribute Attribute;
};
