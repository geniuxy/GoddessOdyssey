// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Goddess/GoddessAnimInstance.h"

#include "Characters/Goddess.h"

void UGoddessAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
		OwningGoddess = Cast<AGoddess>(OwningCharacter);
}

void UGoddessAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
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
}
