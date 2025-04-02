// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Money/MoneyBase.h"

AMoneyBase::AMoneyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MoneyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Money"));
	MoneyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoneyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(MoneyMesh);
}

