// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "GoddessAnimInstance.generated.h"

class AGoddess;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|Refrences")
	AGoddess* OwningGoddess;

	UPROPERTY()
	UCustomMovementComponent* GoddessMovementComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime; // 空闲已用时间
};
