// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "GameFramework/Actor.h"
#include "MoneyBase.generated.h"

UCLASS()
class GODDESSODYSSEY_API AMoneyBase : public APickUpBase
{
	GENERATED_BODY()
	
public:	
	AMoneyBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* MoneyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Table")
	FDataTableRowHandle MoneyHandle;

	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
};
