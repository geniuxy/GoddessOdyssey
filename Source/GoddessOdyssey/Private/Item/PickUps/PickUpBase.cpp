// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/PickUpBase.h"

#include "Characters/Goddess.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"


APickUpBase::APickUpBase()
{
	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	PickUpCollisionSphere->SetupAttachment(GetRootComponent());
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->
		OnComponentBeginOverlap.AddUniqueDynamic(this, &APickUpBase::OnPickUpCollisionSphereBeginOverlap);
	PickUpCollisionSphere->
		OnComponentEndOverlap.AddUniqueDynamic(this, &APickUpBase::OnPickUpCollisionSphereEndOverlap);
	
	PickUpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	PickUpWidget->SetupAttachment(RootComponent);
}

void APickUpBase::HidePickUpWidget()
{
	if (PickUpWidget)
	{
		PickUpWidget->SetWidgetClass(nullptr);
	}

	PickUpCollisionSphere->SetGenerateOverlapEvents(false);
}

void APickUpBase::SetPickUpWidgetVisibility(bool bWasVisible)
{
	if (PickUpWidget)
		PickUpWidget->SetVisibility(bWasVisible);
}

void APickUpBase::BeginPlay()
{
	Super::BeginPlay();

	SetPickUpWidgetVisibility(false);
}

void APickUpBase::OnPickUpCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		SetPickUpWidgetVisibility(true);
	}
}

void APickUpBase::OnPickUpCollisionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		SetPickUpWidgetVisibility(false);
	}
}
