// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/StoneBase.h"

#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Goddess.h"

void AStoneBase::OnPickUpCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		Goddess->GetBaseAbilitySystemComponent()
		       ->TryActivateAbilityByTag(GoddessGameplayTags::Character_Ability_PickUp_Stone);
	}
}
