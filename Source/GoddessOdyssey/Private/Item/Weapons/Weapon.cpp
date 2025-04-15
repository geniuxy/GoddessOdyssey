// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/Weapon.h"

#include "Components/BoxComponent.h"
#include "GoddessFunctionLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Characters/NPC.h"

AWeapon::AWeapon()
{
	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeapon::OnWeaponBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AWeapon::OnWeaponEndOverlap);
}

void AWeapon::AttachWeaponTo(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, AttachmentRules, SocketName);
}

void AWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instiagtor as the owning pawn for the weapon: %s"), *GetName());

	if (ABaseCharacter* HitPawn = Cast<ABaseCharacter>(OtherActor))
	{
		if (Cast<ANPC>(OtherActor) != nullptr) return;
		if (UGoddessFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
	}
}

void AWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instiagtor as the owning pawn for the weapon: %s"), *GetName());

	if (ABaseCharacter* HitPawn = Cast<ABaseCharacter>(OtherActor))
	{
		if (Cast<ANPC>(OtherActor) != nullptr) return;
		if (UGoddessFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
	}
}
