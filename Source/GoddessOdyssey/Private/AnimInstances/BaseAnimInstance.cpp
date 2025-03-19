// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BaseAnimInstance.h"

#include "GameplayTagContainer.h"
#include "GoddessFunctionLibrary.h"

bool UBaseAnimInstance::DoesActorHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn  = TryGetPawnOwner())
		return UGoddessFunctionLibrary::NativeDoesActorHaveTag(OwningPawn , TagToCheck);
	return false;
}
