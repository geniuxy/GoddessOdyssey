// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Goddess.h"

#include "EnhancedInputComponent.h"
#include "Item/Weapons/Weapon.h"

AGoddess::AGoddess()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AGoddess::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGoddess::Equip()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh()->GetChildComponent(0), FName("RightHandSocket"), this, this);
		// HeroState = EHeroState::EHS_EquippedOneHandedWeapon;
		EquippedWeapon = OverlappingWeapon;
		OverlappingItem = nullptr;
	}
}

void AGoddess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoddess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AGoddess::Equip);
	}
}

