// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"


UCustomMovementComponent::UCustomMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCustomMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

