// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "NPC.generated.h"

class UNPCInventoryComponent;
class UCameraComponent;
class USpringArmComponent;
class AGoddess;
class UWidgetComponent;
class USphereComponent;

UCLASS()
class GODDESSODYSSEY_API ANPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ANPC();

	UFUNCTION(BlueprintImplementableEvent, Category="Shop Interaction")
	void EnterShoppingMode(AGoddess* Goddess);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category="Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UNPCInventoryComponent* NPCInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shop Interaction")
	USphereComponent* TalkCollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Shop Interaction")
	UWidgetComponent* TalkWidget;

	UFUNCTION(BlueprintCallable, Category = "Shop Interaction")
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
