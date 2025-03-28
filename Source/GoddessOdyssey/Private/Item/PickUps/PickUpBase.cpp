// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/PickUpBase.h"

#include "Components/SphereComponent.h"


APickUpBase::APickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->
		OnComponentBeginOverlap.AddUniqueDynamic(this, &APickUpBase::OnPickUpCollisionSphereBeginOverlap);
}

void APickUpBase::OnPickUpCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
}
