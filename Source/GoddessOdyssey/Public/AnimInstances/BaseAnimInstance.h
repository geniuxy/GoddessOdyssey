// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,meta=(BlueprintThreadSafe))
	bool DoesActorHaveTag(FGameplayTag TagToCheck) const;
	
};
