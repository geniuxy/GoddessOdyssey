// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class UCustomMovementComponent;
class UCharacterMovementComponent;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ABaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float LocomotionDirection;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Reference,meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	void GetGroundSpeed();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Reference,meta = (AllowPrivateAccess = "true"))
	float AirSpeed;
	void GetAirSpeed();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Reference,meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;
	void GetShouldMove();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Reference,meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;
	void GetIsFalling();
};
