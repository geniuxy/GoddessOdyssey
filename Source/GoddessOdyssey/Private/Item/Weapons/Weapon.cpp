// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/Weapon.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	
	Sphere->SetupAttachment(GetRootComponent());
	
	EmbersEffect->SetupAttachment(GetRootComponent());

	// 设置武器的缩放值
	WeaponMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
}

void AWeapon::Equip(USceneComponent* InParent, FName SocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	AttachWeaponTo(InParent, SocketName);
	ItemState = EItemState::EIS_Equipped;
	if (Sphere)
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// if (EmbersEffect)
	// 	EmbersEffect->Deactivate();
}

void AWeapon::AttachWeaponTo(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(InParent, AttachmentRules, SocketName);

	// 设置武器的缩放值
	WeaponMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
}
