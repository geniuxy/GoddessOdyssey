// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"

#include "Characters/Goddess.h"
#include "PlayerControllers/GoddessController.h"

AGoddess* UGoddessGameplayAbility::GetGoddessFromActorInfo()
{
	if (!CachedGoddess.IsValid())
		CachedGoddess = Cast<AGoddess>(CurrentActorInfo->AvatarActor);

	return CachedGoddess.IsValid() ? CachedGoddess.Get() : nullptr;
}

AGoddessController* UGoddessGameplayAbility::GetGoddessControllerFromActorInfo()
{
	if (!CachedGoddessController.IsValid())
		CachedGoddessController = Cast<AGoddessController>(CurrentActorInfo->PlayerController);

	return CachedGoddessController.IsValid() ? CachedGoddessController.Get() : nullptr;
}

UGoddessCombatComponent* UGoddessGameplayAbility::GetGoddessCombatComponentFromActorInfo()
{
	return GetGoddessFromActorInfo()->GetGoddessCombatComponent();
}
