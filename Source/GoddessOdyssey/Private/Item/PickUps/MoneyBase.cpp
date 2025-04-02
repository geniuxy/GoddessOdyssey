// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/MoneyBase.h"

#include "DebugHelper.h"
#include "Characters/Goddess.h"

AMoneyBase::AMoneyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MoneyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Money"));
	MoneyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoneyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(GetRootComponent());
}

void AMoneyBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickUpCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                           SweepResult);

	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		Debug::Print(TEXT("I Touched A Money"));
	}
}

