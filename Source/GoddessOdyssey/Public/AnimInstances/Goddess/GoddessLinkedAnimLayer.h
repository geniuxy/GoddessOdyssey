// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "GoddessLinkedAnimLayer.generated.h"

class UGoddessAnimInstance;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessLinkedAnimLayer : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UGoddessAnimInstance* GetGoddessAnimInstance() const;
};
