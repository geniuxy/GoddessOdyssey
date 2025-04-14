// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GoddessGE_CustomEffect.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGE_CustomEffect : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UGoddessGE_CustomEffect();
	
	void SetEffectAmount(float InAmount);
	void ClearModifiers();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	FGameplayAttribute Attribute;
};
