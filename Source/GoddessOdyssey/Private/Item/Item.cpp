// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

#include "Characters/Goddess.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(ItemMesh);

	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EmbersEffect"));
	EmbersEffect->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Carried)
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));

	// float MoveSpeed = 50.f;
	// float RotatorSpeed = 45.f;
	// float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	// AddActorWorldOffset(FVector(MoveSpeed * DeltaTime, 0.f, DeltaZ));
	// AddActorWorldRotation(FRotator(0.f, RotatorSpeed * DeltaTime, 0.f));
	// DRAW_SPHERE_SINGLE_FRAME(GetActorLocation());
	// DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
	// DRAW_POINT_SINGLE_FRAME(Avg<FVector>(GetActorLocation(), FVector::ZeroVector));
}


