// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"

#include "Characters/Goddess.h"
#include "PlayerControllers/GoddessController.h"

AGoddess* UGoddessGameplayAbility::GetGoddessFromActorInfo()
{
	if (!CashedGoddess.IsValid())
		CashedGoddess = Cast<AGoddess>(CurrentActorInfo->AvatarActor);

	return CashedGoddess.IsValid() ? CashedGoddess.Get() : nullptr;
}

AGoddessController* UGoddessGameplayAbility::GetGoddessControllerFromActorInfo()
{
	if (!CashedGoddessController.IsValid())
		CashedGoddessController = Cast<AGoddessController>(CurrentActorInfo->PlayerController);

	return CashedGoddessController.IsValid() ? CashedGoddessController.Get() : nullptr;
}

UGoddessCombatComponent* UGoddessGameplayAbility::GetGoddessCombatComponent()
{
	return GetGoddessFromActorInfo()->GetGoddessCombatComponent();
}
