// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Goddess/GoddessAnimInstance.h"

#include "Characters/Goddess.h"
#include "Components/CustomMovementComponent.h"

void UGoddessAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
		OwningGoddess = Cast<AGoddess>(OwningCharacter);
	
	if(OwningMovementComponent)
	{
		GoddessMovementComponent = Cast<UCustomMovementComponent>(OwningMovementComponent);
	}
}

void UGoddessAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bShouldMove)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		// bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
		// 暂时取消进入relax state
		bShouldEnterRelaxState = false;
	}
	if (!GoddessMovementComponent) return;
	GetIsClimbing();
	GetClimbVelocity();
}

void UGoddessAnimInstance::GetIsClimbing()
{
	bIsClimbing = GoddessMovementComponent->IsClimbing();
}

void UGoddessAnimInstance::GetClimbVelocity()
{
	ClimbVelocity = GoddessMovementComponent->GetUnrotatedClimbVelocity();
}
