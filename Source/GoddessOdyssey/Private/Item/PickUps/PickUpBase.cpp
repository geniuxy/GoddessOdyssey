// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/PickUpBase.h"

#include "Components/SphereComponent.h"


APickUpBase::APickUpBase()
{
	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	PickUpCollisionSphere->SetupAttachment(GetRootComponent());
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
