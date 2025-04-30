// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GetGroundSpeed();
	GetShouldMove();

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(
		GetOwningActor()->GetVelocity(),
		GetOwningActor()->GetActorRotation()
	);

	GetAirSpeed();
	GetIsFalling();
}

void UCharacterAnimInstance::GetGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(OwningCharacter->GetVelocity());
}

void UCharacterAnimInstance::GetAirSpeed()
{
	AirSpeed = OwningCharacter->GetVelocity().Z;
}

void UCharacterAnimInstance::GetShouldMove()
{
	bShouldMove =
		OwningMovementComponent->GetCurrentAcceleration().Size() > 0 &&
		GroundSpeed > 5.f &&
		!bIsFalling;
}

void UCharacterAnimInstance::GetIsFalling()
{
	bIsFalling = OwningMovementComponent->IsFalling();
}
