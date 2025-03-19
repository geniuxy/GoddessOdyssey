// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "GoddessType.h"
#include "Goddess.generated.h"

class UGoddessUIComponent;
class UGoddessCombatComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;
class AWeapon;
class AItem;
class UInputAction;
class UInputMappingContext;
enum class EGoddessActionState : uint8;

UCLASS()
class GODDESSODYSSEY_API AGoddess : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AGoddess();

	//~ Begin ICombatComponentInterface Interface.
	virtual UBaseCombatComponent* GetCombatComponentByInterface() const override;
	//~ End ICombatComponentInterface Interface

	//~ Begin IUIComponentInterface Interface.
	virtual UBaseUIComponent* GetUIComponentByInterface() const override;
	virtual UGoddessUIComponent* GetGoddessUIComponentByInterface() const override;
	//~ End IUIComponentInterface Interface

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

#pragma region Components

	UPROPERTY(EditAnywhere, Category="Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category="Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* WeaponFloatSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* WeaponPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UGoddessCombatComponent* GoddessCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UGoddessUIComponent* GoddessUIComponent;

#pragma endregion

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	UDataAsset_InputConfig* InputConfigDataAsset;

	void CallBack_Move(const FInputActionValue& InputActionValue);
	void CallBack_Look(const FInputActionValue& InputActionValue);
	void CallBack_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void CallBack_SwitchTargetCompleted(const FInputActionValue& InputActionValue);
	void CallBack_AbilityInputPressed(FGameplayTag InInputTag);
	void CallBack_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion

	UPROPERTY(BlueprintReadWrite)
	EGoddessEquippedState EquippedState = EGoddessEquippedState::EGES_UnEquipped;
	UPROPERTY(BlueprintReadWrite)
	EGoddessActionState ActionState = EGoddessActionState::EGAS_UnOccupied;

	// virtual void InitFloatingWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> FloatingWeaponClass;

	// UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	// AWeapon* FloatingWeapon;

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

	/**
	 * Custom Events
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void WeaponAttachToHandEvent();

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void WeaponBackToFloatEvent();

private:

public:
	FORCEINLINE void SetOverlappingWeapon(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE UGoddessCombatComponent* GetGoddessCombatComponent() const { return GoddessCombatComponent;}
};
