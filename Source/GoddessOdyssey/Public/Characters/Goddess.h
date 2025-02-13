// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoddessType.h"
#include "GameFramework/Character.h"
#include "Goddess.generated.h"

enum class EGoddessActionState : uint8;
class AWeapon;
class AItem;
class UInputAction;
class UInputMappingContext;

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

	EGoddessEquippedState EquippedState = EGoddessEquippedState::EGES_UnEquipped;
	EGoddessActionState ActionState = EGoddessActionState::EGAS_UnOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* MappingContext;

	/** 
	 * Attack
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* AttackAction;
	
	virtual void Attack();

	int32 AttackCount;

	UPROPERTY(EditAnywhere, Category=Attack)
	int32 ComboCount = 4;

	float LastAttackTime;

	const float AttackComboWindow = 2.0f;

	bool CanAttack();

	UFUNCTION(BlueprintCallable)
	virtual void FinishAttack();

	/** 
	 * Equip
	 */
	virtual void Equip();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* EquipAction;

	UPROPERTY(VisibleInstanceOnly, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	/**
	 * Play Montages Functions
	 */
	virtual void PlayAttackMontage();

	/**
	 * Montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

private:

public:
	FORCEINLINE void SetOverlappingWeapon(AItem* Item) { OverlappingItem = Item; }
};
