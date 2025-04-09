// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "NPC.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class GODDESSODYSSEY_API ANPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ANPC();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shop Interaction")
	USphereComponent* TalkCollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Shop Interaction")
	UWidgetComponent* TalkWidget;

	void SetTalkWidgetVisibility(bool bWasVisible);

	UFUNCTION()
	virtual void OnTalkCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnTalkCollisionSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

public:
};
