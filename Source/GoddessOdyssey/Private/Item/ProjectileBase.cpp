// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ProjectileBase.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileBoxComponent"));
	SetRootComponent(ProjectileBoxComponent);
	ProjectileBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->InitialSpeed = 500.f;
	ProjectileMovementComp->MaxSpeed = 500.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}
