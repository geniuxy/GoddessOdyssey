// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "Item/Item.h"
#include "PickUpBase.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class GODDESSODYSSEY_API APickUpBase : public AItem
{
	GENERATED_BODY()

public:
	APickUpBase();

	UFUNCTION(BlueprintCallable)
	void HidePickUpWidget();
protected:
	virtual void BeginPlay() override;
	
	void SetPickUpWidgetVisibility(bool bWasVisible);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pick Up Interaction")
	USphereComponent* PickUpCollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Pick Up Interaction")
	UWidgetComponent* PickUpWidget;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnPickUpCollisionSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

public:
	FORCEINLINE USphereComponent* GetPickUpCollisionSphere() const { return PickUpCollisionSphere; }
};
