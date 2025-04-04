// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "Item/Item.h"
#include "PickUpBase.generated.h"

class USphereComponent;

UCLASS()
class GODDESSODYSSEY_API APickUpBase : public AItem
{
	GENERATED_BODY()

public:
	APickUpBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Table|Pick Up")
	FGoddessSlotData PickUpSlotData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pick Up Interaction")
	USphereComponent* PickUpCollisionSphere;
	
	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
