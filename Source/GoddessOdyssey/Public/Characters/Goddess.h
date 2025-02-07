// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Goddess.generated.h"

class AWeapon;
class AItem;
class UInputAction;

UCLASS()
class GODDESSODYSSEY_API AGoddess : public ACharacter
{
	GENERATED_BODY()

public:
	AGoddess();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Equip();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* EquipAction;
	
	UPROPERTY(VisibleInstanceOnly, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;


private:

public:
	FORCEINLINE void SetOverlappingWeapon(AItem* Item) { OverlappingItem = Item; }
};
